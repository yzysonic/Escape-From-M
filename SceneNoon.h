#pragma once
#include "Core/Scene.h"
#include "Core/Core.h"
#include "NumberUI.h"

class SceneNoon : public Scene
{
public:
	void Init(void) override;
	void Update(void) override;
	void Uninit(void) override;

private:
	Object *ElementObj;
	Object *ElementObj1;
	Object *ElementObj2;
	Object *ElementObj3;
	Object *Cursor;
	Object *background;
	Object *Item;
	Object *Waku;
	Object *Sentaku;
	Object *Sentaku1;
	Object *Sentaku2;
	NumberUI *Day;
	NumberUI *gauge;
	NumberUI *Element;
	NumberUI *Element1;
	NumberUI *Element2;
	NumberUI *Element3;

	enum State
	{
		StateWaitFade,
		StateNormal
	}state;

	enum Command
	{
		COM_START,
		COM_EXIT,
		COM_OP,
	}com;

	// カメラ
	Camera *camera;

	// 画像


	// カーソル
	int cursor;

	void update_fadeWait(void);
};
