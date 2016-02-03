#include "MVC_Model_AI.h"
#include "Raycast.h"
#include <sstream>

// Using Directives
using std::ostringstream;

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

	m_turnTimer = 0.f;
	m_maxTimer = 2.f;

	// Initialize Ranger
	m_testChar = new CharacterBundle(new GameCharacter(), m_defaultFont, Vector2());
	GameCharacter* gc = dynamic_cast<GameCharacter*>(m_testChar->character);
	gc->Init(GameCharacter::GC_RANGER, 10, 10, GetMeshResource("Character"));
	gc->InitProbability(50, 30, 15, 5);
	gc->SetPos(Vector2(100, 300));
	gc->SetScale(CHAR_SCALE);

	// Initialize Ranger Text
	m_textObjects[TO_CHAR_TYPE]->SetPos(Vector2(0.0f, 12.0f));
	m_textObjects[TO_CHAR_HEALTH]->SetPos(Vector2(0.0f, 9.0f));
	m_textObjects[TO_CHAR_STATE]->SetPos(Vector2(0.0f, 6.0f));
	m_textObjects[TO_CHAR_SUBSTATE]->SetPos(Vector2(0.0f, 3.0f));
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
		m_testChar->character->StartTurn();
		m_turnTimer = 0.f;
	}

	m_testChar->Update(dt);

	// Draw the environment
	for (size_t i = 0; i < EO_TOTAL; ++i)
	{
		m_renderList2D.push(m_envObjects[i]);
	}

	ostringstream oss;
	// Render the test char
	pushCharBundleRender(m_testChar);
	

	// Update and render the text
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
		m_textObjects[i]->SetPos(Vector2(0.0f, 60 - (i * 3.0f)));
		m_textObjects[i]->SetScale(Vector2(3.0f));
	}

	//m_textObjects[TO_MESSAGE_BOARD]->SetPos(Vector2());
}

void MVC_Model_AI::initEnvironment(void)
{
	m_envObjects[EO_TEST] = new GameObject2D;
	m_envObjects[EO_TEST]->Init(GetMeshResource("Road"), Transform(Vector3(m_viewWidth * 0.5f, m_viewHeight * 0.8f), Vector3(), Vector3(m_viewWidth * 2, 125.0f)));
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
