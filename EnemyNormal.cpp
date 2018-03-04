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
	this->timer.Reset(0.7f);
}

void EnemyNormal::Update(void)
{
	this->transform.lookAt(&target->transform);

	//if (GetKeyboardTrigger(DIK_K))
	//{
		//bullet->transform.setFront(this->transform.getFront());
	//}
	
	if (target != NULL)
	{
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
}

void EnemyNormal::OnCollision(Object * other)
{
	if (other->type == ObjectType::Bullet)
	{
		this->Damage(1);
	}
}
