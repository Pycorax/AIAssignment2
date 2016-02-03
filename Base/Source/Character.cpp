#include "Character.h"

const float Character::S_CRITICAL_HEALTH = 0.3;

Character::Character(int maxHealth, int attack)
	: m_maxHealth(maxHealth)
	, m_health(maxHealth)
	, m_attack(attack)
	, m_bonusAttack(0)
	, m_team(NULL)
	, m_opponentTeam(NULL)
	, m_endTurn(true)
{
	
}

Character::~Character()
{
}

void Character::Init(int maxHealth, int attack, Mesh * mesh)
{
	m_maxHealth = m_health = maxHealth;
	m_attack = attack;
	GameObject2D::Init(mesh, Transform());
}

void Character::Update(double dt)
{
	NPC::Update(dt);
	HandleMessage();
}

void Character::Stun(int numOfTurns)
{
	m_stunnedTurns += numOfTurns;
}

short Character::GetStunnedTurns()
{
	return m_stunnedTurns;
}

bool Character::IsStunned()
{
	return m_stunnedTurns > 0;
}

void Character::ProcessStun()
{
	if (m_stunnedTurns > 0)
	{
		--m_stunnedTurns;
	}
}

void Character::SetWaitType(WaitState::WAIT_TYPE type)
{
	m_waitType = type;
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
	return m_attack + m_bonusAttack;
}

int Character::GetBonusAttack(void) const
{
	return m_bonusAttack;
}

bool Character::IsAlive(void) const
{
	return m_health > 0;
}

void Character::AddToTeam(Character * c)
{
	m_team.push_back(c);
}

void Character::AddToOpponentTeam(Character * c)
{
	m_opponentTeam.push_back(c);
}

void Character::SetBonusAttack(int bonusAttack)
{
	m_bonusAttack = bonusAttack;
}

void Character::SetTeam(vector<Character*>& team)
{
	m_team = team;
}

void Character::SetOpponentTeam(vector<Character*>& opponentTeam)
{
	m_opponentTeam = opponentTeam;
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
	//std::cout << "Start turn" << std::endl;
	m_endTurn = false;

	// Reset the waiting type
	m_waitType = WaitState::WT_NORMAL;

	// Check if stun
	if (IsStunned())
	{
		EndTurn();
	}
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
	//std::cout << "End turn" << std::endl;
	m_endTurn = true;

	if (IsStunned())
	{
		ProcessStun();
	}
}

bool Character::GetEndTurn()
{
	return m_endTurn;
}
