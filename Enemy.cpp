#include "Enemy.h"
#include "EnemyBullet.h"

Enemy::Enemy(void)
{
	this->transform.position = transform.position;
	this->transform.setRotation(transform.getRotation());
	this->transform.scale = transform.scale;
	this->model = AddComponent<StaticModel>("enemy");
	this->collider = AddComponent<SphereCollider>();
	this->type = ObjectType::Enemy;
	this->target = NULL;
	this->hp = 0;
	this->max_hp = 1;
	this->speed = 1.0f;
	this->uihp = new UIHP(this, 15.0f);
	this->shoot_distance = 0.0f;
	this->uihp->SetOpacity(0.0f);
	this->state = State::Move;

	this->event_death += [&] {
		timer.Reset(1.0f);
		this->collider->SetActive(false);
		this->state = State::FadeOut;
	};

	SetScale(1.0f);

}

void Enemy::Update(void)
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

void Enemy::Move(void)
{
	if (target != NULL)
	{
		Vector3 EtoM;
		float length;

		EtoM = (target->GetAtkPos(this) - this->transform.position);
		length = EtoM.length();

		this->transform.lookAt(&target->transform);

		EtoM = EtoM.normalized();

		this->transform.position += EtoM * speed * Time::DeltaTime();
	}

}

void Enemy::Damage(int point)
{
	if (this->hp == 0)
		return;

	this->uihp->SetOpacity(1.0f);

	this->hp -= point;
	this->uihp->SetPercent((float)this->hp / max_hp);

	if (this->hp == 0)
		this->event_death();

}

void Enemy::SetScale(float value)
{
	this->transform.scale = value * Vector3::one;
	this->collider->radius = value * 0.5f;
}

void Enemy::Shoot(void)
{
	if (timer.TimeUp())
	{
		EnemyBullet* bullet = new EnemyBullet;

		bullet->transform.position = this->transform.position;
		bullet->transform.setFront(this->transform.getFront());

		timer.Reset();
	}
}

bool Enemy::IsInShootRange(void)
{
	if (this->target == nullptr)
		return false;

	return (this->transform.position - this->target->GetAtkPos(this)).sqrLength() <= this->shoot_distance*this->shoot_distance;
}

void Enemy::FadeOut(void)
{
	float opacity = 1.0f - timer.Progress();
	for (int i = 0; i < this->model->numMaterial; i++)
	{
		this->model->pMaterials[i].MatD3D.Diffuse.a = opacity;
		this->uihp->SetOpacity(opacity);
	}
}
