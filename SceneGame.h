#pragma once
#include "Core\Core.h"
#include "Player.h"
#include "Shadow.h"
#include "MagicSquare.h"
#include "Barrier.h"
#include "EnemyManager.h"
#include "UIElement.h"


class SceneGame : public Scene
{
public:
	SceneGame(void);
	void Init(void) override;
	void Update(void) override;
	void Uninit(void) override;

private:
	Camera* camera;
	UIElement* ui_element;
	Player* player;
	Shadow* shadow;
	MagicSquare* magic_square;
	EnemyManager* enemy_manager;
	Barrier* barrier;
	Object* field;
	bool camera_play_mode;

};