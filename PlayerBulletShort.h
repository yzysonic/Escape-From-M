#pragma once
#include "Core\Core.h"
#include "Shadow.h"

class PlayerBulletShort : public Object
{
public:
	static constexpr float InitSize = 2.0f;
	static constexpr float EndSize = 6.0f;

	PlayerBulletShort(Transform transform, float wait_time, int atk);
	void Update(void) override;
	void OnCollision(Object* other) override;
	void OnDraw(void) override;
	void AfterDraw(void) override;

private:
	int state;
	int atk;
	Vector3 last_pos;
	Vector3 target_pos;
	FrameTimer syn_timer;
	FrameTimer timer;
	Billboard* billboard;
	SphereCollider* collider;
};