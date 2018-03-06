#pragma once
#include "Core/Core.h"
#include "Player.h"
#include "Shadow.h"
#include "MagicSquare.h"
#include "Barrier.h"
#include "EnemyNormal.h"
#include "EnemyBullet.h"
#include "EnemyManager.h"
#include "UIElement.h"

class SceneMakotoTest : public Scene
{
public:
	void Init(void) override;
	void Update(void)override;
	void Uninit(void) override;

private:
	Camera* camera;
	Player* player;
	Shadow* shadow;
	MagicSquare* magic_square;
	EnemyManager* enemy_manager;
	Barrier* barrier;
	Object* field;
	Object* test_obj;
	Enemy* enemy;
	UIElement* ui_element;
	NumberUI* ui_day;
	FrameTimer timer;
	bool camera_play_mode;
	bool light_on;
	bool gameover;
	int day_count;
};