#include "CameraSmooth.h"

void CameraSmooth::Init(void)
{
	camera = dynamic_cast<Camera*>(object);
	offset = camera->transform.position - target->position;
	speed = 5.0f;
}

void CameraSmooth::Update(void)
{
	if (target == nullptr)
		return;

	camera->transform.position = Vector3::Lerp(camera->transform.position, target->position + offset, speed*Time::DeltaTime());
	camera->at = Vector3::Lerp(camera->at, target->position, speed*Time::DeltaTime());
}