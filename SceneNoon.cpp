#include "SceneNoon.h"

void SceneNoon::Init(void)
{
	this->background = new Object;
	this->background->AddComponent<RectPolygon2D>("forest", Layer::BG_00)->SetSize((float)SystemParameters::ResolutionX, (float)SystemParameters::ResolutionY);

	this->Waku = new Object;
	this->Waku->transform.position.y = 0.4f*SystemParameters::ResolutionY;
	this->Waku->transform.position.x = -0.4f*SystemParameters::ResolutionX;
	this->Waku->transform.scale.x = 1.5f;
	this->Waku->transform.scale.y = 1.5f;
	this->Waku->AddComponent<RectPolygon2D>("waku", Layer::DEFAULT);

	this->Sentaku = new Object;
	this->Sentaku->transform.position.y = -0.1f*SystemParameters::ResolutionY;
	this->Sentaku->transform.position.x = -0.25f*SystemParameters::ResolutionX;
	this->Sentaku->transform.scale.x = 1.0f;
	this->Sentaku->transform.scale.y = 1.0f;
	this->Sentaku->AddComponent<RectPolygon2D>("sentaku", Layer::DEFAULT);

	this->Sentaku1 = new Object;
	this->Sentaku1->transform.position.y = -0.1f*SystemParameters::ResolutionY;
	this->Sentaku1->transform.position.x = 0.0f*SystemParameters::ResolutionX;
	this->Sentaku1->transform.scale.x = 1.0f;
	this->Sentaku1->transform.scale.y = 1.0f;
	this->Sentaku1->AddComponent<RectPolygon2D>("sentaku", Layer::DEFAULT);

	this->Sentaku2 = new Object;
	this->Sentaku2->transform.position.y = -0.1f*SystemParameters::ResolutionY;
	this->Sentaku2->transform.position.x = 0.25f*SystemParameters::ResolutionX;
	this->Sentaku2->transform.scale.x = 1.0f;
	this->Sentaku2->transform.scale.y = 1.0f;
	this->Sentaku2->AddComponent<RectPolygon2D>("sentaku", Layer::DEFAULT);

	this->ElementObj = new Object;
	this->ElementObj->transform.position.y = 0.2f*SystemParameters::ResolutionY;
	this->ElementObj->transform.position.x = -0.45f*SystemParameters::ResolutionX;
	this->ElementObj->AddComponent<RectPolygon2D>("ui_element_title", Layer::DEFAULT);

	this->ElementObj1 = new Object;
	this->ElementObj1->transform.position.y = -0.1f*SystemParameters::ResolutionY;
	this->ElementObj1->transform.position.x = -0.3f*SystemParameters::ResolutionX;
	this->ElementObj1->AddComponent<RectPolygon2D>("ui_element_title", Layer::DEFAULT);

	this->ElementObj2 = new Object;
	this->ElementObj2->transform.position.y = -0.1f*SystemParameters::ResolutionY;
	this->ElementObj2->transform.position.x = -0.05f*SystemParameters::ResolutionX;
	this->ElementObj2->AddComponent<RectPolygon2D>("ui_element_title", Layer::DEFAULT);

	this->ElementObj3 = new Object;
	this->ElementObj3->transform.position.y = -0.1f*SystemParameters::ResolutionY;
	this->ElementObj3->transform.position.x = 0.2f*SystemParameters::ResolutionX;
	this->ElementObj3->AddComponent<RectPolygon2D>("ui_element_title", Layer::DEFAULT);

	this->Item = new Object;
	this->Item->transform.position.y = 0.3f*SystemParameters::ResolutionY;
	this->Item->transform.position.x = -0.39f*SystemParameters::ResolutionX;
	this->Item->transform.scale.x = 2.0f;
	this->Item->transform.scale.y = 2.0f;
	this->Item->AddComponent<RectPolygon2D>("Item", Layer::DEFAULT);

	this->Cursor = new Object;
	this->Cursor->transform.position.y = -0.4f*SystemParameters::ResolutionY;
	this->Cursor->transform.position.x = -0.25f*SystemParameters::ResolutionX;
	this->Cursor->transform.scale.x = 0.3f;
	this->Cursor->transform.scale.y = 0.3f;
	this->Cursor->AddComponent<RectPolygon2D>("Cursor", Layer::DEFAULT);

	this->gauge = new NumberUI(1, 450, 300, "ui_gauge");
	this->gauge->SetOffset(130, 0);
	this->gauge->SetNumber(GameManager::Var<int>("Day"));

	this->Day = new NumberUI(1, -480, 300, "number", "ui_day_title");
	this->Day->SetOffset(130, 0);
	this->Day->SetNumber(GameManager::Var<int>("Day"));

	this->Element = new NumberUI(3, -500, 135, "number_score");
	this->Element->SetOffset(130, 0);
	this->Element->SetNumber(GameManager::Var<int>("Element"));

	this->Element1 = new NumberUI(2, -300, -80, "number_score");
	this->Element1->SetOffset(130, 0);
	this->Element1->SetNumber(10 * (GameManager::Var<int>("Day")));

	this->Element2 = new NumberUI(2, 20, -80, "number_score");
	this->Element2->SetOffset(130, 0);
	this->Element2->SetNumber(15 * (GameManager::Var<int>("Day")));

	this->Element3 = new NumberUI(2, 340, -80, "number_score");
	this->Element3->SetOffset(130, 0);
	this->Element3->SetNumber(20 * (GameManager::Var<int>("Day")));

	this->cursor = 0;
}

void SceneNoon::Update(void)
{
	if (GetKeyboardTrigger(DIK_RIGHT) || IsButtonTriggered(0, BUTTON_RIGHT))
	{
		if (this->cursor < 2)
		{
			this->Cursor->transform.position.x += 320;
			this->cursor++;
		}
	}
	if (GetKeyboardTrigger(DIK_LEFT) || IsButtonTriggered(0, BUTTON_LEFT))
	{
		if (this->cursor > 0)
		{
			this->Cursor->transform.position.x -= 320;
			this->cursor--;
		}
	}

}

void SceneNoon::Uninit(void)
{
}
