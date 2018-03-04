#include "EnemyNormal.h"
#include "EnemyRare.h"
#include "EnemyBullet.h"

EnemyNormal::EnemyNormal(void)
{
	this->collider->radius = 3.0f;
	this->transform.scale = 0.5f * Vector3::one;
	this->speed = ENEMY_SPEED;
	this->hp = MaxHp;
	this->max_hp = MaxHp;
	this->shoot_distance = 10.0f;
}
