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
	probabilities.Init(attProb, defProb, specProb, passProb);
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
	m_bonusAttack = 0;
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
		if (IsAlive())
		{
			// Call for support
			RequestSupport();
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

string GameCharacter::GetName(void) const
{
	switch (m_type)
	{
	case GC_HEALER:
	{
		return "Healer";
	}
	break;
	case GC_TANK:
	{
		return "Tank";
	}
	break;
	case GC_WARRIOR:
	{
		return "Warrior";
	}
	break;
	case GC_RANGER:
	{
		return "Ranger";
	}
	break;
	}
}

void GameCharacter::handleMessage(Message msg)
{
	if (!IsAlive())
	{
		return;
	}
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
			probabilities.m_attackProbability += 30;
		}
		break;
	case Message::MSG_PLAN_TO_STUN:
		{
			probabilities.m_defendProbability = 0;
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
			m_bonusAttack = m_attack * 0.3f;
		}
		break;
	case Message::MSG_DEATH:
		{
			if (m_type == GC_RANGER || m_type == GC_WARRIOR)
			{
				GameCharacter* dead = dynamic_cast<GameCharacter*>(sender);
				if (dead->GetType() == GC_HEALER && !containsMessage(Message::MSG_REPLACE_HEALER))
				{
					// Replace the dead
					replaceDead(dead);

					// Inform that he is replacing
					sendMessage(Message::MSG_REPLACE_HEALER);
				}
				else if (dead->GetType() == GC_TANK && !containsMessage(Message::MSG_REPLACE_TANK))
				{
					// Replace the dead
					replaceDead(dead);

					// Inform that he is replacing
					sendMessage(Message::MSG_REPLACE_TANK);
				}
			}
		}
		break;
	case Message::MSG_LAST_WORDS:
		{
			m_bonusAttack = -(m_attack * 0.3f);
		}
		break;

	case Message::MSG_REPLACE_HEALER:
		break;
	case Message::MSG_REPLACE_TANK:
		break;
	}
}

void GameCharacter::replaceDead(GameCharacter * dead)
{
	if (dead)
	{
		// Set our current type to the other's type
		m_type = dead->GetType();
		// Get the dead's mesh
		m__mesh = dead->GetMesh();
	}
}
