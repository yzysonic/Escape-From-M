#include "EnemyRare.h"
#include "EnemyBullet.h"

int flag = false;
bool use = false;

EnemyRare::EnemyRare(Transform transform) : Enemy(transform)
{
	this->transform.setRotation(0.0f, 0.0f, 0.0f);
	this->transform.position = Vector3(300.0f, 0.0f, 200.0f);
	this->transform.scale = 0.5f * Vector3::one;
	this->collider = AddComponent<SphereCollider>();
	this->collider->radius = 3.0f;
	this->hp = MaxHP;
	this->max_hp = MaxHP;

	this->target = NULL;
	this->timer.Reset(3.0f);
}

void EnemyRare::Update(void)
{
	Vector3 RtoP;

	this->transform.lookAt(&target->transform);

	RtoP = (target->transform.position - this->transform.position);

	if (use == false)
	{
		if (flag == false)
		{
			this->transform.position.x += 10.0f*Time::DeltaTime();

			if (this->timer.TimeUp())
			{
				flag = true;
				this->timer.Reset();
			}
		}

		if (flag == true)
		{
			this->transform.position.x -= 10.0f*Time::DeltaTime();

			if (this->timer.TimeUp())
			{
				flag = false;
				this->timer.Reset();
			}
		}
	}

	if (use == true)
	{
		RtoP = RtoP.normalized();
		this->transform.position += RtoP * speed * Time::DeltaTime();

		if (this->timer.TimeUp())
		{
			EnemyBullet* bullet = new EnemyBullet;
			bullet->dir = RtoP;
			bullet->transform.position = this->transform.position;
			bullet->target = this->target;

			timer.Reset();
		}
	}
	this->timer++;
}

void EnemyRare::OnCollision(Object * other)
{
	if (other->type == ObjectType::Bullet)
	{
		use = true;
		this->Damage(1);
	}
}
