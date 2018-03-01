#pragma once
#include "Core\Core.h"

class PlayerBulletShort : public Object
{
public:
	PlayerBulletShort(Vector3 pos);
	void Update(void) override;
	void OnCollision(Object* other) override;
	void OnDraw(void) override;
	void AfterDraw(void) override;

private:
	FrameTimer timer;
};