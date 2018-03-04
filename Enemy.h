#pragma once
#include "Core/Core.h"
#include "UIHP.h"
#include "EnemyTarget.h"

class Enemy : public Object
{
public:
	enum class State
	{
		Move,
		Shoot,
		FadeOut
	} state;

	EnemyTarget* target;
	float shoot_distance;
	Event event_death;

	Enemy(void);
	virtual void Update(void) override;
	void Move(void);
	void Damage(int point);
	void SetScale(float value);
	void Shoot(void);

protected:
	int hp;
	int max_hp;
	float speed;
	UIHP* uihp;
	StaticModel* model;
	SphereCollider* collider;
	FrameTimer timer;

	bool IsInShootRange(void);
	void FadeOut(void);

};