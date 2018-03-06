#include "SceneClear.h"
#include "Core/Core.h"
#include "SceneTitle.h"
#include "FadeScreen.h"
#include "MagicSquare.h"

void SceneClear::Init(void)
{
	this->title = new Object;
	this->title->transform.position.y = 0.4f*SystemParameters::ResolutionY;
	this->title->transform.position.x = -0.3f*SystemParameters::ResolutionX;
	this->title->AddComponent<RectPolygon2D>("result_title", Layer::DEFAULT);

	this->title = new Object;
	this->title->transform.position.y = 0.2f*SystemParameters::ResolutionY;
	this->title->transform.position.x = 0.1f*SystemParameters::ResolutionX;
	this->title->AddComponent<RectPolygon2D>("game_score", Layer::DEFAULT);

	this->title = new Object;
	this->title->transform.position.y = 0.2f*SystemParameters::ResolutionY;
	this->title->transform.position.x = 0.3f*SystemParameters::ResolutionX;
	this->title->AddComponent<RectPolygon2D>("game_score", Layer::DEFAULT);

	this->scoreDay = new NumberUI(5, 70, -20, "number_score" ,"game_score");
	this->scoreDay->SetOffset(130, 0);
	this->scoreDay->SetNumber(GameManager::Var<int>("Day"));

	this->scoreBonusD = new NumberUI(5, 330, -20, "number_score");
	this->scoreBonusD->SetOffset(130, 0);

	int total = 0;

	if (GameManager::Var<int>("Day") == 5)
	{
		this->scoreBonusD->SetNumber(0);
		total += 0;
	}
	else if (GameManager::Var<int>("Day") == 4)
	{
		this->scoreBonusD->SetNumber(100);
		total += 100;
	}
	else if (GameManager::Var<int>("Day") == 3)
	{
		this->scoreBonusD->SetNumber(200);
		total += 200;
	}
	else if (GameManager::Var<int>("Day") == 2)
	{
		this->scoreBonusD->SetNumber(300);
		total += 300;
	}
	else if (GameManager::Var<int>("Day") == 1)
	{
		this->scoreBonusD->SetNumber(400);
		total += 400;
	}

	this->scoreElement = new NumberUI(5, 70, -90,"number_score", "game_score");
	this->scoreElement->SetOffset(130, 0);
	this->scoreElement->SetNumber(GameManager::Var<int>("Element"));

	this->scoreBonusE = new NumberUI(5, 330, -90, "number_score");
	this->scoreBonusE->SetOffset(130, 0);
	this->scoreBonusE->SetNumber(GameManager::Var<int>("Element"));
	total += GameManager::Var<int>("Element");

	this->scoreMagicHP = new NumberUI(5, 70, -160, "number_score", "game_score");
	this->scoreMagicHP->SetOffset(130, 0);
	this->scoreMagicHP->SetNumber(GameManager::Var<int>("Magic"));

	this->scoreBonusM = new NumberUI(5, 330, -160, "number_score");
	this->scoreBonusM->SetOffset(130, 0);

	MagicSquare::MaxHp / GameManager::Var<int>("Magic");

	float MagicHP;

	MagicHP = (float)GameManager::Var<int>("Magic") / MagicSquare::MaxHp;

	if (MagicHP <= 0.25)
	{
		this->scoreBonusM->SetNumber(100);
		total += 100;
	}
	else if (MagicHP <= 0.5)
	{
		this->scoreBonusM->SetNumber(200);
		total += 200;
	}
	else if (MagicHP <= 0.75)
	{
		this->scoreBonusM->SetNumber(300);
		total += 300;
	}
	else if (MagicHP <= 1.0)
	{
		this->scoreBonusM->SetNumber(400);
		total += 400;
	}

	this->scoreTotal = new NumberUI(5, 330, -250, "number_score", "game_score");
	this->scoreTotal->SetOffset(130, 0);
	this->scoreTotal->SetNumber(total);

	this->rank = new NumberUI(5, -300, -250, "number_score", "game_score");
	this->rank->SetOffset(130, 0);
	this->rank->SetNumber(100);

	Renderer::GetInstance()->getCamera("default")->setBackColor(180, 180, 180, 255);

	this->timer = 0;

	// BGMを再生
	//SetVolume(BGM_CLEAR, -1800);
	//PlayBGM(BGM_CLEAR);

	// フェイトイン効果
	FadeScreen::FadeIn(Color::white);

	SceneClear::pUpdate = &SceneClear::update_clear_fadeWait;
}

void SceneClear::Update(void)
{
	(this->*pUpdate)();
	this->timer += Time::DeltaTime();
}

void SceneClear::Uninit(void)
{
	//StopSound(BGM_CLEAR);
}

void SceneClear::update_clear_fadeWait(void)
{
	if (FadeScreen::Finished())
	{
		SceneClear::pUpdate = &SceneClear::update_clear_state0;
	}
}

void SceneClear::update_clear_state0(void)
{
	if (this->timer > 4.0f)
	{
		FadeScreen::FadeOut(Color::black, 0.7f);
		this->timer = 0;
		SceneClear::pUpdate = &SceneClear::update_clear_state1;
	}
		
}

void SceneClear::update_clear_state1(void)
{
	if (this->timer > 1.0f)
	{
		GameManager::SetScene(new SceneTitle);
	}
		
}
