#include "EnemyBig.h"

EnemyBig::EnemyBig(void)
{
	this->AddComponent<RectPolygon>("player");

	RectPolygon* poly = this->GetComponent<RectPolygon>();
	poly->SetColor(Color(0, 255, 0, 255));

	this->transform.setRotation(0.0f, 0.0f, 0.0f);
	this->transform.position = Vector3(-200.0f, 0.0f, 0.0f);
	this->transform.scale = Vector3::one * 1.5;
	this->target = NULL;
}

void EnemyBig::Update(void)
{
	Vector3 EtoR;

	EtoR = (target->transform.position - this->transform.position).normalized();

	this->transform.position += EtoR;

	//EtoM =/* GetPositionModel()*/ - this->transform.position;

	//D3DXVec3Normalize(&EtoM, &EtoM);

	//this->transform.position += EtoM;

	//this->transform.position.x += 20.0f * Time::DeltaTime();

	if (target != NULL)
	{
		//PtoE = GetPositionModel() - this->transform.position;
		//D3DXVec3Normalize(&PtoE, &PtoE);
		//this->transform.position += PtoE;
	}
}
