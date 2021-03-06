#pragma once
#include "Core/Core.h"
#include "AttackTarget.h"

class MagicSquare : public AttackTarget
{
public:
	static constexpr int MaxHp = 30;
	static constexpr float Radius = 20.0f;
	float rotation_speed;		// 回転の速さ
	float color_change_speed;	// 色切替の速さ

	MagicSquare(void);
	void Update(void) override;
	void OnDraw(void) override;
	void AfterDraw(void) override;

private:
	FrameTimer effect_timer;
};