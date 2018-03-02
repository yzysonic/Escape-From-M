#include "SceneTest.h"
#include "FadeScreen.h"
#include "CameraPlay.h"
#include "CameraSmooth.h"

void SceneTest::Init(void)
{
	Texture::LoadTexture("attack");
	Texture::LoadTexture("body_sum", "body_sum.tga");
	Texture::LoadTexture("misaki_head", "misaki_head.tga");
	Texture::LoadTexture("enemy");
	Texture::LoadTexture("white_field", "white_field.jpg");
	Texture::LoadTexture("shadow");
	Texture::LoadTexture("magic_square");
	Texture::LoadTexture("player");
	Texture::LoadTexture("player_bullet");


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

}

void SceneTest::Update(void)
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