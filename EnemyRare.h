#pragma once
#include "Core/Core.h"
#include "Enemy.h"

#define ENEMY_RARE (30)
#define ENEMYRARE_SPEED (1.0f)

class EnemyRare : public Enemy
{
public:
	FrameTimer timer;

	static const int MaxHP = 3;

	EnemyRare(Transform transform);
	void Update(void) override;
	void OnCollision(Object* other) override;
};