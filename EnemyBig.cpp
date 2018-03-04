#include "EnemyBig.h"
#include "EnemyBullet.h"

EnemyBig::EnemyBig(Transform transform) : Enemy(transform)
{
	this->collider->radius = 3.0f;
	this->transform.scale = 1.0f * Vector3::one;
	this->speed = ENEMYBIG_SPEED;
	this->hp = MaxHP;
	this->max_hp = MaxHP;
	this->timer.Reset(0.7f);
}

void EnemyBig::Update(void)
{
	this->transform.lookAt(&target->transform);

	Vector3 EtoM;
	float length;

	EtoM = (target->transform.position - this->transform.position);
	length = EtoM.length();
	EtoM = EtoM.normalized();

	// çUåÇ
	if (length <= 10.0f)
	{
		if (this->timer.TimeUp())
		{
			EnemyBullet* bullet = new EnemyBullet;
			bullet->dir = EtoM;
			bullet->transform.position = this->transform.position;
			bullet->target = this->target;
			timer.Reset();
		}
		timer++;

	}
	// à⁄ìÆ
	else
	{
		this->transform.position += EtoM * speed * Time::DeltaTime();
	}
}

void EnemyBig::OnCollision(Object * other)
{
	if (other->type == ObjectType::Bullet)
	{
		this->Damage(1);
	}
}
