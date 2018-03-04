#pragma once
#include "Core/Core.h"
#include "Enemy.h"

#define ENEMY_RARE (30)
#define ENEMYRARE_SPEED (1.0f)
#define EnemyRareElementNum (10);

class EnemyRare : public Enemy
{
public:
	static const int MaxHp = 3;
	bool flag;
	int count;

	EnemyRare(void);
	void Update(void) override;
	void OnCollision(Object* other) override;
};