#pragma once
#include "Core/Core.h"

class MagicSquare : public Object
{
public:
	float rotation_speed;		// 回転の速さ
	float color_change_speed;	// 色切替の速さ

	MagicSquare(void);
	void Update(void) override;
	void OnDraw(void) override;
	void AfterDraw(void) override;

private:
	FrameTimer timer;
};