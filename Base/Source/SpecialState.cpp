#include "SpecialState.h"

SpecialState::SpecialState(Character* target) : FSMState(), m_target(target)
{
	m_stateName = "Special state";
}


SpecialState::~SpecialState()
{
}

void SpecialState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);

	// Get the actual NPC-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	// Set up the child state
}

void SpecialState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);

	// Get the actual NPC-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}
}

void SpecialState::Update(double dt)
{
	// Pause state update for a duration
	if (m_stateTimer < S_MAX_STATE_TIME)
	{
		m_stateTimer += dt;
		return;
	}
	else
	{
		m_stateTimer = 0.f;
	}

	FSMState::Update(dt);

	// Get the actual NPC-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	// Determine which character
	if (m_target)
	{
		switch (c->GetType())
		{
		case GameCharacter::GC_HEALER:
			{
				m_target->Heal(Math::RandIntMinMax(10, 20));
			}
			break;
		case GameCharacter::GC_RANGER:
			{
				c->sendMessage(Message::MSG_PRIORITY_ATTACK);
			}
			break;
		case GameCharacter::GC_TANK:
			{
				GameCharacter* gc = dynamic_cast<GameCharacter*>(m_target);
				if (gc)
				{
					gc->Guard(c);
				}
			}
			break;
		case GameCharacter::GC_WARRIOR:
			{
				c->sendMessage(Message::MSG_PLAN_TO_STUN);
				m_target->Stun(1);
				c->Stun(1);
			}
			break;
		}
	}
	else
	{

	}

	c->SetNextTarget(nullptr);
	c->EndTurn();
}

void SpecialState::Exit(void)
{
}
