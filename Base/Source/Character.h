#ifndef _CHARACTER_H_
#define _CHARACTER_H_

// Inheritance Includes
#include "NPC.h"
#include "GameObject2D.h"
#include "MessageBoard\MessageListener.h"

// STL Includes
#include <vector>

// Other Includes
#include "WaitState.h"

class StunnedState;
class ActionState;
class DeadState;

// Using Directives
using std::vector;

class Character : public GameObject2D, public NPC, public MessageListener
{
	/*
	*		State Classes Friend Declarations
	* States should be able to access this class's properties
	*/
	friend class ActionState;
	friend class StunnedState;
	friend class WaitState;
	friend class DeadState;

public:
	static const float S_CRITICAL_HEALTH; // Percentage of health to be counted as critical (0.f - 1.f)

protected:
	int m_maxHealth;
	int m_health;
	int m_attack;
	int m_bonusAttack;

	vector<Character*> m_team;
	vector<Character*> m_opponentTeam;

	bool m_endTurn;
	bool m_hasRan; // Used in model for individual character start turn
	short m_stunnedTurns;

	WaitState::WAIT_TYPE m_waitType;

public:
	Character(int maxHealth = 1, int attack = 1);
	virtual ~Character();

	virtual void Init(int maxHealth, int attack, Mesh* mesh);
	virtual void Update(double dt);

	// Stun
	virtual void Stun(int turnDuration);
	short GetStunnedTurns();
	bool IsStunned();
	void ProcessStun(); // Reduce a count in stun turns

	// Wait State
	void SetWaitType(WaitState::WAIT_TYPE type);

	// Getters
	int GetMaxHealth(void) const;
	int GetHealth(void) const;
	int GetAttack(void) const;
	int GetBonusAttack(void) const;
	bool IsAlive(void) const;
	bool HasRan(void) const;

	void AddToTeam(Character* c);
	void AddToOpponentTeam(Character* c);

	void SetBonusAttack(int bonusAttack);
	void SetTeam(vector<Character*>& team);
	void SetOpponentTeam(vector<Character*>& opponentTeam);

	void ResetRan();

	vector<Character*>& GetTeam();
	vector<Character*>& GetOpponentTeam();

	bool GetEndTurn();

	virtual void StartTurn();
	virtual void EndTurn();

	virtual void Injure(int damage);
	void Heal(int health);

};

#endif