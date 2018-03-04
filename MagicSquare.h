#pragma once
#include "Core/Core.h"
#include "AttackTarget.h"

class MagicSquare : public AttackTarget
{
public:
	static constexpr int MaxHp = 30;
	static constexpr float Radius = 20.0f;
	float rotation_speed;		// ‰ñ“]‚Ì‘¬‚³
	float color_change_speed;	// FØ‘Ö‚Ì‘¬‚³

	MagicSquare(void);
	void Update(void) override;
	void OnDraw(void) override;
	void AfterDraw(void) override;

private:
	FrameTimer effect_timer;
};