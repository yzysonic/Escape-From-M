#pragma once
#include "Core\Core.h"
#include "PlayerBullet.h"

class PlayerBulletArea : public PlayerBullet
{
public:
	PlayerBulletArea(Transform transform, int atk, float radius);
	void Update(void) override;

private:
	FrameTimer launch_timer;
	int state;
	float radius;
	float theta;
	Vector3 center;
};