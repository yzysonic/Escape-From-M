#include "EnemyBig.h"
#include "EnemyBullet.h"

EnemyBig::EnemyBig(void)
{
	this->collider->radius = 3.0f;
	this->transform.scale = 1.0f * Vector3::one;
	this->speed = ENEMYBIG_SPEED;
	this->hp = MaxHp;
	this->max_hp = MaxHp;
	this->timer.Reset(0.7f);
}

void EnemyBig::OnCollision(Object * other)
{
	if (other->type == ObjectType::Bullet)
	{
		this->Damage(1);
	}
}
