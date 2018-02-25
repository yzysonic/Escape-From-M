#include "Player.h"

Player::Player(void)
{
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
	static int i = 0;

	if (GetKeyboardTrigger(DIK_PGUP))
	{
		i++;
		this->model->SetAnime(i);
	}
	if (GetKeyboardTrigger(DIK_PGDN))
	{
		i--;
		this->model->SetAnime(i);
	}

	Move();

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
		this->transform.position += control * this->speed * Time::DeltaTime();
		if (this->anime_state == AnimeState::Idle)
		{
			this->model->SetAnime((int)AnimeState::Running);
			this->anime_state = AnimeState::Running;
		}
		this->event_move();
	}
	else
	{
		if (this->anime_state == AnimeState::Running)
		{
			this->model->SetAnime((int)AnimeState::Idle);
			this->anime_state = AnimeState::Idle;
		}
	}

	// 向きの設定
	if ((control.x != 0.0f) || control.z != 0.0f)
		this->transform.setFront(control);

}
