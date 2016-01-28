#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <vector>
#include "NPC.h"
#include "GameObject2D.h"

using std::vector;

class Character : public GameObject2D, public NPC
{
	/*
	*		State Classes Friend Declarations
	* States should be able to access this class's properties
	*/

protected:
	int m_maxHealth;
	int m_health;
	int m_attack;

	vector<Character*> m_team;
	vector<Character*> m_opponentTeam;

	bool m_endTurn;

public:
	Character(int maxHealth = 1, int attack = 1);
	virtual ~Character();

	virtual void Init(int maxHealth, int attack, Mesh* mesh);
	virtual void Update(double dt);

	int GetMaxHealth(void) const;
	int GetHealth(void) const;
	int GetAttack(void) const;

	vector<Character*>& GetTeam();
	vector<Character*>& GetOpponentTeam();

	void StartTurn();
	void Injure(int damage);
	void Heal(int health);

	void EndTurn();
	bool GetEndTurn();
};

#endif