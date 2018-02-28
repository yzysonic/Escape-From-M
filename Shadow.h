#pragma once
#include "Core\Core.h"

class Shadow : public Object
{
public:
	Shadow(Object* target);
	void Update(void) override;
	void OnDraw(void) override;
	void AfterDraw(void) override;

private:
	Transform* target;
};