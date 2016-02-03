#include "MVC_Model_AI.h"
#include "Raycast.h"
#include <sstream>

using std::ostringstream;

MVC_Model_AI::MVC_Model_AI(string configSONFile) : MVC_Model(configSONFile)
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
	initText();
	initPlayers();
	initEnemies();
	assignTeams();

	m_turnTimer = 0.f;
	m_maxTimer = 2.f;
	m_testChar = new GameCharacter();
	m_testChar->Init(GameCharacter::GC_RANGER, 10, 10, GetMeshResource("Character"));
	m_testChar->InitProbability(50, 30, 15, 5);
	m_testChar->SetPos(Vector2(100, 100));
	m_testChar->SetScale(Vector3(50, 50, 50));
	m_testState = new TextObject(GetMeshResource("DefaultFont"), "", Color(1, 0, 0));
	m_testState->SetPos(Vector3(0, 6, 0));
	m_testState->SetScale(Vector3(3,3,3));
}

void MVC_Model_AI::Update(double dt)
{
	MVC_Model::Update(dt);

	if (m_turnTimer < m_maxTimer)
	{
		m_turnTimer += dt;
	}
	else
	{
		m_testChar->StartTurn();
		m_turnTimer = 0.f;
	}
	m_testChar->Update(dt);
	m_testState->SetText(m_testChar->GetStateName());
	m_renderList2D.push(m_testState);

	// Draw the environment
	for (size_t i = 0; i < EO_TOTAL; ++i)
	{
		m_renderList2D.push(m_envObjects[i]);
	}

	// Render the test char
	m_renderList2D.push(m_testChar);

	// Update and render the text
	ostringstream oss;
	m_textObjects[TO_TEST]->SetText("Test");
	oss << m_fps;
	m_textObjects[TO_FPS]->SetText(oss.str());
	oss.str("");
	m_textObjects[TO_MESSAGE_BOARD]->SetText(m_messageBoard.PeekGlobalMessage().ToString());

	// Push all the text into the render queue
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

	while (m_charList.size() > 0)
	{
		GameCharacter* gc = m_charList.back();
		if (gc)
		{
			delete gc;
		}
		m_charList.pop_back();
	}

	while (m_enemyList.size() > 0)
	{
		Enemy* e = m_enemyList.back();
		if (e)
		{
			delete e;
		}
		m_enemyList.pop_back();
	}
}

void MVC_Model_AI::Reset(void)
{
	Exit();
	Init();
}

void MVC_Model_AI::initText(void)
{
	for (size_t i = 0; i < TO_TOTAL; ++i)
	{
		m_textObjects[i] = new TextObject(m_defaultFont, "", Color(0.0f, 0.0f, 0.0f));
		m_textObjects[i]->SetPos(Vector2(0.0f, i * 3.0f));
		m_textObjects[i]->SetScale(Vector2(3.0f));
	}

	//m_textObjects[TO_MESSAGE_BOARD]->SetPos(Vector2());
}

void MVC_Model_AI::initEnvironment(void)
{
	m_envObjects[EO_TEST] = new GameObject2D;
	m_envObjects[EO_TEST]->Init(GetMeshResource("Road"), Transform(Vector3(m_viewWidth * 0.5f, m_viewHeight * 0.8f), Vector3(), Vector3(m_viewWidth * 2, 125.0f)));
}

void MVC_Model_AI::initPlayers(void)
{
	GameCharacter* gc = new GameCharacter();

	// Healer
	gc->Init(GameCharacter::GC_HEALER, Math::RandIntMinMax(50, 70), 10, nullptr);
	gc->InitProbability(70, 20, 0, 10);
	// TODO: Set pos and scale
	m_charList.push_back(gc);

	// Warrior
	gc->Init(GameCharacter::GC_WARRIOR, Math::RandIntMinMax(50, 70), 10, nullptr);
	gc->InitProbability(50, 20, 20, 10);
	// TODO: Set pos and scale
	m_charList.push_back(gc);

	// Tank
	gc->Init(GameCharacter::GC_TANK, Math::RandIntMinMax(50, 70), 10, nullptr);
	gc->InitProbability(70, 20, 0, 10);
	// TODO: Set pos and scale
	m_charList.push_back(gc);

	// Ranger
	gc->Init(GameCharacter::GC_RANGER, Math::RandIntMinMax(50, 70), 10, nullptr);
	gc->InitProbability(70, 20, 0, 10);
	// TODO: Set pos and scale
	m_charList.push_back(gc);
}

void MVC_Model_AI::initEnemies(void)
{
}

void MVC_Model_AI::assignTeams(void)
{
	// Game characters
	for (vector<GameCharacter*>::iterator it = m_charList.begin(); it != m_charList.end(); ++it)
	{
		GameCharacter* gc = *it;
		if (gc)
		{
			// Assign game character's team
			for (vector<GameCharacter*>::iterator it2 = m_charList.begin(); it2 != m_charList.end(); ++it2)
			{
				GameCharacter* gc2 = *it2;
				if (gc2)
				{
					gc->AddToTeam(gc2);
				}
			}

			// Assign game character's opponent team
			for (vector<Enemy*>::iterator it2 = m_enemyList.begin(); it2 != m_enemyList.end(); ++it2)
			{
				Enemy* e = *it2;
				if (e)
				{
					gc->AddToOpponentTeam(e);
				}
			}
		}
	}

	// Enemies
	for (vector<Enemy*>::iterator it = m_enemyList.begin(); it != m_enemyList.end(); ++it)
	{
		Enemy* e = *it;
		if (e)
		{
			// Assign enemy's team
			for (vector<Enemy*>::iterator it2 = m_enemyList.begin(); it2 != m_enemyList.end(); ++it2)
			{
				Enemy* e2 = *it2;
				if (e2)
				{
					e->AddToTeam(e2);
				}
			}

			// Assign enemy's opponent team
			for (vector<GameCharacter*>::iterator it2 = m_charList.begin(); it2 != m_charList.end(); ++it2)
			{
				GameCharacter* gc = *it2;
				if (gc)
				{
					e->AddToOpponentTeam(gc);
				}
			}
		}
	}
}

void MVC_Model_AI::processKeyAction(double dt)
{

}

void MVC_Model_AI::onResolutionChanged(int oldViewWidth, int oldViewHeight)
{
}
