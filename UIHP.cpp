#include "UIHP.h"

UIHP::UIHP(Object * owner)
{
	this->base_bar = AddComponent<RectPolygon2D>("none", Layer::UI_00);
	this->base_bar->SetColor(HPBarBaseColor);

	this->obj_main_bar = new Object;
	this->main_bar = this->obj_main_bar->AddComponent<RectPolygon2D>("none", Layer::UI_01);
	this->main_bar->SetColor(HPBarMainColor);

	SetSize(Width, Height);

	this->owner = &owner->transform;
	this->offset_y = 0.0f;
	this->main_bar_offset_x = 0.0f;
}

void UIHP::Update(void)
{
	D3DXMATRIX mtxTranslate;
	D3DXMatrixTranslation(&mtxTranslate, this->owner->object->transform.position.x, this->owner->object->transform.position.y, this->owner->object->transform.position.z);
	D3DXVECTOR4 v = *D3DXVec3Transform(&v, &D3DXVECTOR3(0.0f, this->offset_y, 0.0f), &(mtxTranslate*Renderer::GetInstance()->getCamera()->getViewMatrix(false)*Renderer::GetInstance()->getCamera()->getProjectionMatrix(false)));
	this->transform.position = *((Vector3*)&v);
	this->transform.position.x *= 0.5f*SystemParameters::ResolutionX / v.w;
	this->transform.position.y *= 0.5f*SystemParameters::ResolutionY / v.w;
	this->transform.position.z = 0.0f;

	this->obj_main_bar->transform.position.x = this->transform.position.x;
	this->obj_main_bar->transform.position.y = this->transform.position.y;
	this->obj_main_bar->transform.position.x += this->main_bar_offset_x;
}

void UIHP::SetPercent(float value)
{
	if (value < 0.0f || value > 1.0f)
		return;

	this->obj_main_bar->transform.scale.x = value;
	this->main_bar_offset_x = -0.5f*(1.0f - value)*width;
	this->obj_main_bar->transform.position.x = this->transform.position.x + main_bar_offset_x;
}

void UIHP::SetOpacity(float value)
{
	this->base_bar->SetOpacity(value);
	this->main_bar->SetOpacity(value);
}

void UIHP::SetSize(float width, float height)
{
	this->base_bar->SetSize(width, height);
	this->main_bar->SetSize(width, height);
	this->width = width;
}

void UIHP::SetColor(Color color)
{
	this->main_bar->SetColor(color);
}
