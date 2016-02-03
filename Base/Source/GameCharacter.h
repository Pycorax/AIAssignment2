#ifndef _GAME_CHARACTER_H_
#define _GAME_CHARACTER_H_

#include "Character.h"

struct Probabilities
{
	// State probability (Out of 100)
	short m_attackProbability;
	short m_defendProbability;
	short m_specialProbability;
	short m_passProbability;

	// Default values
	short m_defaultAttackProbability;
	short m_defaultDefendProbability;
	short m_defaultSpecialProbability;
	short m_defaultPassProbability;

	void Init(short attProb, short defProb, short specProb, short passProb)
	{
		m_attackProbability = m_defaultAttackProbability = attProb;
		m_defendProbability = m_defaultDefendProbability = defProb;
		m_specialProbability = m_defaultSpecialProbability = specProb;
		m_passProbability = m_defaultPassProbability = passProb;
	}

	void Set(short attProb, short defProb, short specProb, short passProb)
	{
		m_attackProbability = attProb;
		m_defendProbability = defProb;
		m_specialProbability = specProb;
		m_passProbability = passProb;
	}

	void SetDefault()
	{
		m_attackProbability = m_defaultAttackProbability;
		m_defendProbability = m_defaultDefendProbability;
		m_specialProbability = m_defaultSpecialProbability;
		m_passProbability = m_defaultPassProbability;
	}

	void Reset()
	{
		m_attackProbability = 0;
		m_defendProbability = 0;
		m_specialProbability = 0;
		m_passProbability = 0;
	}
};

class GameCharacter : public Character
{
	friend class StartTurnState;
	friend class AttackState;
	friend class DefendState;
	friend class PassState;
	friend class SpecialState;
	friend class DeadState;

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

	Probabilities probabilities;

public:
	GameCharacter();
	virtual ~GameCharacter();

	virtual void Init(GAME_CHARACTER_TYPE type, int maxHealth, int attack, Mesh* mesh);
	void InitProbability(short attProb, short defProb, short specProb, short passProb);
	virtual void Update(double dt);

	virtual void StartTurn();
	virtual void EndTurn();

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

	void replaceDead(GameCharacter* dead);
};

#endif