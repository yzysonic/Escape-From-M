#pragma once
#include "Core\Core.h"
#include "EnemyNormal.h"
#include "EnemyBig.h"
#include "EnemyRare.h"

class EnemyManager : public Object
{
public:
	static constexpr float	SwapRangeX = 150.0f;
	static constexpr float	SwapRangeY = 150.0f;
	static constexpr float	SwapInterval = 5.0f;
	static constexpr int	SwapNum = 3;
	static constexpr int	EnemyMax = 15;

	EnemyManager(void);
	void Update(void) override;

private:
	FrameTimer swap_timer;
	int enemy_count;
};