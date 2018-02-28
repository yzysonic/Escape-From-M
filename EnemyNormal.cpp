#include "EnemyNormal.h"
#include "EnemyRare.h"
#include "EnemyBullet.h"

EnemyNormal::EnemyNormal(void)
{
	for (int i = 0;i < ENEMYNORMAL_MAX;i++)
	{
		this->AddComponent<RectPolygon>("player");

		//RectPolygon* poly = this->GetComponent<RectPolygon>();

		this->transform.setRotation(0.0f, 0.0f, 0.0f);
		this->transform.position = Vector3(0.0f, 0.0f, 0.0f);
		this->target = NULL;
	}
}

void EnemyNormal::Update(void)
{
	Vector3 EtoR;

	EtoR = (target->transform.position - this->transform.position).normalized();
	
	this->transform.position += EtoR;

	if (GetKeyboardTrigger(DIK_K))
	{
		new EnemyBullet;
	}

	if (target != NULL)
	{
		//PtoE = GetPositionModel() - this->transform.position;
		//D3DXVec3Normalize(&PtoE, &PtoE);
		//this->transform.position += PtoE;
	}
}