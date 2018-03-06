#pragma once
#include "Core\Core.h"
#include "UIGauge.h"

class UIHP : public UIGauge
{
public:
	float offset_y;

	UIHP(Object* owner);
	void Update(void) override;

private:
	Transform* owner;
};