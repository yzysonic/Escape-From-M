#pragma once
#include "Core/Core.h"
#include "UIHP.h"

class Enemy : public Object
{
public:
	Object* target;

	Enemy(Transform transform);
	void Move(void);
	void Damage(int point);
	void SetScale(float value);

protected:
	int hp;
	int max_hp;
	float speed;
	UIHP* uihp;
	StaticModel* model;
	SphereCollider* collider;

};