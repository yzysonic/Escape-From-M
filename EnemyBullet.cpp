#include "EnemyBullet.h"
#include "AttackTarget.h"

Vector3 BulletSpeed; // ‘¬‚³

EnemyBullet::EnemyBullet(void)
{
	this->type = ObjectType::Bullet_E;
	this->AddComponent<Billboard>("bullet_enemy");
	this->collider = AddComponent<SphereCollider>();
	this->collider->radius = 1.0f;
	this->transform.scale = 2.0f * Vector3::one;
	this->timer.Reset(2.0f);
}

void EnemyBullet::Update(void) 
{
	if (this->timer.TimeUp())
		this->Destroy();

	this->transform.position += this->transform.getFront() * ENEMYBULLET_SPEED;
	this->timer++;
}

void EnemyBullet::OnCollision(Object * other)
{
	if (other->type == ObjectType::Player || other->type == ObjectType::EnemyTarget)
	{
		auto target = dynamic_cast<AttackTarget*>(other);
		target->Damage(EnemyAtk);
		this->Destroy();
	}
}
