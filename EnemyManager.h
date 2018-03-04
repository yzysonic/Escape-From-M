#pragma once
#include "Core\Core.h"
#include "EnemyTarget.h"
#include "EnemyNormal.h"
#include "EnemyBig.h"
#include "EnemyRare.h"

class EnemyManager : public Object
{
public:
	static constexpr float	SwapRadius = 100.0f;
	static constexpr float	SwapInterval = 5.0f;
	static constexpr int	SwapNormalNum = 3;
	static constexpr int	EnemyMax = 15;
	static constexpr float	RearProb = 0.2f;

	EnemyTarget* target1;
	EnemyTarget* target2;

	EnemyManager(void);
	void Update(void) override;
	void SwapNormal(void);
	void SwapRear(void);

private:
	FrameTimer swap_timer;
	int enemy_count;
	EnemyTarget* target_now;
};