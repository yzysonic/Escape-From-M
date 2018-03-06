#include "SceneGame.h"
#include "FadeScreen.h"
#include "SceneGameOver.h"
#include "SceneClear.h"


void SceneGame::Init(void)
{
	this->gameover = false;
	this->day_count = 1;
	this->timer.Reset(60.0f);

	// �J����������
	this->camera = new GameCamera;

	// ���C�e�B���O�I��
	Direct3D::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);

	// UI������
	this->ui_bighp = new UIBigHp(130 + (Texture::Get("ui_gauge")->size.x - SystemParameters::ResolutionX) / 2, 70 - SystemParameters::ResolutionY / 2);
	this->ui_element = new UIElement(
		-(int)Texture::Get("ui_element_title")->size.x + SystemParameters::ResolutionX / 2 - 40,
		-(int)Texture::Get("number")->size.y + SystemParameters::ResolutionY / 2 - 20
	);
	this->ui_daytime = new UIDayTime(
		-SystemParameters::ResolutionX / 2 + 150,
		-50 - (int)Texture::Get("number")->size.y + SystemParameters::ResolutionY / 2
	);
	this->ui_daytime->SetDay(1);

	// �t�B�[���h������
	this->field = new Object;
	this->field->AddComponent<StaticModel>("stage")->alphaTestEnable = true;
	this->field->GetComponent<StaticModel>()->SetLayer(Layer::BG_01);


	// �v���C���[������
	this->player = new Player;
	this->player->event_get_element += [&] {
		this->ui_element->SetNumber(this->player->GetElementNum());
	};
	this->player->event_death += [&] {
		this->gameover = true;
	};
	this->camera->SetTarget(&this->player->transform);

	// ���@�w������
	this->magic_square = new MagicSquare;
	this->magic_square->event_damage += [&] {
		this->ui_bighp->SetPercent((float)this->magic_square->GetHp() / MagicSquare::MaxHp);
	};
	this->magic_square->event_death += [&] {
		this->gameover = true;
	};

	// ���E������
	this->barrier = new Barrier;
	this->barrier->event_damage += [&] {
		this->ui_bighp->SetPercent((float)this->barrier->GetHp() / Barrier::MaxHp);
	};
	this->barrier->event_death += [&] {
		this->ui_bighp->SetTexture("ui_bighp_title2");
		this->ui_bighp->SetPercent((float)this->magic_square->GetHp() / MagicSquare::MaxHp);
	};

	// �G�l�~�[������
	this->enemy_manager = new EnemyManager;
	this->enemy_manager->target1 = this->barrier;
	this->enemy_manager->target2 = this->magic_square;
	this->enemy_manager->target3 = this->player;
	this->enemy_manager->UpdateTarget();

	// �t�F�C�g�C��
	FadeScreen::FadeIn(Color::black, 0.7f);

}

void SceneGame::Update(void)
{
	this->ui_daytime->SetTime(this->timer.Progress());
	this->timer++;

	// �Q�[���I�[�o�[
	if (gameover == true)
	{
		GameManager::SetScene(new SceneGameOver);
		return;
	}

	// �Q�[���N���A
	if (this->timer.TimeUp())
	{
		GameManager::Var<int>("Day") = this->day_count;
		GameManager::Var<int>("Magic") = this->magic_square->GetHp();
		GameManager::Var<int>("Element") = this->player->GetElementNum();
		GameManager::SetScene(new SceneClear);
		return;
	}

}

void SceneGame::Uninit(void)
{
	//StopSound(BGM_TITLE);
	Renderer::GetInstance()->setCamera(nullptr);
}
