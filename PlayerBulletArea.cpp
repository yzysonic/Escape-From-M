#include "PlayerBulletArea.h"

PlayerBulletArea::PlayerBulletArea(Transform transform, int atk, float radius) : PlayerBullet(transform, atk)
{
	this->center = transform.position;
	this->radius = radius;
	this->theta = transform.getRotation().y;
	this->transform.scale = Vector3::zero;
	this->state = 0;
	this->launch_timer.Reset(0.2f);
	this->timer.Reset(Randomf(0.5f, 0.6f));
}

void PlayerBulletArea::Update(void)
{
	switch (this->state)
	{
	case 0:
	{
		// アニメーション計算
		float radius = Lerpf(this->radius*0.1f, this->radius, this->launch_timer.Progress());
		float theta = this->theta + this->timer.Elapsed();

		this->transform.position.x = radius*cosf(theta);
		this->transform.position.z = radius*sinf(theta);
		this->transform.position.y = Lerpf(-3.0f, 0.0f, this->launch_timer.Progress());
		this->transform.position += this->center;
		this->transform.scale = Vector3::Lerp(this->transform.scale, Vector3::one*this->InitSize, 0.07f);

		this->billboard->SetOpacity(Lerpf(0.0f, 1.0f, this->launch_timer.Progress()));

		// タイマーの更新
		this->launch_timer++;
		this->timer++;

		// 状態遷移
		if (this->timer.TimeUp())
			this->state = 1;

		break;
	}

	case 1:
		this->transform.position.y += -70.0f*Time::DeltaTime();

		if (this->transform.position.y < -2.0f)
			this->Destroy();

		break;
	}
}
