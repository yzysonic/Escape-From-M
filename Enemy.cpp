#include "Enemy.h"

Enemy::Enemy(Transform transform)
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
	//this->uihp->SetOpacity(0.0f);
	SetScale(1.0f);

}

void Enemy::Move(void)
{
	if (target != NULL)
	{
		Vector3 EtoM;
		float length;

		EtoM = (target->transform.position - this->transform.position);
		length = EtoM.length();

		if (length <= 10.0f)
			return;

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

}

void Enemy::SetScale(float value)
{
	this->transform.scale = value * Vector3::one;
	this->collider->radius = value * 0.5f;
}
