#include "UIBigHp.h"

UIBigHp::UIBigHp(int x, int y)
{
	this->base_bar->SetLayer(Layer::UI_01);
	this->main_bar->SetLayer(Layer::UI_00);

	this->base_bar->SetTexture("ui_gauge");
	this->base_bar->SetColor(Color::white);

	SetSize(this->base_bar->GetSize().x, this->base_bar->GetSize().y);
	SetColor(Color(131, 255, 198, 255));
	SetPosition(Vector2(x, y));

	this->title = new Object;
	this->title->AddComponent<RectPolygon2D>("ui_bighp_title", Layer::UI_00);
	this->title->transform.position.x = x - (Texture::Get("ui_gauge")->size.x + Texture::Get("ui_bighp_title")->size.x) / 2 - 10;
	this->title->transform.position.y = y;
}

void UIBigHp::SetTexture(std::string name)
{
	this->title->GetComponent<RectPolygon2D>()->SetTexture(name);
	this->title->transform.position.x = this->transform.position.x - (Texture::Get("ui_gauge")->size.x + Texture::Get(name)->size.x) / 2 - 10;
}
