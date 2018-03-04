#include "Enemy.h"
#include "EnemyBullet.h"

Enemy::Enemy(void)
{
	this->type = ObjectType::Enemy;

	// トラスフォーム初期化
	this->transform.position = transform.position;
	this->transform.setRotation(transform.getRotation());
	this->transform.scale = transform.scale;

	// モデル初期化
	this->model = AddComponent<StaticModel>("enemy");

	// コライダー初期化
	this->collider = AddComponent<SphereCollider>();

	// 影初期化
	this->shadow = new Shadow(this);
	this->shadow->transform.scale = 5.0f*Vector3::one;

	// AttackTarget初期化
	this->uihp->offset_y = 8.0f;
	this->uihp->SetOpacity(0.0f);
	this->damage_timer.Reset(0.4f);

	// 他初期化
	this->target = NULL;
	this->speed = 1.0f;
	this->shoot_distance = 0.0f;
	this->state = State::MoveControl;

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
	// ターゲットに向かって移動
	case State::MoveControl:
		Move();
		if (IsInShootRange())
		{
			timer.Reset(0.7f);
			state = State::Shoot;
		}
		break;

	// ターゲットに射撃
	case State::Shoot:
		if (IsInShootRange())
			Shoot();
		else
			state = State::MoveControl;
		break;

	// フェイトアウト
	case State::FadeOut:
		if (!timer.TimeUp())
			FadeOut();
		else
			this->Destroy();
		break;
	}

	timer++;
	damage_timer++;
}

void Enemy::Uninit(void)
{
	this->shadow->Destroy();
	this->uihp->Destroy();
}

void Enemy::Move(void)
{
	if (!IsVaildTarget())
		return;

	Vector3 EtoM = ((*target)->GetAtkPos(this) - this->transform.position).normalized();

	this->transform.position += EtoM * speed * Time::DeltaTime();
	this->transform.lookAt(&(*target)->transform);

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
		bullet->transform.position.y = 2.0f;
		bullet->transform.setFront(this->transform.getFront());

		timer.Reset();
	}
}

bool Enemy::IsInShootRange(void)
{
	if (!IsVaildTarget())
		return false;

	return (this->transform.position - (*this->target)->GetAtkPos(this)).sqrLength() <= this->shoot_distance*this->shoot_distance;
}

void Enemy::FadeOut(void)
{
	float opacity = 1.0f - timer.Progress();
	for (int i = 0; i < (int)this->model->numMaterial; i++)
	{
		this->model->pMaterials[i].MatD3D.Diffuse.a = opacity;
		this->uihp->SetOpacity(opacity);
		this->shadow->SetOpacity(opacity);
	}
}

bool Enemy::IsVaildTarget(void)
{
	if (this->target == nullptr)
		return false;

	if ((*this->target)->GetHp() <= 0)
		return false;

	return true;
}
