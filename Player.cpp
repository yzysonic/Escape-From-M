#include "Player.h"
#include "PlayerBulletShort.h"

Player::Player(void)
{
	this->type = ObjectType::Player;

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

	switch (this->anime_state)
	{
	case AnimeState::Idle:
	case AnimeState::Running:
		Move();
		Attack();

		break;

	case AnimeState::AttackShort:
		if (this->anime_timer.Elapsed() > 0.3f)
			break;

		if (this->bullet_timer.TimeUp())
		{
			AttackShort();
			this->bullet_timer.Reset();
		}
		
		break;

	case AnimeState::AttackLong:

		break;


	}

	
	if (this->anime_timer.TimeUp())
	{
		this->model->SetAnime((int)AnimeState::Idle);
		this->anime_timer.Reset(-1);
		this->anime_state = AnimeState::Idle;
	}


	this->anime_timer++;
	this->bullet_timer++;
}

int Player::GetHp(void)
{
	return this->hp;
}

Vector3 Player::GetAtkPos(Object * enemy)
{
	return this->transform.position;
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
	control += Vector3(GetPadLX(), 0, -GetPadLY());

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

void Player::Attack(void)
{
	int anime_index = -1;
	if (GetKeyboardTrigger(KeyAtkShort) || IsButtonTriggered(0, BtnAtkShort))
	{
		anime_index = (int)AnimeState::AttackShort;
		this->anime_state = AnimeState::AttackShort;
		this->bullet_timer.Reset(0.03f);
	}
	if (GetKeyboardTrigger(KeyAtkLong) || IsButtonTriggered(0, BtnAtkLong))
	{
		anime_index = (int)AnimeState::AttackLong;
		this->anime_state = AnimeState::AttackLong;
	}
	if (GetKeyboardTrigger(KeyAtkArea) || IsButtonTriggered(0, BtnAtkArea))
	{
		anime_index = (int)AnimeState::AttackArea;
		this->anime_state = AnimeState::AttackArea;
	}

	if (anime_index >= 0)
	{
		this->model->SetAnime(anime_index);
		this->anime_timer.Reset(this->model->GetAnimePeriod(anime_index));
	}

}

void Player::AttackShort(void)
{
	Transform t = this->transform;
	t.rotate(0.0f, Deg2Rad(Lerpf(50.0f, -50.0f, this->anime_timer.Elapsed()/0.3f)), 0.0f);
	t.position += t.getFront()*5.0f;
	t.position.y += 3.0f;
	new PlayerBulletShort(t, 0.3f-this->anime_timer.Elapsed());
}
