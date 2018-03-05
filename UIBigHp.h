#pragma once
#include "Core\Core.h"
#include "UIGauge.h"

class UIBigHp : public UIGauge
{
public:
	UIBigHp(int x, int y);
	void SetTexture(std::string name);

private:
	Object* title;
};
