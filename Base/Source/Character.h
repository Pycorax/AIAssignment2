#pragma once

#include "NPC.h"
#include "GameObject2D.h"

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

public:
	Character(int maxHealth, int attack);
	virtual ~Character();

	int GetMaxHealth(void) const;
	int GetHealth(void) const;
	int GetAttack(void) const;

	void Injure(int damage);
	void Heal(int health);
};