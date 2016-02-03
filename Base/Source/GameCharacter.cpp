#include "GameCharacter.h"

// State includes
#include "ActionState.h"
#include "StartTurnState.h"

const float GameCharacter::S_GUARD_DAMAGE_REDUCTION = 0.8f; // Out of 1.f

GameCharacter::GameCharacter()
	: m_guarder(nullptr)
	, m_defending(false)
	, m_nextTarget(nullptr)
{
	probabilities.Reset();
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
	probabilities.Set(attProb, defProb, specProb, passProb);
}

void GameCharacter::Update(double dt)
{
	Character::Update(dt);
}

void GameCharacter::StartTurn()
{
	Character::StartTurn();
	m_defending = false;
	m_guarder = nullptr;
}

void GameCharacter::EndTurn()
{
	Character::EndTurn();
	probabilities.SetDefault();
}

void GameCharacter::Injure(int damage)
{
	if (m_guarder)
	{
		m_guarder->Character::Injure(damage);
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

	if (m_health <= m_maxHealth * S_CRITICAL_HEALTH)
	{
		// Call for support
		RequestSupport();
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
		Character::Stun(turnDuration);
	}
}

void GameCharacter::RequestSupport()
{
	if (m_type == GC_HEALER)
	{
		// Healer will set to heal himself
		m_nextTarget = this;
	}
	else
	{
		vector<MessageListener*> recipents;
		for (vector<Character*>::iterator it = m_team.begin(); it != m_team.end(); ++it)
		{
			Character* c = *it;
			GameCharacter* gc = dynamic_cast<GameCharacter*>(c);
			if (gc)
			{
				if (gc->GetType() == GC_HEALER || gc->GetType() == GC_TANK)
				{
					recipents.push_back(gc);
				}
			}
		}
		sendMessage(Message::MSG_REQUEST_SUPPORT, recipents);
	}
}

void GameCharacter::Guard(Character * guarder)
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

void GameCharacter::SetNextTarget(Character * target)
{
	m_nextTarget = target;
}

Character * GameCharacter::GetNextTarget()
{
	return m_nextTarget;
}

short GameCharacter::GetAttackProbability()
{
	return probabilities.m_attackProbability;
}

short GameCharacter::GetDefendProbability()
{
	return probabilities.m_defaultDefendProbability;
}

short GameCharacter::GetSpecialProbability()
{
	return probabilities.m_specialProbability;
}

short GameCharacter::GetPassProbability()
{
	return probabilities.m_passProbability;
}

void GameCharacter::handleMessage(Message msg)
{
	Character* sender = (Character*)msg.GetSender();
	switch (msg.GetMessage())
	{
	case Message::MSG_REQUEST_SUPPORT:
		{
			if (m_nextTarget)
			{
				GameCharacter* gc = dynamic_cast<GameCharacter*>(m_nextTarget);

				// Already supporting someone
				switch (m_type)
				{
				case GC_HEALER:
					{
						// Healer will heal the person with lower health
						if (gc && gc->GetType() == GC_HEALER)
						{
							// Healer is healing himself
							return;
						}
						if (sender->GetHealth() < m_nextTarget->GetHealth())
						{
							m_nextTarget = sender;
						}
					}
					break;
				case GC_TANK:
					{
						// Tank will guard the person with higher health as healer is healing the person with lower health
						GameCharacter* gcSender = dynamic_cast<GameCharacter*>(sender);
						if (gcSender && gcSender->GetType() == GC_TANK)
						{
							// Tank cannot guard himself
							return;
						}
						if (sender->GetHealth() < m_nextTarget->GetHealth())
						{
							m_nextTarget = sender;
						}
					}
					break;
				}
			}
			else
			{
				m_nextTarget = sender;
			}
		}
		break;
	case Message::MSG_PRIORITY_ATTACK:
		{
		}
		break;
	case Message::MSG_PLAN_TO_STUN:
		{
		}
		break;
	case Message::MSG_GUARDING_SOMEONE:
		{
			// Received by healer
		}
		break;
	case Message::MSG_HEALING_SOMEONE:
		{
			// Received by tank
		}
		break;
	case Message::MSG_MARTYRDOM:
		{
		}
		break;
	case Message::MSG_LAST_WORDS:
		{
		}
		break;
	}
}
