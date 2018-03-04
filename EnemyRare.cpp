#include "EnemyRare.h"
#include "EnemyBullet.h"

EnemyRare::EnemyRare(void)
{
	this->model = AddComponent<StaticModel>("enemy_rear");
	this->transform.scale = 0.5f * Vector3::one;
	this->collider->radius = 3.0f;
	this->hp = MaxHP;
	this->max_hp = MaxHP;
	this->flag = false;

	this->target = NULL;
	this->timer.Reset(3.0f);
}

void EnemyRare::Update(void)
{
	switch (state)
	{
	case State::Move:
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
		break;

	case State::Shoot:
		Move();
		Shoot();
		break;

	case State::FadeOut:
		if (!timer.TimeUp())
			FadeOut();
		else
		{
			this->Destroy();
			this->uihp->Destroy();
		}
		break;
	}

	timer++;
}

void EnemyRare::OnCollision(Object * other)
{
	if (other->type == ObjectType::Bullet)
	{
		this->state = State::Shoot;
		this->Damage(1);
	}
}
