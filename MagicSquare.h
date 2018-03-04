#pragma once
#include "Core/Core.h"
#include "EnemyTarget.h"

class MagicSquare : public EnemyTarget
{
public:
	static constexpr int MaxHP = 30;
	static constexpr float Radius = 25.0f;
	float rotation_speed;		// ‰ñ“]‚Ì‘¬‚³
	float color_change_speed;	// FØ‘Ö‚Ì‘¬‚³

	MagicSquare(void);
	void Update(void) override;
	void OnDraw(void) override;
	void AfterDraw(void) override;
	int GetHp(void) override;
	Vector3 GetAtkPos(Object* enemy) override;

private:
	int hp;
	FrameTimer timer;
};