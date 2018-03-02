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

void SceneMakotoTest::Init(void)
{
	Texture::LoadTexture("attack");
	Texture::LoadTexture("body_sum", "body_sum.tga");
	Texture::LoadTexture("misaki_head", "misaki_head.tga");
	Texture::LoadTexture("enemy");
	Texture::LoadTexture("white_field", "white_field.jpg");
	Texture::LoadTexture("shadow");
	Texture::LoadTexture("magic_square");
	Texture::LoadTexture("player");
	Texture::LoadTexture("bullet_enemy");

	PixelShader::Load("BarrierPS.hlsl");

	// ライティング
	this->light_on = true;
	//Direct3D::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

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

	// 床初期化
	this->field = new Object;
	this->field->transform.setRotation(0.5f*PI, 0.0f, 0.0f);

	Vertex3D *pVtx;
	this->field->AddComponent<RectPolygon>("white_field", Layer::BG_00)->LockBuff(&pVtx);
	pVtx[0].uv = Vector2(0.0, 0.0f);
	pVtx[1].uv = Vector2(300.0, 0.0f);
	pVtx[2].uv = Vector2(0.0, 300.0f);
	pVtx[3].uv = Vector2(300.0, 300.0f);
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
	this->camera->AddComponent<CameraSmooth>(this->player);

	// 魔法陣初期化
	this->magic_square = new MagicSquare;

	// 結界初期化
	this->barrier = new Barrier;

	// エネミー初期化
	Transform t;
	this->enemy = new EnemyNormal(t);
	this->enemy->transform.position = Vector3(50.0f, 0.0f, -50);
	this->enemy->target = this->barrier;

	// エネミーバレットの初期化
	this->enemybullet = new EnemyBullet;
	this->enemybullet->transform.position = enemy->transform.position;
	this->enemybullet->target = this->barrier;

}

void SceneMakotoTest::Update(void)
{
	// カメラモードの切替
	if (IsMouseLeftPressed() || fabsf((float)GetMouseMoveZ()) > 0.0f)
	{
		if (!this->camera_play_mode)
		{
			this->camera->GetComponent<CameraSmooth>()->SetActive(false);
			this->camera->GetComponent<CameraPlay>()->SetActive(true);
			this->camera_play_mode = true;
		}
	}

	// ライティングの切替
	//if (GetKeyboardTrigger(DIK_L))
	//{
	//	if (this->light_on)
	//		Direct3D::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	//	else
	//		Direct3D::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	//	this->light_on = !this->light_on;
	//}

}