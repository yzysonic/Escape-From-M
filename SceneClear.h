#pragma once
#include "Core/Scene.h"
#include "NumberUI.h"

class SceneClear : public Scene
{
public:
	void Init(void) override;
	void Update(void) override;
	void Uninit(void) override;

private:
	Object *title;
	NumberUI *score;
	NumberUI *scoreDay;
	NumberUI *scoreElement;
	NumberUI *scoreMagicHP;
	NumberUI *scoreBonusD;
	NumberUI *scoreBonusE;
	NumberUI *scoreBonusM;
	NumberUI *scoreTotal;
	NumberUI *rank;

	float timer;
	void(SceneClear::*pUpdate)(void);

	void update_clear_fadeWait(void);
	void update_clear_state0(void);
	void update_clear_state1(void);
};