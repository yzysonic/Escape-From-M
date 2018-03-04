#include "EnemyRare.h"
#include "EnemyBullet.h"

EnemyRare::EnemyRare(void)
{
	this->model = AddComponent<StaticModel>("enemy_rear");
	this->transform.scale = 0.5f * Vector3::one;
	this->collider->radius = 3.0f;
	this->hp = MaxHp;
	this->max_hp = MaxHp;
	this->flag = false;
	this->count = 0;

	this->target = NULL;
	this->timer.Reset(3.0f);

	this->element_num = EnemyRareElementNum;
}

void EnemyRare::Update(void)
{
	switch (state)
	{
	case State::MoveControl:
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
				this->count++;

				if (count != 2)
				{
					flag = false;
				}
				this->timer.Reset();
			}
		}

		if (count == 2)
		{
			this->timer.Reset(0.4f);
			this->state = State::FadeOut;
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
	damage_timer++;
}

void EnemyRare::OnCollision(Object * other)
{
	if (other->type == ObjectType::Bullet)
	{
		this->state = State::Shoot;
		this->Damage(1);
	}
}
