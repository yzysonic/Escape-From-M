#pragma once
#include "Core/Core.h"

class SceneTest : public Scene
{
public:
	void Init(void) override;
	void Update(void)override;

private:
	Camera* camera;
	Object* test_obj;
};