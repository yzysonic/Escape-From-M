#pragma once
#include "Core/Core.h"
#include "EnemyTarget.h"

class MagicSquare : public EnemyTarget
{
public:
	static constexpr int MaxHP = 30;
	static constexpr float Radius = 25.0f;
	float rotation_speed;		// 回転の速さ
	float color_change_speed;	// 色切替の速さ

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