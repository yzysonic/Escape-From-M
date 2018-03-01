#include "EnemyBullet.h"

Vector3 BulletSpeed; // ‘¬‚³

EnemyBullet::EnemyBullet(void)
{
	this->AddComponent<RectPolygon>("bullet_enemy");

	this->transform.scale = 2.0f * Vector3::one;
	this->target = NULL;
}

void EnemyBullet::Update(void)
{
	if (target != NULL)
	{
		Vector3 BtoM;

		BtoM = (target->transform.position - this->transform.position).normalized();

		//this->transform.position += BtoM * ENEMYBULLET_SPEED;
	}
}
