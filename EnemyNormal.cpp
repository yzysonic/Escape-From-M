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

void EnemyNormal::Update(void)
{
	switch (state)
	{
	case State::Move:
		Move();
		if (IsInShootRange()) 
		{
			timer.Reset(0.7f);
			state = State::Shoot;
		}
		break;

	case State::Shoot:
		if (IsInShootRange())
			Shoot();
		else
			state = State::Move;
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

void EnemyNormal::OnCollision(Object * other)
{
	if (other->type == ObjectType::Bullet)
	{
		this->Damage(1);
	}
}

void EnemyNormal::Shoot(void)
{
	if (timer.TimeUp())
	{
		EnemyBullet* bullet = new EnemyBullet;

		bullet->transform.position = this->transform.position;
		bullet->transform.setFront(this->transform.getFront());

		timer.Reset();
	}
}
