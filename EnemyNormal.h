#pragma once
#include "Core/Core.h"
#include "Enemy.h"

#define ENEMY_SPEED 10.0f;

class EnemyNormal : public Enemy
{
public:
	static const int MaxHP = 3;

	EnemyNormal(Transform transform);
	void Update(void) override;
	void OnCollision(Object* other) override;
};