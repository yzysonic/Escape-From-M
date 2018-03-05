#pragma once
#include "Core\Core.h"
#include "NumberUI.h"

class UIDayTime : public Object
{
public:
	UIDayTime(int x, int y);
	void SetDay(int value);
	void SetTime(float progress);

private:
	NumberUI* day;
	Object* icon;
	float ellipse_x;
	float ellipse_y;
};
