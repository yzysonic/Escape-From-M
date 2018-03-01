#include "EnemyNormal.h"
#include "EnemyRare.h"
#include "EnemyBullet.h"

EnemyNormal::EnemyNormal(void)
{
	AddComponent<StaticModel>("enemy");
	AddComponent<SphereCollider>()->radius = 2.0f;
	this->type = ObjectType::Enemy;
	this->transform.scale = 0.5f * Vector3::one;
	this->target = NULL;
	this->hp = MaxHP;
	this->uihp = new UIHP(this, 7.0f);
	this->uihp->SetOpacity(0.0f);
}

void EnemyNormal::Update(void)
{

	if (GetKeyboardTrigger(DIK_K))
	{
		new EnemyBullet;
	}

	if (target != NULL)
	{
		Vector3 EtoR;

		EtoR = (target->transform.position - this->transform.position).normalized();

		this->transform.position += EtoR;

		//PtoE = GetPositionModel() - this->transform.position;
		//D3DXVec3Normalize(&PtoE, &PtoE);
		//this->transform.position += PtoE;
	}
}

void EnemyNormal::OnCollision(Object * other)
{
	if (other->type == ObjectType::Bullet)
	{
		this->Damage(1);
	}
}

void EnemyNormal::Damage(int point)
{
	if (this->hp == 0)
		return;

	this->uihp->SetOpacity(1.0f);

	this->hp -= point;
	this->uihp->SetPercent((float)this->hp / MaxHP);
}
