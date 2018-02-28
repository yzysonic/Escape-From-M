#pragma once
#include "Core/Core.h"

class MagicSquare : public Object
{
public:
	float rotation_speed;		// ‰ñ“]‚Ì‘¬‚³
	float color_change_speed;	// FØ‘Ö‚Ì‘¬‚³

	MagicSquare(void);
	void Update(void) override;
	void OnDraw(void) override;
	void AfterDraw(void) override;

private:
	FrameTimer timer;
};