#include "SceneGlobal.h"
#include "SceneTest.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneClear.h"
#include "SceneGameOver.h"
#include "SceneNoon.h"
#include "FadeScreen.h"
#include "Light.h"
#include "Core\Game.h"

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
	Texture::LoadTexture("ui_day_outline");
	Texture::LoadTexture("ui_sun");
	Texture::LoadTexture("ui_moon");
	Texture::LoadTexture("ui_gauge");
	Texture::LoadTexture("ui_bighp_title");
	Texture::LoadTexture("ui_bighp_title2");
	Texture::LoadTexture("game_over");
	Texture::LoadTexture("result_title");
	Texture::LoadTexture("number_score", "number_score.png", 10);
	Texture::LoadTexture("game_score");
	Texture::LoadTexture("bark01_bottom", "bark01_bottom.tga");
	Texture::LoadTexture("branch01", "branch01.tga");
	Texture::LoadTexture("Cursor");
	Texture::LoadTexture("Item");
	Texture::LoadTexture("waku");
	Texture::LoadTexture("sentaku");
	Texture::LoadTexture("rensei");
	Texture::LoadTexture("terrain");


	// シェーダーの初期化
	VertexShader::Load("InstancingVS.hlsl");

	auto pDevice = Direct3D::GetDevice();

	float Density = 0.005f;
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_FOGCOLOR, 0xFF5EDEFF);
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP2);
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD *)(&Density));

	Light::Init();
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
	if (GetKeyboardTrigger(DIK_3))
		gm->SetScene(new SceneGameOver);
	if (GetKeyboardTrigger(DIK_4))
		gm->SetScene(new SceneClear);
	if (GetKeyboardTrigger(DIK_5))
		gm->SetScene(new SceneNoon);

#endif
}

void SceneGlobal::Uninit(void)
{
	FadeScreen::Singleton<FadeScreen>::Destroy();
	Shader::UnloadAll();
}