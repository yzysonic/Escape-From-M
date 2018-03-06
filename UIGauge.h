#pragma once
#include "Core\Core.h"

#define UIGaugeBaseColor Color(200, 200, 200, 255)
#define UIGaugeMainColor Color::red

class UIGauge : public Object
{
public:
	static constexpr float Width = 40.0f;
	static constexpr float Height = 3.0f;
	float offset_y;

	UIGauge(void);
	void SetPercent(float value);
	void SetOpacity(float value);
	void SetSize(float width, float height);
	void SetColor(Color color);
	void SetPosition(Vector2 position);

protected:
	float width;
	Object* obj_main_bar;
	RectPolygon2D* base_bar;
	RectPolygon2D* main_bar;
	float main_bar_offset_x;
};