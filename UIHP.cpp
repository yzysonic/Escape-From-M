#include "UIHP.h"

UIHP::UIHP(Object * owner, float offset_y)
{
	this->base_bar = AddComponent<Billboard>("none");
	this->base_bar->SetColor(HPBarBaseColor);
	this->base_bar->SetSize(Vector2(Width, Height));

	this->obj_main_bar = new Object;
	this->main_bar = this->obj_main_bar->AddComponent<Billboard>("none");
	this->main_bar->SetColor(HPBarMainColor);
	this->main_bar->SetSize(Vector2(Width, Height));

	this->owner = &owner->transform;
	this->offset_y = offset_y;
	this->main_bar_offset_x = 0.0f;
}

void UIHP::Update(void)
{
	this->transform.position = this->owner->position;
	this->transform.position.y += this->offset_y;

	this->obj_main_bar->transform.position = this->transform.position;
	this->obj_main_bar->transform.position.x += this->main_bar_offset_x;
}

void UIHP::SetPercent(float value)
{
	if (value < 0.0f || value > 1.0f)
		return;

	this->obj_main_bar->transform.scale.x = value;
	this->main_bar_offset_x = -0.5f*(1.0f - value)*Width;
	this->obj_main_bar->transform.position.x = this->transform.position.x + main_bar_offset_x;
}

void UIHP::SetOpacity(float value)
{
	this->base_bar->SetOpacity(value);
	this->main_bar->SetOpacity(value);
}
