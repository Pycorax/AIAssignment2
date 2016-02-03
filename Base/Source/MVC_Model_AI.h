#ifndef MVC_MODEL_AI_H
#define MVC_MODEL_AI_H

// Inheritance Includes
#include "MVC_Model.h"

// Other Includes
#include "TextObject.h"
#include "GameCharacter.h"
#include "Enemy.h"
#include "MessageBoard\MessageBoard.h"

class MVC_Model_AI : public MVC_Model
{
private:
	enum E_ENV_OBJECT
	{
		EO_TEST,
		EO_TOTAL
	};

	enum E_TEXT_OBJECT
	{
		TO_TEST,
		TO_MESSAGE_BOARD,
		TO_TOTAL
	};

private:
	// Text Output
	TextObject* m_textObjects[TO_TOTAL];

	// Environment Objects
	GameObject2D* m_envObjects[EO_TOTAL];

	// MessageBoard
	MessageBoard m_messageBoard;

	// Characters
	GameCharacter* m_testChar;
	TextObject* m_testState;
	float m_turnTimer;
	float m_maxTimer;

	vector<GameCharacter*> m_charList;
	vector<Enemy*> m_enemyList;

public:
	MVC_Model_AI(string configSONFile);
	~MVC_Model_AI();

	void Init(void);
	void Update(double dt);
	void Exit(void);
	void Reset(void);

private:
	void initText(void);
	void initEnvironment(void);

	void initPlayers(void);
	void initEnemies(void);
	void assignTeams(void);

	// Input
	void processKeyAction(double dt);
	// Resizing Code
	void onResolutionChanged(int oldViewWidth, int oldViewHeight);

	//bool lineCircle(Guard* go1, Guard* go2);
	//bool lineLine(Vector2 a1, Vector2 a2, Vector2 b1, Vector2 b2);
};

#endif
