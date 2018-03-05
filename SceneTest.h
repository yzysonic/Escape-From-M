#pragma once
#include "Core/Core.h"
#include "Player.h"
#include "Shadow.h"
#include "MagicSquare.h"
#include "Barrier.h"
#include "EnemyNormal.h"
#include "EnemyBullet.h"
#include "EnemyManager.h"
#include "UIDayTime.h"
#include "UIElement.h"
#include "UIBigHp.h"

class SceneTest : public Scene
{
public:
	void Init(void) override;
	void Update(void)override;

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
	UIBigHp* ui_bighp;
	UIElement* ui_element;
	UIDayTime* ui_daytime;
	bool camera_play_mode;
	bool light_on;

	FrameTimer timer;
};