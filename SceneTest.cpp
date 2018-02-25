#include "SceneTest.h"
#include "FadeScreen.h"
#include "CameraPlay.h"

void SceneTest::Init(void)
{
	Texture::LoadTexture("attack");

	this->camera = new Camera;
	this->camera->AddComponent<CameraPlay>()->SetActive(true);
	Renderer::GetInstance()->setCamera(this->camera);

	this->test_obj = new Object;
	this->test_obj->AddComponent<RectPolygon>("attack");

}

void SceneTest::Update(void)
{

}