#include "NumberUI.h"

NumberUI::NumberUI(int digits, int x, int y, std::string texture_digit, std::string texture_title)
{
	this->tex_title = Texture::Get(texture_title);
	this->tex_digit = Texture::Get(texture_digit);

	this->transform.position = Vector3((float)x, (float)y, 0.0f);

	if (texture_title != "none")
	{
		AddComponent<RectPolygon2D>(texture_title, Layer::UI_00);
		this->transform.position.x -= this->tex_title->size.x / 2;
	}

	this->digitNum = digits;

	this->digitList.reserve(digits);
	for (int i = 0; i < digits; i++)
	{
		Object* digit = new Object;
		
		digit->AddComponent<RectPolygon2D>(texture_digit, Layer::UI_00);
		digit->transform.position.x = x + (digits - i - 0.5f)*this->tex_digit->size.x;
		digit->transform.position.y = (float)y;

		this->digitList.push_back(digit);
	}

	this->digit_space = this->tex_digit->size.x;
}

NumberUI::~NumberUI()
{
	for (size_t i = 0; i < this->digitList.size(); i++)
		this->digitList[i]->Destroy();
	this->digitList.clear();

}

void NumberUI::SetNumber(unsigned int value)
{
	this->value = value;
	for (int i = 0; i < this->digitNum; i++)
	{
		this->digitList[i]->GetComponent<RectPolygon2D>()->setPattern(value % 10);
		value /= 10;
	}
}

void NumberUI::SetOffset(int x, int y)
{
	this->number_offset_x = x;
	this->number_offset_y = y;
}

void NumberUI::SetColor(Color color)
{
	if(GetComponent<RectPolygon2D>() != nullptr)
		GetComponent<RectPolygon2D>()->SetColor(color);
	for (auto digit : digitList)
		digit->GetComponent<RectPolygon2D>()->SetColor(color);
}

void NumberUI::SetNumberScale(float value)
{
	Vector2 size = this->digitList[0]->GetComponent<RectPolygon2D>()->GetSize()*value;

	for (auto &digit : this->digitList)
		digit->GetComponent<RectPolygon2D>()->SetSize(size.x, size.y);

	SetNumberPos();
}

void NumberUI::SetNumberSpace(int value)
{
	this->digit_space = value;
	SetNumberPos();
}

void NumberUI::SetNumberPos(void)
{
	int x = this->transform.position.x + 0.5f*this->tex_title->size.x + this->number_offset_x;
	int y = this->transform.position.y + this->number_offset_y;

	for (int i = 0; i < digitNum; i++)
	{
		auto digit = this->digitList[i];
		digit->transform.position.x = x + (digitNum - i - 0.5f)*this->digit_space;
		digit->transform.position.y = (float)y;
	}

}
