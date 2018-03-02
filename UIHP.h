#pragma once
#include "Core\Core.h"

#define HPBarBaseColor Color(200, 200, 200, 255)
#define HPBarMainColor Color::red

class UIHP : public Object
{
public:
	static constexpr float Width = 40.0f;
	static constexpr float Height = 3.0f;
	float offset_y;

	UIHP(Object* owner, float offset_y);
	void Update(void) override;
	void SetPercent(float value);
	void SetOpacity(float value);

private:
	Transform* owner;
	Object* obj_main_bar;
	RectPolygon2D* base_bar;
	RectPolygon2D* main_bar;
	float main_bar_offset_x;
};