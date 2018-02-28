#pragma once
#include "Core\Core.h"

class Barrier : public Object
{
public:

	int hp;

	Barrier(void);
	void OnDraw(void) override;
	void AfterDraw(void) override;
};