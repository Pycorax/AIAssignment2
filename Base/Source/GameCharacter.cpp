#include "GameCharacter.h"



GameCharacter::GameCharacter()
	: m_guarder(nullptr)
	, m_defending(false)
{
}


GameCharacter::~GameCharacter()
{
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
