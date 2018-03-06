//=============================================================================
//
// ファイル名：SceneMakotoTest.cpp
// 作者：GP11A143 04 五十嵐 誠人
//
//=============================================================================
#include "SceneMakotoTest.h"
#include "FadeScreen.h"
#include "CameraPlay.h"
#include "CameraSmooth.h"
#include "SceneGameOver.h"
#include "SceneClear.h"

void SceneMakotoTest::Init(void)
{
	this->day_count = 1;

	// カメラ初期化
	this->camera = new Camera;
	this->camera->setBackColor(Color(223, 223, 223, 255));
	this->camera->near_z = 2.0f;
	this->camera->far_z = 500.0f;
	this->camera->fov = Deg2Rad(45.0f);
	this->camera->transform.position = Vector3(0.0f, 40.0f, -120.0f);
	this->camera->AddComponent<CameraPlay>();
	this->camera_play_mode = false;
	this->timer.Reset(120.0f);
	Renderer::GetInstance()->setCamera(this->camera);

	// UI初期化
	this->ui_element = new UIElement(
		10 + (int)Texture::Get("ui_element_title")->size.x - SystemParameters::ResolutionX / 2,
		0 - (int)Texture::Get("number")->size.y + SystemParameters::ResolutionY / 2
	);
	this->ui_day = new NumberUI(
		1,
		SystemParameters::ResolutionX / 2 - 70,
		0 - (int)Texture::Get("number")->size.y + SystemParameters::ResolutionY / 2,
		"number", "ui_day_title"
	);
	this->ui_day->SetNumber(this->day_count);

	// 床初期化
	this->field = new Object;
	this->field->transform.setRotation(0.5f*PI, 0.0f, 0.0f);

	Vertex3D *pVtx;
	this->field->AddComponent<RectPolygon>("dark_grass", Layer::BG_00)->LockBuff(&pVtx);
	pVtx[0].uv = Vector2(0.0, 0.0f);
	pVtx[1].uv = Vector2(10.0, 0.0f);
	pVtx[2].uv = Vector2(0.0, 10.0f);
	pVtx[3].uv = Vector2(10.0, 10.0f);
	this->field->GetComponent<RectPolygon>()->UnlockBuff();
	this->field->GetComponent<RectPolygon>()->SetSize(400.0f*Vector2::one);

	// プレイヤー初期化
	this->player = new Player;
	this->player->event_move += [&]
	{
		if (this->camera_play_mode)
		{
			this->camera->GetComponent<CameraPlay>()->SetActive(false);
			this->camera->GetComponent<CameraSmooth>()->SetActive(true);
			this->camera_play_mode = false;
		}
	};
	this->player->event_get_element += [&] {
		this->ui_element->SetNumber(this->player->GetElementNum());
	};
	this->player->event_death += [&] {
		gameover = true;
	};

	this->camera->AddComponent<CameraSmooth>(this->player);

	// 魔法陣初期化
	this->magic_square = new MagicSquare;
	this->magic_square->event_death += [&] {
		gameover = true;
	};

	// 結界初期化
	this->barrier = new Barrier;

	// エネミー初期化
	this->enemy_manager = new EnemyManager;
	this->enemy_manager->target1 = this->barrier;
	this->enemy_manager->target2 = this->magic_square;
	this->enemy_manager->target3 = this->player;

	FadeScreen::FadeIn(Color::black, 0.0f);

	this->gameover = false;
}

void SceneMakotoTest::Update(void)
{
	// カメラモードの切替
	Vector2 pad_input_r(GetPadRX(), GetPadRY());
	if (IsMouseLeftPressed() || fabsf((float)GetMouseMoveZ()) > 0.0f || pad_input_r.sqrLength() >= 0.01f)
	{
		if (!this->camera_play_mode)
		{
			this->camera->GetComponent<CameraSmooth>()->SetActive(false);
			this->camera->GetComponent<CameraPlay>()->SetActive(true);
			this->camera_play_mode = true;
		}
	}
	
	// ゲームオーバー
	if (gameover == true)
	{
		GameManager::SetScene(new SceneGameOver);
	}

	// ゲームクリア
	if (this->timer.TimeUp())
	{
		GameManager::Var<int>("Day") = this->day_count;
		GameManager::Var<int>("Magic") = this->magic_square->GetHp();
		GameManager::Var<int>("Element") = this->player->GetElementNum();
		GameManager::SetScene(new SceneClear);
	}
	timer++;

	if (GetKeyboardTrigger(DIK_E))
	{
		this->enemy_manager->SwapNormal();
		this->enemy_manager->SwapRear();
	}

	if (GetKeyboardTrigger(DIK_Q))
	{
		timer.Reset(0);
	}

	if (GetKeyboardTrigger(DIK_Z))
	{
		this->day_count++;
	}
}

void SceneMakotoTest::Uninit(void)
{
	//StopSound(BGM_TITLE);
	Renderer::GetInstance()->setCamera(nullptr);
}
