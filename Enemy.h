#pragma once
#include "Core/Core.h"
#include "UIHP.h"
#include "AttackTarget.h"
#include "Shadow.h"

class Enemy : public AttackTarget
{
public:
	enum class State
	{
		MoveControl,
		Shoot,
		FadeOut
	} state;

	AttackTarget** target;
	float shoot_distance;

	Enemy(void);
	virtual void Update(void) override;
	void Uninit(void) override;
	void Move(void);
	void SetScale(float value);
	void Shoot(void);

protected:
	float speed;
	int element_num;
	StaticModel* model;
	SphereCollider* collider;
	Shadow* shadow;
	FrameTimer timer;

	bool IsInShootRange(void);
	void FadeOut(void);
	bool IsVaildTarget(void);
	void DropMaterial(void);

};