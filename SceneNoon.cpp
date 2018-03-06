#include "SceneNoon.h"

void SceneNoon::Init(void)
{
	this->background = new Object;
	this->background->AddComponent<RectPolygon2D>("forest", Layer::BG_00)->SetSize((float)SystemParameters::ResolutionX, (float)SystemParameters::ResolutionY);
}

void SceneNoon::Update(void)
{
}

void SceneNoon::Uninit(void)
{
}
