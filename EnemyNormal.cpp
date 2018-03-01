#include "EnemyNormal.h"
#include "EnemyRare.h"
#include "EnemyBullet.h"

EnemyNormal::EnemyNormal(void)
{
	AddComponent<StaticModel>("enemy");

	this->transform.scale = 0.5f * Vector3::one;
	this->target = NULL;
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