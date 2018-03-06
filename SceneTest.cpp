#include "SceneTest.h"
#include "FadeScreen.h"
#include "CameraPlay.h"
#include "CameraSmooth.h"
#include "SceneGameOver.h"
#include "SceneClear.h"

void SceneTest::Init(void)
{
	this->gameover = false;
	this->day_count = 1;
	this->timer.Reset(60.0f);

	// カメラ初期化
	this->camera = new GameCamera;

	// UI初期化
	this->ui_bighp = new UIBigHp(130 + (Texture::Get("ui_gauge")->size.x-SystemParameters::ResolutionX)/2, 70 - SystemParameters::ResolutionY / 2);
	this->ui_element = new UIElement(
		- (int)Texture::Get("ui_element_title")->size.x + SystemParameters::ResolutionX/2 - 40, 
		- (int)Texture::Get("number")->size.y + SystemParameters::ResolutionY/2 - 20
	);
	this->ui_daytime = new UIDayTime(
		-SystemParameters::ResolutionX/2 + 150,
		-50 - (int)Texture::Get("number")->size.y + SystemParameters::ResolutionY / 2
	);
	this->ui_daytime->SetDay(1);

	// 床初期化
	//this->field = new Object;
	//this->field->transform.setRotation(0.5f*PI, 0.0f, 0.0f);

	//Vertex3D *pVtx;
	//this->field->AddComponent<RectPolygon>("dark_grass", Layer::BG_00)->LockBuff(&pVtx);
	//pVtx[0].uv = Vector2(0.0, 0.0f);
	//pVtx[1].uv = Vector2(10.0, 0.0f);
	//pVtx[2].uv = Vector2(0.0, 10.0f);
	//pVtx[3].uv = Vector2(10.0, 10.0f);
	//this->field->GetComponent<RectPolygon>()->UnlockBuff();
	//this->field->GetComponent<RectPolygon>()->SetSize(400.0f*Vector2::one);

	// プレイヤー初期化
	this->player = new Player;
	//this->player->event_move += [&]
	//{
	//	if (this->camera_play_mode)
	//	{
	//		this->camera->GetComponent<CameraPlay>()->SetActive(false);
	//		this->camera->GetComponent<CameraSmooth>()->SetActive(true);
	//		this->camera_play_mode = false;
	//	}
	//};
	this->player->event_get_element += [&] {
		this->ui_element->SetNumber(this->player->GetElementNum());
	};
	this->player->event_death += [&] {
		this->gameover = true;
	};
	this->camera->SetTarget(&this->player->transform);

	// 魔法陣初期化
	this->magic_square = new MagicSquare;
	this->magic_square->event_damage += [&] {
		this->ui_bighp->SetPercent((float)this->magic_square->GetHp() / MagicSquare::MaxHp);
	};
	this->magic_square->event_death += [&] {
		this->gameover = true;
	};


	// 結界初期化
	this->barrier = new Barrier;
	this->barrier->event_damage += [&] {
		this->ui_bighp->SetPercent((float)this->barrier->GetHp() / Barrier::MaxHp);
	};
	this->barrier->event_death += [&] {
		this->ui_bighp->SetTexture("ui_bighp_title2");
		this->ui_bighp->SetPercent((float)this->magic_square->GetHp() / MagicSquare::MaxHp);
	};

	// エネミー初期化
	this->enemy_manager = new EnemyManager;
	this->enemy_manager->target1 = this->barrier;
	this->enemy_manager->target2 = this->magic_square;
	this->enemy_manager->target3 = this->player;
	this->enemy_manager->UpdateTarget();
	FadeScreen::FadeIn(Color::black, 0.0f);

	//this->test_obj = new Object;
	//this->test_obj->AddComponent<StaticModel>("stage")->alphaTestEnable = true;
	//this->test_obj->GetComponent<StaticModel>()->SetLayer(Layer::BG_01);
}

void SceneTest::Update(void)
{
	// カメラモードの切替
	//Vector2 pad_input_r(GetPadRX(), GetPadRY());
	//if (IsMouseLeftPressed() || fabsf((float)GetMouseMoveZ()) > 0.0f || pad_input_r.sqrLength() >= 0.01f)
	//{
	//	if (!this->camera_play_mode)
	//	{
	//		this->camera->GetComponent<CameraSmooth>()->SetActive(false);
	//		this->camera->GetComponent<CameraPlay>()->SetActive(true);
	//		this->camera_play_mode = true;
	//	}
	//}

	if (GetKeyboardTrigger(DIK_E))
	{
		this->enemy_manager->SwapNormal();
		this->enemy_manager->SwapRear();
	}

	this->ui_daytime->SetTime(this->timer.Progress());
	this->timer++;
	
	// ゲームオーバー
	if (gameover == true)
	{
		GameManager::SetScene(new SceneGameOver);
		return;
	}

	// ゲームクリア
	if (this->timer.TimeUp())
	{
		GameManager::Var<int>("Day") = this->day_count;
		GameManager::Var<int>("Magic") = this->magic_square->GetHp();
		GameManager::Var<int>("Element") = this->player->GetElementNum();
		GameManager::SetScene(new SceneClear);
		return;
	}

}

void SceneTest::Uninit(void)
{
	//StopSound(BGM_TITLE);
	Renderer::GetInstance()->setCamera(nullptr);
}
