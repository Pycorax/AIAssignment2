#include "GameCharacter.h"
#include "ActionState.h"
#include "StartTurnState.h"

const float GameCharacter::S_GUARD_DAMAGE_REDUCTION = 0.8f; // Out of 1.f

GameCharacter::GameCharacter()
	: m_guarder(nullptr)
	, m_defending(false)
{
}


GameCharacter::~GameCharacter()
{
}

void GameCharacter::Init(GAME_CHARACTER_TYPE type, int maxHealth, int attack, Mesh * mesh)
{
	m_type = type;
	Character::Init(maxHealth, attack, mesh);
	setCurrentState(new WaitState());
}

void GameCharacter::InitProbability(short attProb, short defProb, short specProb, short passProb)
{
	m_attackProbability = attProb;
	m_defendProbability = defProb;
	m_specialProbability = specProb;
	m_passProbability = passProb;
}

void GameCharacter::Update(double dt)
{
	Character::Update(dt);
}

void GameCharacter::StartTurn()
{
	Character::StartTurn();
}

void GameCharacter::Injure(int damage)
{
	if (m_guarder)
	{
		m_guarder->Character::Injure(damage);
		return;
	}
	else
	{
		if (m_defending)
		{
			Character::Injure(damage * S_GUARD_DAMAGE_REDUCTION);
		}
		else
		{
			Character::Injure(damage);
		}
	}
}

void GameCharacter::Stun(int turnDuration)
{
	if (m_guarder)
	{
		m_guarder->Character::Stun(turnDuration);
	}
	else
	{
		m_guarder->Character::Stun(turnDuration);
	}
}

void GameCharacter::SetGuarder(Character * guarder)
{
	m_guarder = guarder;
}

Character * GameCharacter::GetGuarder()
{
	return m_guarder;
}

void GameCharacter::Defend()
{
	m_defending = true;
}

bool GameCharacter::GetDefend()
{
	return m_defending;
}

void GameCharacter::SetType(GAME_CHARACTER_TYPE type)
{
	m_type = type;
}

GameCharacter::GAME_CHARACTER_TYPE GameCharacter::GetType()
{
	return m_type;
}

short GameCharacter::GetAttackProbability()
{
	return m_attackProbability;
}

short GameCharacter::GetDefendProbability()
{
	return m_defendProbability;
}

short GameCharacter::GetSpecialProbability()
{
	return m_specialProbability;
}

short GameCharacter::GetPassProbability()
{
	return m_passProbability;
}

void GameCharacter::handleMessage(Message msg)
{
}
