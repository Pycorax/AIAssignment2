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

	m_turnTimer = 0.f;
	m_maxTimer = 2.f;
	m_testChar = new GameCharacter();
	m_testChar->Init(GameCharacter::GC_RANGER, 10, 10, nullptr);
	m_testChar->InitProbability(50, 30, 15, 5);
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

	// Draw the environment
	for (size_t i = 0; i < EO_TOTAL; ++i)
	{
		m_renderList2D.push(m_envObjects[i]);
	}

	// Update and render the text
	ostringstream oss;
	m_textObjects[TO_TEST]->SetText("Test");

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
		m_textObjects[i]->SetPos(Vector2(0.0f, i * 3.0f));
		m_textObjects[i]->SetScale(Vector2(3.0f));
	}
}

void MVC_Model_AI::initEnvironment(void)
{
	m_envObjects[EO_TEST] = new GameObject2D;
	m_envObjects[EO_TEST]->Init(GetMeshResource("Road"), Transform(Vector3(m_viewWidth * 0.5f, m_viewHeight * 0.8f), Vector3(), Vector3(m_viewWidth * 2, 125.0f)));
}

void MVC_Model_AI::processKeyAction(double dt)
{

}

void MVC_Model_AI::onResolutionChanged(int oldViewWidth, int oldViewHeight)
{
}
