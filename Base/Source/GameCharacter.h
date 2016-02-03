#ifndef _GAME_CHARACTER_H_
#define _GAME_CHARACTER_H_

#include "Character.h"

class GameCharacter : public Character
{
	friend class StartTurnState;
	friend class AttackState;
	friend class DefendState;
	friend class PassState;
	friend class SpecialState;

public:
	static const float S_GUARD_DAMAGE_REDUCTION; // In percentage from 0.f - 1.f
	enum GAME_CHARACTER_TYPE
	{
		GC_WARRIOR,
		GC_RANGER,
		GC_TANK,
		GC_HEALER,
		NUM_GC,
	};

protected:
	Character* m_guarder; // Pointer to character that is guarding this game character
	bool m_defending; // Defend
	GAME_CHARACTER_TYPE m_type;
	Character* m_nextTarget; // Plan next target when processing message

	// State probability (Out of 100)
	short m_attackProbability;
	short m_defendProbability;
	short m_specialProbability;
	short m_passProbability;

public:
	GameCharacter();
	virtual ~GameCharacter();

	virtual void Init(GAME_CHARACTER_TYPE type, int maxHealth, int attack, Mesh* mesh);
	void InitProbability(short attProb, short defProb, short specProb, short passProb);
	virtual void Update(double dt);

	virtual void StartTurn();
	virtual void EndStart();

	virtual void Injure(int damage);
	virtual void Stun(int turnDuration);

	void RequestSupport();

	void Guard(Character* guarder);
	Character* GetGuarder();

	void Defend();
	bool GetDefend();

	void SetType(GAME_CHARACTER_TYPE type);
	GAME_CHARACTER_TYPE GetType();

	void SetNextTarget(Character* target);
	Character* GetNextTarget();

	short GetAttackProbability();
	short GetDefendProbability();
	short GetSpecialProbability();
	short GetPassProbability();

	/*
	 * Message Listener Interface Abstract Functions
	 */
	virtual void handleMessage(Message msg);
};

#endif