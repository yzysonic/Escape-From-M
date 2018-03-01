//=============================================================================
//
// ファイル名：SceneMakotoTest.cpp
// 作者：GP11A143 04 五十嵐 誠人
//
//=============================================================================
#include "SceneMakotoTest.h"
#include "Player.h"

void SceneMakotoTest::Init(void)
{
	//Texture::LoadTexture("panti02");
	//Texture::LoadTexture("Attack");

	// まだ入ってない
	Texture::LoadTexture("player");
	Texture::LoadTexture("bullet01");

	// カメラ初期化
	this->camera = new Camera;
	this->camera->setBackColor(Color(223, 223, 223, 255));
	this->camera->near_z = 2.0f;
	this->camera->far_z = 500.0f;
	this->camera->fov = Deg2Rad(45.0f);
	this->camera->transform.position = Vector3(0.0f, 10.0f, -30.0f);
	Renderer::GetInstance()->setCamera(this->camera);



	//test_obj = new Object;
	//test_obj->AddComponent<RectPolygon>("panti02");

	//test_obj1 = new Object;
	//test_obj1->AddComponent<RectPolygon>("Attack", Layer::PLAYER);

	//test_obj2 = new Object;
	//test_obj2->AddComponent<RectPolygon>("Attack");

	rare = new EnemyRare;
	player = new EnemyNormal;
	big = new EnemyBig;
	bullet = new EnemyBullet;
	new Player;


	player->target = rare;
	big->target = rare;

	Direct3D::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

}

void SceneMakotoTest::Update(void)
{
	//test_obj1->transform.position.x += 10.0f * Time::DeltaTime();
	//test_obj1->transform.rotate(0.0f, 0.0f, Deg2Rad(10.0f * Time::DeltaTime()));

	//float scale = 1.0f + 0.3f* fabsf(sinf(Time::DeltaTime()*2*PI));
	//test_obj1->transform.scale = Vector3(scale, scale, 0.0f);
}