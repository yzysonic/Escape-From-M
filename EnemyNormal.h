#pragma once
#include "Core/Core.h"

#define ENEMYNORMAL_MAX (70)
#define ENEMY_SPEED (0.1f)

class EnemyNormal : public Object
{
public:
	Object* target;

	EnemyNormal(void);
	void Update(void) override;

};