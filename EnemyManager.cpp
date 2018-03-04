#include "EnemyManager.h"

EnemyManager::EnemyManager(void)
{
	this->swap_timer.Reset(SwapInterval);
	this->enemy_count = 0;
	this->target1 = nullptr;
	this->target2 = nullptr;
	this->target_now = nullptr;
}

void EnemyManager::Update(void)
{
	if (this->swap_timer.TimeUp())
	{ 
		if (this->target1)
		{
			if (this->target1->GetHp() > 0)
			{
				this->target_now = this->target1;
			}
			else if (this->target2)
			{
				if (this->target2->GetHp() > 0)
					this->target_now = this->target_now;
				else
					this->target_now = nullptr;
			}
		}
		//SwapRear();
		SwapNormal();
		this->swap_timer.Reset();
	}
	this->swap_timer++;
}

void EnemyManager::SwapNormal(void)
{
	float angle = Randomf(0.0f, 2.0f*PI);
	for (int i = 0; i < SwapNormalNum; i++)
	{
		auto enemy = new EnemyNormal;
		enemy->target = this->target_now;
		enemy->transform.position.x = SwapRadius * cosf(angle+Deg2Rad(5.0f)*i);
		enemy->transform.position.z = SwapRadius * sinf(angle+Deg2Rad(5.0f)*i);
	}
}

void EnemyManager::SwapRear(void)
{
	if (Randomf(0.0f, 1.0f) > RearProb)
		return;

	new EnemyRare;
}
