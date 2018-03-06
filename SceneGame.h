#pragma once
#include "Core\Core.h"
#include "Player.h"
#include "Shadow.h"
#include "MagicSquare.h"
#include "Barrier.h"
#include "EnemyManager.h"
#include "UIElement.h"
#include "UIDayTime.h"
#include "UIBigHp.h"
#include "GameCamera.h"

class SceneGame : public Scene
{
public:
	void Init(void) override;
	void Update(void) override;
	void Uninit(void) override;

private:
	GameCamera* camera;
	Player* player;
	Shadow* shadow;
	MagicSquare* magic_square;
	EnemyManager* enemy_manager;
	UIBigHp* ui_bighp;
	UIElement* ui_element;
	UIDayTime* ui_daytime;
	Barrier* barrier;
	FrameTimer timer;
	Object* field;
	bool gameover;
	int day_count;

};