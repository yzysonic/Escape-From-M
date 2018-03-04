#pragma once
#include "Core/Core.h"

#define BULLET_MAX	(100)
#define ENEMYBULLET_SPEED (0.5f)
#define EnemyAtk (1)

class EnemyBullet : public Object
{
public:
	EnemyBullet(void);
	void Update(void) override;
	void OnCollision(Object* other) override;

private:
	FrameTimer timer;
	SphereCollider* collider;
};