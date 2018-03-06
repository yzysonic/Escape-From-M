#include "UIHP.h"

UIHP::UIHP(Object * owner)
{
	this->owner = &owner->transform;
	this->offset_y = 0.0f;
}

void UIHP::Update(void)
{
	D3DXMATRIX mtxTranslate;
	D3DXMatrixTranslation(&mtxTranslate, this->owner->object->transform.position.x, this->owner->object->transform.position.y, this->owner->object->transform.position.z);

	D3DXVECTOR4 v = *D3DXVec3Transform(&v, &D3DXVECTOR3(0.0f, this->offset_y, 0.0f), &(mtxTranslate*Renderer::GetInstance()->getCamera()->getViewMatrix(false)*Renderer::GetInstance()->getCamera()->getProjectionMatrix(false)));
	Vector3 pos = *((Vector3*)&v);
	pos.x *= 0.5f*SystemParameters::ResolutionX / v.w;
	pos.y *= 0.5f*SystemParameters::ResolutionY / v.w;
	SetPosition(Vector2(pos.x, pos.y));

}
