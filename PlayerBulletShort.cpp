#include "PlayerBulletShort.h"

PlayerBulletShort::PlayerBulletShort(Transform transform, int atk, float wait_time) : PlayerBullet(transform, atk)
{
	this->last_pos = transform.position;
	this->target_pos = this->last_pos + this->transform.getFront()*7.0f;
	this->state = 0;
	this->syn_timer.Reset(wait_time + 0.1f);
}

void PlayerBulletShort::Update(void)
{
	switch (this->state)
	{
	case 0:
		
		this->transform.position.x = Ease::CircOut(this->last_pos.x, target_pos.x, this->timer.Progress());
		this->transform.position.z = Ease::CircOut(this->last_pos.z, target_pos.z, this->timer.Progress());
		if (this->timer.TimeUp())
		{
			this->transform.position = this->target_pos;
			this->state = 1;
		}
		break;

	case 1:
		this->transform.position += this->transform.getFront()*Time::DeltaTime()*3.0f;
		this->syn_timer++;
		if (this->syn_timer.TimeUp())
		{
			this->last_pos = this->transform.position;
			this->target_pos = this->last_pos + this->transform.getFront()*10.0f;
			this->state = 2;
			this->timer.Reset(0.3f);
		}
		break;

	case 2:
		this->transform.position.x = Ease::CircOut(this->last_pos.x, target_pos.x, this->timer.Progress());
		this->transform.position.z = Ease::CircOut(this->last_pos.z, target_pos.z, this->timer.Progress());
		this->transform.scale = Vector3::Lerp(InitSize*Vector3::one, EndSize*Vector3::one, this->timer.Progress());
		this->collider->radius = 0.5f*this->transform.scale.x;
		this->billboard->SetOpacity(1.0f-this->timer.Progress());
		if (this->timer.TimeUp())
			this->Destroy();
		break;

	}
	this->timer++;
}