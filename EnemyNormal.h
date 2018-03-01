#pragma once
#include "Core/Core.h"
#include "UIHP.h"

#define ENEMYNORMAL_MAX (70)
#define ENEMY_SPEED (0.1f)

class EnemyNormal : public Object
{
public:
	static const int MaxHP = 3;
	Object* target;

	EnemyNormal(void);
	void Update(void) override;
	void OnCollision(Object* other) override;
	void Damage(int point);

private:
	int hp;
	UIHP* uihp;
};