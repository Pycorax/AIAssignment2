#ifndef MVC_MODEL_AI_H
#define MVC_MODEL_AI_H

// Inheritance Includes
#include "MVC_Model.h"

// Other Includes
#include "TextObject.h"
#include "GameCharacter.h"
#include "MessageBoard\MessageBoard.h"
#include "CharacterBundle.h"

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
		TO_CHAR_HEALTH,
		TO_CHAR_STATE,
		TO_CHAR_SUBSTATE,
		TO_CHAR_TYPE,
		TO_FPS,
		TO_MESSAGE_BOARD,
		TO_TOTAL
	};

private:
	// Static Constants
	static const Vector3 CHAR_SCALE;

	// Text Output
	TextObject* m_textObjects[TO_TOTAL];

	// Environment Objects
	GameObject2D* m_envObjects[EO_TOTAL];

	// MessageBoard
	MessageBoard m_messageBoard;

	// Characters
	CharacterBundle* m_testChar;
	float m_turnTimer;
	float m_maxTimer;

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

	// Render
	void pushCharBundleRender(CharacterBundle* ch);

	// Input
	void processKeyAction(double dt);
	// Resizing Code
	void onResolutionChanged(int oldViewWidth, int oldViewHeight);

	//bool lineCircle(Guard* go1, Guard* go2);
	//bool lineLine(Vector2 a1, Vector2 a2, Vector2 b1, Vector2 b2);
};

#endif
