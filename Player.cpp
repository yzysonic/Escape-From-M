#include "Player.h"

Player::Player(void)
{
	this->hp = MaxHp;
	this->atk = 1;

	this->speed = 15.0f;
	this->anime_state = AnimeState::Idle;

	this->model = AddComponent<SkinnedModel>("player");
	this->model->SetAnime((int)this->anime_state);

	this->shadow = new Shadow(this);
	this->shadow->transform.scale = 5.0f*Vector3::one;
}

Player::~Player(void)
{
}

void Player::Update(void)
{
	int anime_index = -1;
	if (GetKeyboardPress(KeyAtkShort))
		anime_index = (int)AnimeState::AttackShort;
	if (GetKeyboardPress(KeyAtkLong))
		anime_index = (int)AnimeState::AttackLong;
	if (GetKeyboardPress(KeyAtkArea))
		anime_index = (int)AnimeState::AttackArea;

	if (anime_index >= 0)
	{
		this->model->SetAnime(anime_index);
		this->anime_timer.Reset(this->model->GetAnimePeriod(anime_index));
	}
	
	if (this->anime_timer.TimeUp())
	{
		this->model->SetAnime((int)AnimeState::Idle);
		this->anime_timer.Reset(-1);
	}

	Move();

	this->anime_timer++;
}

void Player::AtkUp(void)
{
	this->atk = min(this->atk + 1, MaxAtk);
}

void Player::Move(void)
{
	this->control = Vector3::zero;

	// キーボード入力
	if (GetKeyboardPress(DIK_W))
		control += Vector3(0.0f, 0.0f, 1.0f);
	if (GetKeyboardPress(DIK_S))
		control += Vector3(0.0f, 0.0f, -1.0f);
	if (GetKeyboardPress(DIK_A))
		control += Vector3(-1.0f, 0.0f, 0.0f);
	if (GetKeyboardPress(DIK_D))
		control += Vector3(1.0f, 0.0f, 0.0f);

	if (GetKeyboardPress(DIK_W) || GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_D))
		control = control.normalized();

	// パッド入力
	control += Vector3(GetPadLX(), -GetPadLY(), 0);

	// 移動処理
	if (control.sqrLength() > 0.0f)
	{
		auto camera = Renderer::GetInstance()->getCamera();
		Vector3 offset = this->transform.position - camera->transform.position;
		float phi = atan2f(offset.z, offset.x) - 0.5f*PI;

		Vector3 move;
		move.x = control.x*cosf(phi) - control.z*sinf(phi);
		move.z = control.x*sinf(phi) + control.z*cosf(phi);

		this->transform.position += move * this->speed * Time::DeltaTime();
		if (this->anime_state == AnimeState::Idle)
		{
			this->model->SetAnime((int)AnimeState::Running);
			this->anime_state = AnimeState::Running;
		}
		this->event_move();

		// 向きの設定
		this->transform.setFront(move);

	}
	else
	{
		if (this->anime_state == AnimeState::Running)
		{
			this->model->SetAnime((int)AnimeState::Idle);
			this->anime_state = AnimeState::Idle;
		}
	}


}
