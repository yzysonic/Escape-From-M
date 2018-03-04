#pragma once
#include "Core\Core.h"

class Element : public Object
{
public:
	Element(Vector3 pos);
	void Update(void) override;
	void OnCollision(Object* other) override;
	void OnDraw(void) override;
	void AfterDraw(void) override;

private:
	Transform* target;
	FrameTimer delay_timer;
};