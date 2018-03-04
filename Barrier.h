#pragma once
#include "Core\Core.h"
#include "EnemyTarget.h"

class Barrier : public EnemyTarget
{
public:
	static constexpr int MaxHP = 20;
	static constexpr float Radius = 24.0f;

	Barrier(void);
	void OnDraw(void) override;
	void AfterDraw(void) override;

private:
	int hp;
	int GetHp(void) override;
	Vector3 GetAtkPos(Object* enemy) override;
};