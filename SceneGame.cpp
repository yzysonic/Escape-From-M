#include "SceneGame.h"
#include "FadeScreen.h"
#include "CameraPlay.h"
#include "CameraSmooth.h"

SceneGame::SceneGame(void)
{
}

void SceneGame::Init(void)
{
	// カメラ初期化
	this->camera = new Camera;
	this->camera->setBackColor(Color(223, 223, 223, 255));
	this->camera->near_z = 2.0f;
	this->camera->far_z = 500.0f;
	this->camera->fov = Deg2Rad(45.0f);
	this->camera->transform.position = Vector3(0.0f, 40.0f, -120.0f);
	this->camera->AddComponent<CameraPlay>();
	this->camera_play_mode = false;
	Renderer::GetInstance()->setCamera(this->camera);

	// UI初期化
	this->ui_element = new UIElement(
		10 + (int)Texture::Get("ui_element_title")->size.x - SystemParameters::ResolutionX / 2,
		0 - (int)Texture::Get("number")->size.y + SystemParameters::ResolutionY / 2
	);

	// ライティングオン
	Direct3D::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);


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
	this->camera->AddComponent<CameraSmooth>(this->player);

	// 魔法陣初期化
	this->magic_square = new MagicSquare;

	// 結界初期化
	this->barrier = new Barrier;

	// エネミー初期化
	this->enemy_manager = new EnemyManager;
	this->enemy_manager->target1 = this->barrier;
	this->enemy_manager->target2 = this->magic_square;
	this->enemy_manager->target3 = this->player;

	// フェイトイン
	FadeScreen::FadeIn(Color::black, 0.7f);

}

void SceneGame::Update(void)
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

}

void SceneGame::Uninit(void)
{
}
