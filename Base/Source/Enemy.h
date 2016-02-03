#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Character.h"

class Enemy : public Character
{
	/*
	*		State Classes Friend Declarations
	* States should be able to access this class's properties
	*/
	friend class EnemyActionState;
	friend class EnemyAttackActionState;

public:
	Enemy();
	~Enemy();

protected:
	void Attack();
};

#endif