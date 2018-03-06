#pragma once
#include "Core\Core.h"
#include "PlayerBullet.h"

class PlayerBulletLong : public PlayerBullet
{
public:
	static constexpr float LifeTime = 5.0f;
	static constexpr float Speed = 15.0f;

	PlayerBulletLong(Transform transform, int atk);
	void Update(void) override;
};