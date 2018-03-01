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
	this->transform.lookAt(&target->transform);

	if (GetKeyboardTrigger(DIK_K))
	{
		EnemyBullet* bullet = new EnemyBullet;

		bullet->transform.position = this->transform.position;

		//bullet->transform.setFront(this->transform.getFront());
	}

	if (target != NULL)
	{
		Vector3 EtoM;
		float length;
		
		EtoM = (target->transform.position - this->transform.position);
		length = EtoM.length();
		EtoM = EtoM.normalized();

		this->transform.position += EtoM * ENEMY_SPEED;

		if (length <= 10.0f)
		{
			this->transform.position -= EtoM * ENEMY_SPEED;

		}

		//PtoE = GetPositionModel() - this->transform.position;
		//D3DXVec3Normalize(&PtoE, &PtoE);
		//this->transform.position += PtoE;
	}
}