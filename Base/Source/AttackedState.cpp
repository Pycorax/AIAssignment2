#include "SlackState.h"
#include "RetreatState.h"
#include "KnockOutState.h"

const float AttackedState::S_TIME_TILL_RELAX = 15.f;

AttackedState::AttackedState() : FSMState(), m_relaxTimer(0.f)
{
	m_stateName = "Attacked State";
}


AttackedState::~AttackedState()
{
}

void AttackedState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);
	if (!g)
	{
		return;
	}
	g->SetAttacked(false); // Response is made, change it back to false
	g->SetMoveSpeed(Guard::S_GUARD_ALERT_SPEED);

	// Set up the child state
	if (g->GetKnockedOut()) // If knocked out by attack, knock out state
	{
		setCurrentState(new KnockOutState());
	}
	else // Fail to knock out guard, retreat
	{
		setCurrentState(new RetreatState(g->GetTransform().Translation));
	}
}

void AttackedState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);

	// Get the actual NPC-type pointer
	Guard* npc = dynamic_cast<Guard*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!npc)
	{
		return;
	}
}

void AttackedState::Update(double dt)
{
	// Run the child state
	FSMState::Update(dt);

	// Get the actual NPC-type pointer
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!g)
	{
		return;
	}

	int attackChance = Math::RandIntMinMax(1, 100);
	if (!g->GetKnockedOut() && !g->GetRegainConscious() && g->GetAttacker() && attackChance < 30) // % chance to turn back and attack
	{
		g->attack(g->GetAttacker());
		changeState(new AttackState());
		g->GetView()->SetScale(Vector2(g->GetDefaultViewRadius() * 3.f, g->GetDefaultViewRadius() * 3.f));
		g->UpdateViewPosition();
		return;
	}

	m_relaxTimer += dt;
	if (g->GetAttacked())
	{
		m_relaxTimer = 0.f; // Reset timer if guard gets attacked again
		g->SetAttacked(false);
	}

	if (m_relaxTimer >= S_TIME_TILL_RELAX)
	{
		g->SetMoveSpeed(Guard::S_GUARD_PATROL_SPEED); // Change speed back to normal patrol speed
		changeState(new PatrolState());
		g->SetAttacker(nullptr);
		return; // Break out of this function
	}
}

void AttackedState::Exit(void)
{
}
