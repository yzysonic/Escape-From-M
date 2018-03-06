#pragma once
#include "Core\Core.h"

class PlayerBullet : public Object
{
public:
	static constexpr float InitSize = 2.0f;

	PlayerBullet(Transform transform, int atk);
	void OnCollision(Object* other) override;
	void OnDraw(void) override;
	void AfterDraw(void) override;

protected:
	int atk;
	FrameTimer timer;
	Billboard* billboard;
	SphereCollider* collider;

};