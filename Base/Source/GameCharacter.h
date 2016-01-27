#ifndef _GAME_CHARACTER_H_
#define _GAME_CHARACTER_H_

#include "Character.h"

class GameCharacter : public Character
{
	friend class ActionState;
	friend class AttackState;
	friend class DefendState;
	friend class PassState;

public:
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

	// State probability (Out of 100)
	short m_attackProbability;
	short m_defendProbability;
	short m_specialProbability;
	short m_passProbability;

public:
	GameCharacter();
	virtual ~GameCharacter();

	void SetGuarder(Character* guarder);
	Character* GetGuarder();

	void Defend();
	bool GetDefend();

	void SetType(GAME_CHARACTER_TYPE type);
	GAME_CHARACTER_TYPE GetType();

	short GetAttackProbability();
	short GetDefendProbability();
	short GetSpecialProbability();
	short GetPassProbability();
};

#endif