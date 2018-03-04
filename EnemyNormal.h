#pragma once
#include "Core/Core.h"
#include "Enemy.h"

#define ENEMY_SPEED 10.0f;
#define EnemyNormalElementNum (3)

class EnemyNormal : public Enemy
{
public:
	static const int MaxHp = 3;

	EnemyNormal(void);
};