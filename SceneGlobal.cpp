#include "SceneGlobal.h"
#include "SceneTest.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "FadeScreen.h"
#include "Light.h"

void SceneGlobal::Init(void)
{
	// フェイドエフェクトの初期化
	FadeScreen::Create();
	FadeScreen::FadeOut(Color::black, 0.0f);

	// タイトルテクスチャ
	Texture::LoadTexture("forest");
	Texture::LoadTexture("title_logo");
	Texture::LoadTexture("title_start");
	Texture::LoadTexture("title_exit");
	Texture::LoadTexture("title_info");
	Texture::LoadTexture("title_cursor");

	// ゲームテクスチャ
	Texture::LoadTexture("dark_grass");
	Texture::LoadTexture("body_sum", "body_sum.tga");
	Texture::LoadTexture("misaki_head", "misaki_head.tga");
	Texture::LoadTexture("white_field", "white_field.jpg");
	Texture::LoadTexture("magic_square");
	Texture::LoadTexture("shadow");
	Texture::LoadTexture("enemy");
	Texture::LoadTexture("bullet_player");
	Texture::LoadTexture("bullet_enemy");
	Texture::LoadTexture("element");
	Texture::LoadTexture("number", "number.png", 10);
	Texture::LoadTexture("ui_element_title");
	Texture::LoadTexture("ui_day_title");

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
	if (GetKeyboardTrigger(DIK_1))
		gm->SetScene(new SceneTitle);
	if (GetKeyboardTrigger(DIK_2))
		gm->SetScene(new SceneGame);

#endif
}

void SceneGlobal::Uninit(void)
{
	FadeScreen::Singleton<FadeScreen>::Destroy();
	Shader::UnloadAll();
}