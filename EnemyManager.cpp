#include "EnemyManager.h"

EnemyManager::EnemyManager(void)
{
	this->swap_timer.Reset(SwapInterval);
	this->check_timer.Reset(0.5f);
	this->enemy_count = 0;
	this->target1 = nullptr;
	this->target2 = nullptr;
	this->target3 = nullptr;
	this->target_now = nullptr;
}

void EnemyManager::Update(void)
{
	if (this->check_timer.TimeUp())
	{
		UpdateTarget();
		this->check_timer.Reset();
	}
	

	if (this->swap_timer.TimeUp())
	{ 
		SwapRear();
		SwapNormal();
		this->swap_timer.Reset();
	}

	this->swap_timer++;
	this->check_timer++;
}

void EnemyManager::SwapNormal(void)
{
	float angle = Randomf(0.0f, 2.0f*PI);
	for (int i = 0; i < SwapNormalNum; i++)
	{
		auto enemy = new EnemyNormal;
		enemy->target = &this->target_now;
		enemy->transform.position.x = SwapRadius * cosf(angle+Deg2Rad(5.0f)*i);
		enemy->transform.position.z = SwapRadius * sinf(angle+Deg2Rad(5.0f)*i);
	}
}

void EnemyManager::SwapRear(void)
{
	if (Randomf(0.0f, 1.0f) > RearProb)
		return;

	float angle = Randomf(0.0f, 2.0f*PI);
	auto enemy = new EnemyRare;
	enemy->target = &this->target3;
	enemy->transform.position.x = SwapRadius * cosf(angle);
	enemy->transform.position.z = SwapRadius * sinf(angle);

}

void EnemyManager::UpdateTarget(void)
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
				this->target_now = this->target2;
		}
	}

}
