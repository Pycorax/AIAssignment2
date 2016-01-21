#include "CChar.h"

DeprecatedCharacter::DeprecatedCharacter(void)
	: m_health(0)
	, m_maxHealth(0)
	, m_animMesh(NULL)
	, m_lookDir(Vector2::ZERO_VECTOR)
	, m_active(false)
	, m_moveSpeed(0)
{
}

DeprecatedCharacter::~DeprecatedCharacter(void)
{
}

void DeprecatedCharacter::Init(bool active, int health, Vector2 dir, Mesh* mesh,int moveSpeed)
{
	this->m_active							= active;
	this->m__mesh							= mesh;
	this->m_active							= active;
	this->m_maxHealth = this->m_health		= health;
	this->m_lookDir							= dir;
	this->m_animMesh						= mesh;
	this->m_moveSpeed						= moveSpeed;
}

void DeprecatedCharacter::Update()
{
}

void DeprecatedCharacter::SetHealth(int health)
{
	this->m_health = health;
}
void DeprecatedCharacter::SetMaxHealth(int health)
{
	this->m_maxHealth = health;
}

void DeprecatedCharacter::AddToHealth(int health_plus)
{
	this->m_health += health_plus;
}

void DeprecatedCharacter::SetLookDir(Vector2 dir)
{
	this->m_lookDir = dir;
}
void DeprecatedCharacter::SetMoveSpeed(int moveSpeed)
{
	this->m_moveSpeed = moveSpeed;
}

void DeprecatedCharacter::SetAnimMesh(Mesh* mesh)
{
	this->m_animMesh = mesh;
}
void DeprecatedCharacter::SetActive(bool active)
{
	this->m_active = active;
}

// === Get functions ===
int DeprecatedCharacter::GetHealth(void)const
{
	return this->m_health;
}
int DeprecatedCharacter::GetMaxHealth(void)const
{
	return this->m_maxHealth;
}

Vector2 DeprecatedCharacter::GetLookDir(void)const
{
	return this->m_lookDir;
}
int DeprecatedCharacter::GetMoveSpeed(void) const
{
	return this->m_moveSpeed;
}

Mesh* DeprecatedCharacter::GetAnimMesh(void)const
{
	return this->m_animMesh;
}
bool DeprecatedCharacter::GetActive(void) const
{
	return this->m_active;
}

void DeprecatedCharacter::updateScreenPos(Vector2 pos)
{
	m_transforms.Translation = pos;
}

void DeprecatedCharacter::SpottedTarget(Vector2 pos)
{
	
}