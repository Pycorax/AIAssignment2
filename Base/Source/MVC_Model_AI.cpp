#include "MVC_Model_AI.h"
#include "Raycast.h"
#include <sstream>

using std::ostringstream;

const int MVC_Model_AI::S_MAX_GUARDS = 3;
const float MVC_Model_AI::S_TIME_TILL_TOGGLE_WAYPOINT = 0.5f;

MVC_Model_AI::MVC_Model_AI(string configSONFile) : MVC_Model(configSONFile)
	, m_guardList(NULL)
	, m_spawnPoints(NULL)
	, m_waypointList(NULL)
	, m_bombSite(NULL)
	, m_showWaypoints(false)
	, m_toggleWaypointTimer(S_TIME_TILL_TOGGLE_WAYPOINT)
{
}

MVC_Model_AI::~MVC_Model_AI()
{
}

void MVC_Model_AI::Init(void)
{
	MVC_Model::Init();
	srand(time(NULL));
	
	initEnvironment();
	InitWaypointMap();
	InitGuards();
	initText();

	// Initialize the spy
	m_spy.Init(GetMeshResource("Player"), true, &m_waypointList);
	m_spy.SetPos(Vector3(100.0f, 100.0f, 0.0f));
	m_spy.SetScale(Vector3(50.0f, 50.0f));
	// Add the guards to the spy's guard watch so that it can keep track
	for (vector<Guard*>::iterator guardIter = m_guardList.begin(); guardIter != m_guardList.end(); ++guardIter)
	{
		m_spy.AddGuardWatch(*guardIter);
	}

	// Tell the spy to go to the bomb
	m_spy.SetTarget(m_bombSite->GetTransform().Translation);

	// Initialize the Car
	m_car.Init(GetMeshResource("Car"), m_viewWidth);
	m_car.SetPos(Vector3(500.0f, 550.0f, 0.0f));
	m_car.SetScale(Vector3(100.0f, 70.0f));
	m_car.AddVictim(&m_spy);
}

void MVC_Model_AI::Update(double dt)
{
	MVC_Model::Update(dt);

	if (m_toggleWaypointTimer < S_TIME_TILL_TOGGLE_WAYPOINT)
	{
		m_toggleWaypointTimer += dt;
	}

	// Draw the environment
	for (size_t i = 0; i < EO_TOTAL; ++i)
	{
		m_renderList2D.push(m_envObjects[i]);
	}

	// Draw the bomb site
	m_renderList2D.push(m_bombSite);

	// Draw the Waypoints
	if (m_showWaypoints)
	{
		for (int i = 0; i < m_waypointList.size(); ++i)
		{
			Waypoint* p = m_waypointList[i];
			m_renderList2D.push(p);
		}
	}

	// Update and draw the guards
	for (int i = 0; i < m_guardList.size(); ++i)
	{
		Guard* g = m_guardList[i];
		g->Update(dt);
		if (g->GetView()->GetActive())
		{
			// Check collision with spy
			int random = Math::RandIntMinMax(0, 1);
			if (random)
			{
				if (!g->GetKnockedOut() && !g->GetSleep() && Raycast::lineCircle(g, &m_spy, m_envObjects, EO_TOTAL))
				{
					g->attack(&m_spy);
					g->SetMoveSpeed(Guard::S_GUARD_ALERT_SPEED);
				}
				else
				{
					g->SetTarget(nullptr);
				}
			}
			else
			{
				if (!g->GetKnockedOut() && !g->GetSleep() && (g->GetTransform().Translation - m_spy.GetTransform().Translation).LengthSquared() <= (g->GetView()->GetTransform().Scale.x * 0.5f) * (g->GetView()->GetTransform().Scale.x * 0.5f) + (m_spy.GetTransform().Scale.x * 0.5f) * (m_spy.GetTransform().Scale.x * 0.5f))
				{
					g->attack(&m_spy);
					g->SetMoveSpeed(Guard::S_GUARD_ALERT_SPEED);
				}
				else
				{
					g->SetTarget(nullptr);
				}
			}

			m_renderList2D.push(g->GetView());
		}
		m_renderList2D.push(g);
	}

	// Draw and update the Spy
	m_spy.Update(dt);
	m_renderList2D.push(&m_spy);

	// Draw and update the Car
	m_car.Update(dt);
	m_renderList2D.push(&m_car);

	// Update and render the text
	m_textObjects[TO_SPY_STATE]->SetText("Spy State: " + m_spy.GetStateName());
	m_textObjects[TO_GUARD_STATE]->SetText("Guard State: " + m_guardList[0]->GetStateName());
	ostringstream oss;
	oss << m_spy.GetCombatRecord();
	m_textObjects[TO_BOMB_COUNT]->SetText("Bombings: " + oss.str());
	for (size_t i = 0; i < TO_TOTAL; ++i)
	{
		m_renderList2D.push(m_textObjects[i]);
	}
}

void MVC_Model_AI::Exit(void)
{
	MVC_Model::Exit();

	for (size_t i = 0; i < EO_TOTAL; ++i)
	{
		delete m_envObjects[i];
		m_envObjects[i] = NULL;
	}

	for (int i = 0; i < m_waypointList.size(); ++i)
	{
		delete m_waypointList[i];
		m_waypointList[i] = NULL;
	}

	for (int i = 0; i < m_guardList.size(); ++i)
	{
		delete m_guardList[i];
		m_guardList[i] = NULL;
	}

	// Bomb site is stored in waypoint list
	/*if (m_bombSite)
	{
		delete m_bombSite;
		m_bombSite = NULL;
	}*/
}

void MVC_Model_AI::Reset(void)
{
	Exit();
	Init();
}

void MVC_Model_AI::InitGuards()
{
	const float SIZE = 50.f;
	Guard* newGuard;
	int random;
	
	for (int i = 0; i < S_MAX_GUARDS; ++i)
	{
		newGuard = new Guard();
		random = rand() % m_spawnPoints.size();
		newGuard->Init(true, GetMeshResource("Shadow"), m_spawnPoints[random], GetMeshResource("View"), SIZE * 2.f);
		newGuard->SetScale(Vector3(SIZE, SIZE, SIZE));
		m_guardList.push_back(newGuard);
	}
}

void MVC_Model_AI::InitWaypointMap()
{
	// Map
	const float SIZE = 50.f;
	Mesh* mesh = GetMeshResource("Waypoint");

	Waypoint* point = new Waypoint("1", Vector2(m_viewWidth * 0.05, m_viewHeight * 0.62), mesh); // Point 1
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);

	point = new Waypoint("2", Vector2(m_viewWidth * 0.05, m_viewHeight * 0.4), mesh); // Point 2
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);

	point = new Waypoint("3", Vector2(m_viewWidth * 0.46, m_viewHeight * 0.62), mesh); // Point 2
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);

	point = new Waypoint("4", Vector2(m_viewWidth * 0.46, m_viewHeight * 0.4), mesh); // Point 2
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);

	point = new Waypoint("5", Vector2(m_viewWidth * 0.05, m_viewHeight * 0.005), mesh); // Point 2
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);

	point = new Waypoint("6", Vector2(m_viewWidth * 0.25, m_viewHeight * 0.005), mesh); // Point 2
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);

	point = new Waypoint("7", Vector2(m_viewWidth * 0.25, m_viewHeight * 0.23), mesh); // Point 2
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);

	point = new Waypoint("8", Vector2(m_viewWidth * 0.7, m_viewHeight * 0.23), mesh); // Point 2
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);

	point = new Waypoint("9", Vector2(m_viewWidth * 0.7, m_viewHeight * 0.005), mesh); // Point 2
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);

	point = new Waypoint("10", Vector2(m_viewWidth * 0.7, m_viewHeight * 0.13), mesh); // Point 2
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);

	point = new Waypoint("11", Vector2(m_viewWidth * 0.88, m_viewHeight * 0.13), mesh); // Point 2
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);

	point = new Waypoint("12", Vector2(m_viewWidth * 0.88, m_viewHeight * 0.58), mesh); // Point 2
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);

	point = new Waypoint("13", Vector2(m_viewWidth * 0.7, m_viewHeight * 0.58), mesh); // Point 2
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);

	// Bomb site
	point = new Waypoint("Bomb site", Vector2(m_viewWidth * 0.6f, m_viewHeight * 0.3f), GetMeshResource("BombSite")); // Point 2
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);
	m_bombSite = point;

	// 1 links to 2
	m_waypointList[0]->AddToNext(m_waypointList[1]);
	m_waypointList[1]->AddToNext(m_waypointList[0]);
	// 1 links to 3
	m_waypointList[0]->AddToNext(m_waypointList[2]);
	m_waypointList[2]->AddToNext(m_waypointList[0]);
	// 4 links to 2 and 3
	m_waypointList[3]->AddToNext(m_waypointList[1]);
	m_waypointList[3]->AddToNext(m_waypointList[2]);
	m_waypointList[1]->AddToNext(m_waypointList[3]);
	m_waypointList[2]->AddToNext(m_waypointList[3]);
	// 5 links to 2
	m_waypointList[4]->AddToNext(m_waypointList[1]);
	m_waypointList[1]->AddToNext(m_waypointList[4]);
	// 6 links to 5 and 2
	m_waypointList[5]->AddToNext(m_waypointList[4]);
	m_waypointList[5]->AddToNext(m_waypointList[1]);
	m_waypointList[4]->AddToNext(m_waypointList[5]);
	m_waypointList[1]->AddToNext(m_waypointList[5]);
	// 7 links to 6 and 5 and 2 and 4
	m_waypointList[6]->AddToNext(m_waypointList[5]);
	m_waypointList[6]->AddToNext(m_waypointList[4]);
	m_waypointList[6]->AddToNext(m_waypointList[1]);
	m_waypointList[6]->AddToNext(m_waypointList[3]);
	m_waypointList[5]->AddToNext(m_waypointList[6]);
	m_waypointList[4]->AddToNext(m_waypointList[6]);
	m_waypointList[1]->AddToNext(m_waypointList[6]);
	m_waypointList[3]->AddToNext(m_waypointList[6]);
	// 8 links to 7 and 4
	m_waypointList[7]->AddToNext(m_waypointList[6]);
	m_waypointList[7]->AddToNext(m_waypointList[3]);
	m_waypointList[6]->AddToNext(m_waypointList[7]);
	m_waypointList[3]->AddToNext(m_waypointList[7]);
	// 9 links to 8 and 6
	m_waypointList[8]->AddToNext(m_waypointList[7]);
	m_waypointList[8]->AddToNext(m_waypointList[5]);
	m_waypointList[7]->AddToNext(m_waypointList[8]);
	m_waypointList[5]->AddToNext(m_waypointList[8]);
	// 10 links to 8 and 9
	m_waypointList[9]->AddToNext(m_waypointList[8]);
	m_waypointList[9]->AddToNext(m_waypointList[7]);
	m_waypointList[8]->AddToNext(m_waypointList[9]);
	m_waypointList[7]->AddToNext(m_waypointList[9]);
	// 11 links to 10 and 9
	m_waypointList[10]->AddToNext(m_waypointList[9]);
	m_waypointList[10]->AddToNext(m_waypointList[8]);
	m_waypointList[9]->AddToNext(m_waypointList[10]);
	m_waypointList[8]->AddToNext(m_waypointList[10]);
	// 12 links to 11
	m_waypointList[11]->AddToNext(m_waypointList[10]);
	m_waypointList[10]->AddToNext(m_waypointList[11]);
	// 13 links to 3 and 4 and 8 and 12
	m_waypointList[12]->AddToNext(m_waypointList[2]);
	m_waypointList[12]->AddToNext(m_waypointList[3]);
	m_waypointList[12]->AddToNext(m_waypointList[7]);
	m_waypointList[12]->AddToNext(m_waypointList[11]);
	m_waypointList[2]->AddToNext(m_waypointList[12]);
	m_waypointList[3]->AddToNext(m_waypointList[12]);
	m_waypointList[7]->AddToNext(m_waypointList[12]);
	m_waypointList[11]->AddToNext(m_waypointList[12]);
	// Bomb site(14) links to 4 and 7 and 8 and 13
	m_waypointList[13]->AddToNext(m_waypointList[3]);
	m_waypointList[13]->AddToNext(m_waypointList[6]);
	m_waypointList[13]->AddToNext(m_waypointList[7]);
	m_waypointList[13]->AddToNext(m_waypointList[12]);
	m_waypointList[3]->AddToNext(m_waypointList[13]);
	m_waypointList[6]->AddToNext(m_waypointList[13]);
	m_waypointList[7]->AddToNext(m_waypointList[13]);
	m_waypointList[12]->AddToNext(m_waypointList[13]);

	// Set spawn points
	if (m_waypointList.size() > 0)
	{
		for (int i = 0; i < m_waypointList.size() - 1; ++i)
		{
			m_spawnPoints.push_back(m_waypointList[i]);
		}
	}

	// Generate 100 random values
	/*const int MAX_RANDOM = 100;
	float random[MAX_RANDOM];
	for (int i = 0; i < MAX_RANDOM; ++i)
	{
		random[i] = Math::RandFloatMinMax(0.f, 1.f);
	}
	int randomCounter = 0;

	mesh = GetMeshResource("TILE_FLOOR");
	// Method: Create and label all waypoints before assigning paths to each waypoint
	point = new Waypoint("A", Vector2(m_viewWidth * 0.5, m_viewHeight * 0.5), mesh); // A point
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);
	m_spawnPoints.push_back(point); // Add to spawnPoints

	//m_waypointMap = point; // Starting point of the map

	point = new Waypoint("B", Vector2(m_viewWidth * random[randomCounter++], m_viewHeight * random[randomCounter++]), mesh); // A point
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);
	point = new Waypoint("C", Vector2(m_viewWidth * random[randomCounter++], m_viewHeight * random[randomCounter++]), mesh); // A point
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);
	point = new Waypoint("D", Vector2(m_viewWidth * random[randomCounter++], m_viewHeight * random[randomCounter++]), mesh); // A point
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);
	m_spawnPoints.push_back(point); // Add to spawnPoints
	point = new Waypoint("E", Vector2(m_viewWidth * random[randomCounter++], m_viewHeight * random[randomCounter++]), mesh); // A point
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);
	point = new Waypoint("F", Vector2(m_viewWidth * random[randomCounter++], m_viewHeight * random[randomCounter++]), mesh); // A point
	point->SetScale(Vector3(SIZE, SIZE, SIZE));
	m_waypointList.push_back(point);

	// Assigning paths for each waypoint (In this case, all waypoint can lead to all other paths)
	for (int i = 0; i < m_waypointList.size(); ++i)
	{
		for (int j = 0; j < m_waypointList.size(); ++j)
		{
			Waypoint* currPoint = m_waypointList[i];	// Point that is getting added to
			Waypoint* addPoint = m_waypointList[j];	// Point that is being added
			if (currPoint != addPoint)
			{
				currPoint->AddToNext(addPoint);
			}
		}
	}*/
}

void MVC_Model_AI::initText(void)
{
	for (size_t i = 0; i < TO_TOTAL; ++i)
	{
		m_textObjects[i] = new TextObject(m_defaultFont, "", Color(0.0f, 0.0f, 0.0f));
		m_textObjects[i]->SetPos(Vector2(0.0f, i * 3.0f));
		m_textObjects[i]->SetScale(Vector2(3.0f));
	}
}

void MVC_Model_AI::initEnvironment(void)
{
	m_envObjects[EO_ROAD] = new GameObject2D;
	m_envObjects[EO_ROAD]->Init(GetMeshResource("Road"), Transform(Vector3(m_viewWidth * 0.5f, m_viewHeight * 0.8f), Vector3(), Vector3(m_viewWidth * 2, 125.0f)));
	m_envObjects[EO_BUILDING_LEFT] = new GameObject2D;
	m_envObjects[EO_BUILDING_LEFT]->Init(GetMeshResource("Building"), Transform(Vector3(m_viewWidth * 0.2f + 100.0f, m_viewHeight * 0.55f), Vector3(), Vector3(420.0f, 80.0f)));
	m_envObjects[EO_BUILDING_MID] = new GameObject2D;
	m_envObjects[EO_BUILDING_MID]->Init(GetMeshResource("Building"), Transform(Vector3(m_viewWidth * 0.32f + 225.0f, m_viewHeight * 0.15f), Vector3(), Vector3(450.0f, 100.0f)));
	m_envObjects[EO_BUILDING_RIGHT] = new GameObject2D;
	m_envObjects[EO_BUILDING_RIGHT]->Init(GetMeshResource("Building"), Transform(Vector3(m_viewWidth * 0.78f + 50.0f, m_viewHeight * 0.4f), Vector3(), Vector3(100.0f, 230.0f)));

	// Road Strips
	Mesh* roadStripMesh = GetMeshResource("RoadStrip");
	m_envObjects[EO_ROAD_STRIP_1] = new GameObject2D;
	m_envObjects[EO_ROAD_STRIP_1]->Init(roadStripMesh, Transform(Vector2(m_viewWidth * 0.2f, m_viewHeight * 0.8f), Vector2::ZERO_VECTOR, Vector2(130.0f, 10.0f)));
	m_envObjects[EO_ROAD_STRIP_2] = new GameObject2D;
	m_envObjects[EO_ROAD_STRIP_2]->Init(roadStripMesh, Transform(Vector2(m_viewWidth * 0.5f, m_viewHeight * 0.8f), Vector2::ZERO_VECTOR, Vector2(130.0f, 10.0f)));
	m_envObjects[EO_ROAD_STRIP_3] = new GameObject2D;
	m_envObjects[EO_ROAD_STRIP_3]->Init(roadStripMesh, Transform(Vector2(m_viewWidth * 0.8f, m_viewHeight * 0.8f), Vector2::ZERO_VECTOR, Vector2(130.0f, 10.0f)));
}

void MVC_Model_AI::processKeyAction(double dt)
{
	// Do reset
	if (m_bKeyPressed[MISC_0_KEY])
	{

	}

	if (m_bKeyPressed[MISC_1_KEY])
	{
		m_spy.Kill();
	}

	if (m_bKeyPressed[MOVE_JUMP_KEY] && m_toggleWaypointTimer >= S_TIME_TILL_TOGGLE_WAYPOINT)
	{
		m_showWaypoints = !m_showWaypoints;
		m_toggleWaypointTimer = 0.f;
	}
}

void MVC_Model_AI::onResolutionChanged(int oldViewWidth, int oldViewHeight)
{
}
