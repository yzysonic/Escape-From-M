#pragma once
#include "Core/Core.h"

#define BULLET_MAX	(100)
#define ENEMYBULLET_SPEED (0.5f)

class EnemyBullet : public Object
{
public:
	Object* target;
	Vector3 dir;

	EnemyBullet(void);
	void Update(void) override;

};