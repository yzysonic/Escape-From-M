#pragma once
#include "Core\Core.h"
#include "PlayerBullet.h"

class PlayerBulletShort : public PlayerBullet
{
public:
	static constexpr float EndSize = 6.0f;

	PlayerBulletShort(Transform transform, int atk, float wait_time);
	void Update(void) override;

private:
	int state;
	Vector3 last_pos;
	Vector3 target_pos;
	FrameTimer syn_timer;
};