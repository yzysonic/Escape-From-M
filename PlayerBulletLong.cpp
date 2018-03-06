#include "PlayerBulletLong.h"

PlayerBulletLong::PlayerBulletLong(Transform transform, int atk) : PlayerBullet(transform, atk)
{
	this->timer.Reset(LifeTime);
	this->transform.scale = Vector3::zero;
}

void PlayerBulletLong::Update(void)
{
	if (this->timer.TimeUp())
		this->Destroy();

	this->transform.position += this->transform.getFront()*70.0f*Time::DeltaTime();
	this->transform.scale = Vector3::Lerp(this->transform.scale, Vector3::one*this->InitSize, 0.07f);
	
	this->timer++;
}
