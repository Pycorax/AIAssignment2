#include "MVC_Model_AI.h"
#include "Raycast.h"

// Static Constants
const Vector3 MVC_Model_AI::CHAR_SCALE = Vector3(50.0f, 50.0f, 50.0f);

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
}

void MVC_Model_AI::Update(double dt)
{
	MVC_Model::Update(dt);

	// Draw the environment
	for (size_t i = 0; i < EO_TOTAL; ++i)
	{
		m_renderList2D.push(m_envObjects[i]);
	}

	startTurns();
	spawnEnemy();

	// Update and render all the characters
	for (auto c : m_charList)
	{
		c->Update(dt);
		c->UpdateText();
		pushCharBundleRender(c);
	}

	for (auto c : m_enemyList)
	{
		c->Update(dt);
		c->UpdateText();
		pushCharBundleRender(c);
	}

	// Update and render the text
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
		CharacterBundle* gc = m_charList.back();
		if (gc)
		{
			delete gc;
		}
		m_charList.pop_back();
	}

	while (m_enemyList.size() > 0)
	{
		CharacterBundle* e = m_enemyList.back();
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
		m_textObjects[i]->SetPos(Vector2(0.0f, 69 - (i * 3.0f)));
		m_textObjects[i]->SetScale(Vector2(3.0f));
	}

	//m_textObjects[TO_MESSAGE_BOARD]->SetPos(Vector2());
}

void MVC_Model_AI::initEnvironment(void)
{
	m_envObjects[EO_TEST] = new GameObject2D;
	m_envObjects[EO_TEST]->Init(nullptr, Transform(Vector3(m_viewWidth * 0.5f, m_viewHeight * 0.8f), Vector3(), Vector3(m_viewWidth * 2, 125.0f)));
}

void MVC_Model_AI::initPlayers(void)
{
	// Ranger
	GameCharacter* gc = new GameCharacter();
	gc->Init(GameCharacter::GC_RANGER, Math::RandIntMinMax(50, 70), 10, GetMeshResource("Character"));
	gc->InitProbability(45, 20, 25, 10);
	gc->InitProbability(50, 30, 15, 5);
	gc->SetPos(Vector2(100, 200));
	gc->SetScale(CHAR_SCALE);
	m_messageBoard.RegisterUser(gc);
	m_charList.push_back(new CharacterBundle(gc, m_defaultFont, Vector2(90)));

	// Healer
	gc = new GameCharacter();
	gc->Init(GameCharacter::GC_HEALER, Math::RandIntMinMax(50, 70), 10, GetMeshResource("Character"));
	gc->InitProbability(70, 20, 0, 10);
	gc->SetPos(Vector2(100, 500));
	gc->SetScale(CHAR_SCALE);
	m_messageBoard.RegisterUser(gc);
	m_charList.push_back(new CharacterBundle(gc, m_defaultFont, Vector2()));

	// Warrior
	gc = new GameCharacter();
	gc->Init(GameCharacter::GC_WARRIOR, Math::RandIntMinMax(50, 70), 10, GetMeshResource("Character"));
	gc->InitProbability(50, 20, 20, 10);
	gc->InitProbability(50, 30, 15, 5);
	gc->SetPos(Vector2(100, 400));
	gc->SetScale(CHAR_SCALE);
	m_messageBoard.RegisterUser(gc);
	m_charList.push_back(new CharacterBundle(gc, m_defaultFont, Vector2(30)));

	// Tank
	gc = new GameCharacter();
	gc->Init(GameCharacter::GC_TANK, Math::RandIntMinMax(50, 70), 10, GetMeshResource("Character"));
	gc->InitProbability(70, 20, 0, 10);
	gc->InitProbability(50, 30, 15, 5);
	gc->SetPos(Vector2(100, 300));
	gc->SetScale(CHAR_SCALE);
	m_messageBoard.RegisterUser(gc);
	m_charList.push_back(new CharacterBundle(gc, m_defaultFont, Vector2(60)));
}

void MVC_Model_AI::initEnemies(void)
{
	Enemy* e = new Enemy();
	e->Init(Math::RandIntMinMax(100, 150), Math::RandIntMinMax(20, 30), GetMeshResource("Character"));
	e->SetPos(Vector2(1180, 200));
	e->SetScale(CHAR_SCALE);
	m_enemyList.push_back(new CharacterBundle(e, m_defaultFont, Vector2(90, 50)));
}

void MVC_Model_AI::assignTeams(void)
{
	// Game characters
	for (auto it = m_charList.begin(); it != m_charList.end(); ++it)
	{
		GameCharacter* gc = dynamic_cast<GameCharacter*>((*it)->character);
		if (gc)
		{
			// Assign game character's team
			for (auto it2 = m_charList.begin(); it2 != m_charList.end(); ++it2)
			{
				GameCharacter* gc2 = dynamic_cast<GameCharacter*>((*it2)->character);
				if (gc2)
				{
					gc->AddToTeam(gc2);
				}
			}

			// Assign game character's opponent team
			for (auto it2 = m_enemyList.begin(); it2 != m_enemyList.end(); ++it2)
			{
				Enemy* e = dynamic_cast<Enemy*>((*it2)->character);
				if (e)
				{
					gc->AddToOpponentTeam(e);
				}
			}
		}
	}

	// Enemies
	for (auto it = m_enemyList.begin(); it != m_enemyList.end(); ++it)
	{
		Enemy* e = dynamic_cast<Enemy*>((*it)->character);
		if (e)
		{
			// Assign enemy's team
			for (auto it2 = m_enemyList.begin(); it2 != m_enemyList.end(); ++it2)
			{
				Enemy* e2 = dynamic_cast<Enemy*>((*it2)->character);
				if (e2)
				{
					e->AddToTeam(e2);
				}
			}

			// Assign enemy's opponent team
			for (auto it2 = m_charList.begin(); it2 != m_charList.end(); ++it2)
			{
				GameCharacter* gc = dynamic_cast<GameCharacter*>((*it2)->character);
				if (gc)
				{
					e->AddToOpponentTeam(gc);
				}
			}
		}
	}
}

void MVC_Model_AI::startTurns()
{
	static bool playerTurn = true;
	int count = 0; // Count to check if all characters have finished their turn so next type of character can start
	static int currentCounter = 0; // "Points" to the current updating character
	
	if (playerTurn)
	{
		CharacterBundle* c = m_charList[currentCounter];
		if (!c->character->HasRan()) // Hasn't ran
		{
			if (c->character->GetEndTurn()) // Ended turn
			{
				// Ended turn but hasn't ran
				c->character->StartTurn();
				return;
			}
		}
		else // Ran
		{
			if (c->character->GetEndTurn()) // Ended turn
			{
				// Ended turn and ran
				++currentCounter;
				if (currentCounter >= m_charList.size())
				{
					// Next type of character turn (Reset data)
					playerTurn = false;
					currentCounter = 0;
					for (auto c : m_charList)
					{
						c->character->ResetRan();
					}
				}
			}
		}
	}
	else
	{
		CharacterBundle* e = m_enemyList[currentCounter];
		if (!e->character->HasRan()) // Hasn't ran
		{
			if (e->character->GetEndTurn()) // Ended turn
			{
				// Ended turn but hasn't ran
				e->character->StartTurn();
				return;
			}
		}
		else // Ran
		{
			if (e->character->GetEndTurn()) // Ended turn
			{
				// Ended turn and ran
				++currentCounter;
				if (currentCounter >= m_enemyList.size())
				{
					// Next type of character turn (Reset data)
					playerTurn = true;
					currentCounter = 0;
					for (auto c : m_enemyList)
					{
						c->character->ResetRan();
					}
				}
			}
		}
	}
}

void MVC_Model_AI::spawnEnemy()
{
	for (auto e : m_enemyList)
	{
		if (!e->character->IsAlive())
		{
			e->character->Init(Math::RandIntMinMax(100, 150), Math::RandIntMinMax(20, 30), GetMeshResource("Character"));
			e->character->SetPos(Vector2(1180, 200));
			e->character->SetScale(CHAR_SCALE);
		}
	}
}

void MVC_Model_AI::pushCharBundleRender(CharacterBundle * ch)
{
	// Push the character
	m_renderList2D.push(ch->character);

	// Push the text
	for (size_t i = 0; i < CharacterBundle::CTD_TOTAL; ++i)
	{
		m_renderList2D.push(ch->charDetail[i]);
	}
}

void MVC_Model_AI::processKeyAction(double dt)
{

}

void MVC_Model_AI::onResolutionChanged(int oldViewWidth, int oldViewHeight)
{
}
