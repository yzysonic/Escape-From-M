#pragma once
#include "Core\Core.h"

class GameCamera : public Camera
{
public:
	GameCamera(void);
	~GameCamera(void);
	void  SetTarget(Transform* target);
};