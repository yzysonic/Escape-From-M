#include "UIGauge.h"

UIGauge::UIGauge(void)
{
	this->base_bar = AddComponent<RectPolygon2D>("none", Layer::UI_00);
	this->base_bar->SetColor(UIGaugeBaseColor);

	this->obj_main_bar = new Object;
	this->main_bar = this->obj_main_bar->AddComponent<RectPolygon2D>("none", Layer::UI_01);
	this->main_bar->SetColor(UIGaugeMainColor);

	SetSize(Width, Height);

	this->main_bar_offset_x = 0.0f;
}

void UIGauge::SetPercent(float value)
{
	if (value < 0.0f || value > 1.0f)
		return;

	this->obj_main_bar->transform.scale.x = value;
	this->main_bar_offset_x = -0.5f*(1.0f - value)*width;
	this->obj_main_bar->transform.position.x = this->transform.position.x + main_bar_offset_x;
}

void UIGauge::SetOpacity(float value)
{
	this->base_bar->SetOpacity(value);
	this->main_bar->SetOpacity(value);
}

void UIGauge::SetSize(float width, float height)
{
	this->base_bar->SetSize(width, height);
	this->main_bar->SetSize(width, height);
	this->width = width;
}

void UIGauge::SetColor(Color color)
{
	this->main_bar->SetColor(color);
}

void UIGauge::SetPosition(Vector2 position)
{
	this->transform.position.x = position.x;
	this->transform.position.y = position.y;
	this->obj_main_bar->transform.position.x = position.x;
	this->obj_main_bar->transform.position.y = position.y;
	this->obj_main_bar->transform.position.x += this->main_bar_offset_x;
}
