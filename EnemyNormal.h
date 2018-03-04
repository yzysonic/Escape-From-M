#pragma once
#include "Core/Core.h"
#include "Enemy.h"

#define ENEMY_SPEED 30.0f;

class EnemyNormal : public Enemy
{
public:
	static const int MaxHP = 3;

	EnemyNormal(void);
	void OnCollision(Object* other) override;
};