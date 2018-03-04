#include "EnemyNormal.h"
#include "EnemyRare.h"
#include "EnemyBullet.h"

EnemyNormal::EnemyNormal(void)
{
	this->collider->radius = 3.0f;
	this->transform.scale = 0.5f * Vector3::one;
	this->speed = ENEMY_SPEED;
	this->hp = MaxHP;
	this->max_hp = MaxHP;
	this->shoot_distance = 10.0f;
}

void EnemyNormal::OnCollision(Object * other)
{
	if (other->type == ObjectType::Bullet)
	{
		this->Damage(1);
	}
}

