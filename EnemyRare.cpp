#include "EnemyRare.h"

int flag = false;

EnemyRare::EnemyRare(void)
{
	this->AddComponent<RectPolygon>("player");

	RectPolygon* poly = this->GetComponent<RectPolygon>();
	poly->SetColor(Color(255, 0, 0, 255));

	this->transform.setRotation(0.0f, 0.0f, 0.0f);
	this->transform.position = Vector3(300.0f, 0.0f, 200.0f);

	this->target = NULL;
	this->timer.Reset(3.0f);
}

void EnemyRare::Update(void)
{
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

	this->timer++;
}

//D3DXVECTOR3 EnemyRare::GetPositionEnemyRare(void)
//{
//	return this->transform.position;
//}
