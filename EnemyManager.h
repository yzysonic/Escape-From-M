#pragma once
#include "Core\Core.h"
#include "AttackTarget.h"
#include "EnemyNormal.h"
#include "EnemyBig.h"
#include "EnemyRare.h"

class EnemyManager : public Object
{
public:
	static constexpr float	SwapRadius = 150.0f;
	static constexpr float	SwapInterval = 5.0f;
	static constexpr int	SwapNormalNum = 3;
	static constexpr int	EnemyMax = 15;
	static constexpr float	RearProb = 0.3f;

	AttackTarget* target1;
	AttackTarget* target2;
	AttackTarget* target3;

	EnemyManager(void);
	void Update(void) override;
	void SwapNormal(void);
	void SwapRear(void);

private:
	FrameTimer swap_timer;
	FrameTimer check_timer;
	int enemy_count;
	AttackTarget* target_now;
};