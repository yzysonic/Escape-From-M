#pragma once
#include "Core/Core.h"
#include "Player.h"
#include "Shadow.h"
#include "MagicSquare.h"
#include "Barrier.h"
#include "EnemyManager.h"
#include "UIDayTime.h"
#include "UIElement.h"
#include "UIBigHp.h"
#include "GameCamera.h"

class SceneTest : public Scene
{
public:
	void Init(void) override;
	void Update(void)override;
	void Uninit(void) override;

private:
	GameCamera* camera;
	Player* player;
	Shadow* shadow;
	MagicSquare* magic_square;
	EnemyManager* enemy_manager;
	Barrier* barrier;
	Object* field;
	Enemy* enemy;
	UIBigHp* ui_bighp;
	UIElement* ui_element;
	UIDayTime* ui_daytime;
	FrameTimer timer;
	bool gameover;
	int day_count;
};