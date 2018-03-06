#include "UIDayTime.h"

UIDayTime::UIDayTime(int x, int y)
{
	AddComponent<RectPolygon2D>("ui_day_outline", Layer::UI_00);
	this->transform.position.x = x;
	this->transform.position.y = y;

	this->day = new NumberUI(1, x+20, y, "number", "ui_day_title");

	this->icon = new Object;
	this->icon->AddComponent<RectPolygon2D>("ui_sun", Layer::UI_01);
	
	this->ellipse_x = 0.5f*Texture::Get("ui_day_outline")->size.x+ 25;
	this->ellipse_y = 0.5f*Texture::Get("ui_day_outline")->size.y+ 25;

	SetTime(0.0f);
}

void UIDayTime::SetDay(int value)
{
	this->day->SetNumber(value);
}

void UIDayTime::SetTime(float progress)
{
	float angle = Lerpf(Deg2Rad(30.0f), PI - Deg2Rad(30.0f), progress);
	this->icon->transform.position.x = this->ellipse_x*cosf(angle);
	this->icon->transform.position.y = this->ellipse_y*sinf(angle);
	this->icon->transform.position += this->transform.position;
}
