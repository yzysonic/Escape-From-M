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

	// �J����������
	this->camera = new Camera;
	this->camera->setBackColor(Color(223, 223, 223, 255));
	this->camera->near_z = 2.0f;
	this->camera->far_z = 500.0f;
	this->camera->fov = Deg2Rad(45.0f);
	this->camera->transform.position = Vector3(0.0f, 10.0f, -30.0f);
	this->camera->AddComponent<CameraPlay>();
	this->camera_play_mode = false;
	Renderer::GetInstance()->setCamera(this->camera);

	// ��������
	this->field = new Object;
	this->field->transform.scale = 400.0f*Vector3::one;
	this->field->transform.setRotation(0.5f*PI, 0.0f, 0.0f);

	Vertex3D *pVtx;
	this->field->AddComponent<RectPolygon>("white_field")->LockBuff(&pVtx);
	pVtx[0].uv = Vector2(0.0, 0.0f);
	pVtx[1].uv = Vector2(300.0, 0.0f);
	pVtx[2].uv = Vector2(0.0, 300.0f);
	pVtx[3].uv = Vector2(300.0, 300.0f);
	this->field->GetComponent<RectPolygon>()->UnlockBuff();

	// �v���C���[������
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

	// �G�l�~�[�e�X�g
	this->test_obj = new Object;
	this->test_obj->AddComponent<StaticModel>("enemy");
	this->test_obj->transform.scale = 0.5f * Vector3::one;
	this->test_obj->transform.position = Vector3(10.0f, 0.0f, 20.0f);

	// ���C�e�B���O
	this->light_on = false;
	Direct3D::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void SceneTest::Update(void)
{
	this->test_obj->transform.rotate(0.f, 0.02f, 0.f);


	// �J�������[�h�̐ؑ�
	if (IsMouseLeftPressed() || fabsf((float)GetMouseMoveZ()) > 0.0f)
	{
		if (!this->camera_play_mode)
		{
			this->camera->GetComponent<CameraSmooth>()->SetActive(false);
			this->camera->GetComponent<CameraPlay>()->SetActive(true);
			this->camera_play_mode = true;
		}
	}

	// ���C�e�B���O�̐ؑ�
	if (GetKeyboardTrigger(DIK_L))
	{
		if (this->light_on)
			Direct3D::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
		else
			Direct3D::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
		this->light_on = !this->light_on;
	}
	
}