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

protected:
	int m_maxHealth;
	int m_health;
	int m_attack;

	vector<Character*> m_team;
	vector<Character*> m_opponentTeam;

	bool m_endTurn;
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

	vector<Character*>& GetTeam();
	vector<Character*>& GetOpponentTeam();

	virtual void StartTurn();
	virtual void Injure(int damage);
	void Heal(int health);

	void EndTurn();
	bool GetEndTurn();
};

#endif