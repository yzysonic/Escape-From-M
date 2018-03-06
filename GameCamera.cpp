#include "GameCamera.h"
#include "CameraPlay.h"
#include "CameraSmooth.h"

GameCamera::GameCamera(void)
{
	this->setBackColor(Color(100, 193, 248, 255));
	this->near_z = 20.0f;
	this->far_z = 500.0f;
	this->fov = Deg2Rad(45.0f);
	this->transform.position = Vector3(0.0f, 20.0f, -60.0f);
	this->AddComponent<CameraPlay>();
	this->AddComponent<CameraSmooth>();
	Renderer::GetInstance()->setCamera(this);
}

GameCamera::~GameCamera(void)
{
	Renderer::GetInstance()->setCamera(nullptr);
}

void GameCamera::SetTarget(Transform * target)
{
	auto smooth = this->GetComponent<CameraSmooth>();
	smooth->target = target;
	smooth->SetActive(true);
}
