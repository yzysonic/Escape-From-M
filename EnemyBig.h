#pragma once
#include "Core/Core.h"
#include "Enemy.h"

#define ENEMYBIG_SPEED 5.0f;

class EnemyBig : public Enemy
{
public:
	static const int MaxHP = 10;

	FrameTimer timer;
	EnemyBig(Transform transform);
	void Update(void) override;
	void OnCollision(Object* other) override;
};