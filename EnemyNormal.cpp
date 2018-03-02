#include "EnemyNormal.h"
#include "EnemyRare.h"
#include "EnemyBullet.h"

EnemyNormal::EnemyNormal(Transform transform) : Enemy(transform)
{
	this->collider->radius = 3.0f;
	this->transform.scale = 0.5f * Vector3::one;
	this->speed = ENEMY_SPEED;
	this->hp = MaxHP;
	this->max_hp = MaxHP;
}

void EnemyNormal::Update(void)
{
	this->transform.lookAt(&target->transform);

	if (GetKeyboardTrigger(DIK_K))
	{
		EnemyBullet* bullet = new EnemyBullet;

		bullet->transform.position = this->transform.position;
		bullet->target = this->target;
		//bullet->transform.setFront(this->transform.getFront());
	}
	
	Move();

}

void EnemyNormal::OnCollision(Object * other)
{
	if (other->type == ObjectType::Bullet)
	{
		this->Damage(1);
	}
}
