#include "Character.h"
#include "ActionState.h"

Character::Character(int maxHealth, int attack)
	: m_maxHealth(maxHealth)
	, m_health(maxHealth)
	, m_attack(attack)
	, m_team(NULL)
	, m_opponentTeam(NULL)
	, m_endTurn(false)
{
	
}

Character::~Character()
{
}

int Character::GetMaxHealth(void) const
{
	return m_maxHealth;
}

int Character::GetHealth(void) const
{
	return m_health;
}

int Character::GetAttack(void) const
{
	return m_attack;
}

vector<Character*>& Character::GetTeam()
{
	return m_team;
}

vector<Character*>& Character::GetOpponentTeam()
{
	return m_opponentTeam;
}

void Character::StartTurn()
{
	m_endTurn = false;
	setCurrentState(new ActionState());
}

void Character::Injure(int damage)
{
	// Don't allow adding of health
	if (damage <= 0)
	{
		return;
	}

	// Deduct the health
	m_health -= damage;

	// Clamp the health
	if (m_health < 0)
	{
		m_health = 0;
	}
}

void Character::Heal(int health)
{
	// Don't allow damaging of health
	if (health <= 0)
	{
		return;
	}

	// Deduct the health
	m_health += health;

	// Clamp the health
	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
}

void Character::EndTurn()
{
	m_endTurn = true;
}

bool Character::GetEndTurn()
{
	return m_endTurn;
}
