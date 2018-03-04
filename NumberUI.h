#pragma once

#include "Core/Core.h"

class NumberUI : public Object
{
public:
	NumberUI(int digits, int x, int y, std::string texture_digit, std::string texture_title = "none");
	~NumberUI(void);
	void SetNumber(unsigned int value);
	void SetOffset(int x, int y);
	void SetColor(Color color);
	void SetNumberScale(float value);
	void SetNumberSpace(int value);

protected:
	int digitNum;
	int value;
	int digit_space;
	Texture* tex_digit;
	Texture* tex_title;
	int number_offset_x;
	int number_offset_y;
	std::vector<Object*> digitList;

	void SetNumberPos(void);
};