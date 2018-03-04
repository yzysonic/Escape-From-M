#include "EnemyBullet.h"

Vector3 BulletSpeed; // ‘¬‚³

EnemyBullet::EnemyBullet(void)
{
	this->AddComponent<Billboard>("bullet_enemy");
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
