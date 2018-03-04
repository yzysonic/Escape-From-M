#pragma once

#include "Core/Scene.h"
#include "Core/Core.h"

class SceneTitle : public Scene
{
public:
	void Init(void) override;
	void Update(void) override;
	void Uninit(void) override;

private:

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

	// �J����
	Camera *camera;

	// �摜
	Object *background = nullptr;
	Object *logo = nullptr;
	Object *info = nullptr;
	Object *cursor = nullptr;
	Object *start = nullptr;
	Object *exit = nullptr;


	// �J�[�\��
	int cursorPos;

	void update_fadeWait(void);
};
