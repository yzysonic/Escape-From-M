#pragma once
#include "Core/Core.h"
#include "Player.h"
#include "Shadow.h"

class SceneTest : public Scene
{
public:
	void Init(void) override;
	void Update(void)override;

private:
	Camera* camera;
	Player* player;
	Shadow* shadow;
	Object* field;
	Object* test_obj;
	bool camera_play_mode;
	bool light_on;
};