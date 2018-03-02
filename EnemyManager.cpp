#include "EnemyManager.h"

EnemyManager::EnemyManager(void)
{
	this->swap_timer.Reset(SwapInterval);
	this->enemy_count = 0;
}

void EnemyManager::Update(void)
{
	if (this->swap_timer.TimeUp())
	{



		this->swap_timer.Reset();
	}
}
