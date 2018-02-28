#pragma once
#include "Core/Core.h"

#define BULLET_MAX	(100)

class EnemyBullet : public Object
{
public:
	Object* target;

	EnemyBullet(void);
	void Update(void) override;
	void SetBullet(Vector3 pos, Vector3 speed);

};