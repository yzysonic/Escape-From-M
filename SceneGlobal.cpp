#include "SceneGlobal.h"
#include "SceneTest.h"
#include "FadeScreen.h"

void SceneGlobal::Init(void)
{
	FadeScreen::Create();
	//FadeScreen::FadeOut(Color::black, 0.0f);

}

void SceneGlobal::Update(void)
{
#ifdef _DEBUG
	GameManager* gm = GameManager::GetInstance();

	if (GetKeyboardTrigger(DIK_0))
		gm->SetScene(new SceneTest);
#endif
}

void SceneGlobal::Uninit(void)
{
	FadeScreen::Singleton<FadeScreen>::Destroy();
	Shader::UnloadAll();
}