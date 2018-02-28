#include "SceneGlobal.h"
#include "SceneTest.h"
#include "FadeScreen.h"
#include "Light.h"

void SceneGlobal::Init(void)
{
	// フェイドエフェクトの初期化
	FadeScreen::Create();
	//FadeScreen::FadeOut(Color::black, 0.0f);

	// シェーダーの初期化
	VertexShader::Load("InstancingVS.hlsl");

	auto pDevice = Direct3D::GetDevice();

	//float Start = 0.5f;
	//float End = 0.8f;
	//pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_FOGCOLOR, 0x00d0e0f0);
	//pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
	////pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	//pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&Start));
	//pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&End));

	InitLight();
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