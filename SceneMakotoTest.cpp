//=============================================================================
//
// ファイル名：SceneMakotoTest.cpp
// 作者：GP11A143 04 五十嵐 誠人
//
//=============================================================================
#include "SceneMakotoTest.h"

void SceneMakotoTest::Init(void)
{
	//Texture::LoadTexture("panti02");
	//Texture::LoadTexture("Attack");

	// まだ入ってない
	Texture::LoadTexture("player");
	Texture::LoadTexture("bullet01");


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

	player->target = rare;
	big->target = rare;
}

void SceneMakotoTest::Update(void)
{
	//test_obj1->transform.position.x += 10.0f * Time::DeltaTime();
	//test_obj1->transform.rotate(0.0f, 0.0f, Deg2Rad(10.0f * Time::DeltaTime()));

	//float scale = 1.0f + 0.3f* fabsf(sinf(Time::DeltaTime()*2*PI));
	//test_obj1->transform.scale = Vector3(scale, scale, 0.0f);
}