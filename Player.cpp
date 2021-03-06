#include "Player.h"
#include "PlayerBulletShort.h"
#include "PlayerBulletLong.h"
#include "PlayerBulletArea.h"

//=============================================================================
// Player
//=============================================================================

Player::Player(void)
{
	this->type = ObjectType::Player;
	this->atk = 1;
	this->speed = PlayerSpeed;
	this->anime = AnimeSet::Idle;
	this->element_num = 0;
	this->init_attack = [] {};
	this->update_attack = [] {};

	// AttackTarget初期化
	this->hp = this->max_hp = MaxHp;
	this->uihp->offset_y = 12.0f;
	this->uihp->SetColor(Color::blue);
	this->uihp->SetOpacity(0.0f);
	this->event_damage += [&]{
		this->current_state->SetState(StateName::Damage);
	};

	// モデル初期化
	this->model = AddComponent<SkinnedModel>("player");
	this->model->SetAnime((int)this->anime);

	// コライダー初期化
	this->collider = AddComponent<SphereCollider>();
	this->collider->radius = Radius;

	// 影初期化
	this->shadow = new Shadow(this);
	this->shadow->transform.scale = 5.0f*Vector3::one;

	// ステート初期化
	this->state.resize((int)StateName::Max);
	this->state[(int)StateName::Idle].reset(new StateIdle(this));
	this->state[(int)StateName::Move].reset(new StateMove(this));
	this->state[(int)StateName::Attack].reset(new StateAttack(this));
	this->state[(int)StateName::Damage].reset(new StateDamage(this));
	this->current_state = this->state[(int)StateName::Idle].get();
}

void Player::Update(void)
{
	AttackControl();
	MoveControl();

	this->current_state->Update();
}

void Player::Uninit(void)
{
	this->shadow->Destroy();
	this->uihp->Destroy();
}

void Player::OnCollision(Object * other)
{
	if (other->type == ObjectType::Element)
	{
		this->element_num++;
		this->event_get_element();
	}
}

void Player::AtkUp(void)
{
	this->atk = min(this->atk + 1, MaxAtk);
}

int Player::GetElementNum(void)
{
	return this->element_num;
}

void Player::SetAnime(AnimeSet anime, bool loop)
{
	int index = (int)anime;

	this->model->SetAnime(index);
	this->anime = anime;

	if (loop)
		this->anime_timer.Reset(-1);
	else
		this->anime_timer.Reset(this->model->GetAnimePeriod(index));

}

void Player::MoveControl(void)
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

	// ムーブイベント
	if (this->control.sqrLength() >= 0.01f)
	{
		this->current_state->SetState(StateName::Move);
		this->event_move();
	}
}

void Player::Move(void)
{
	// 移動処理
	auto camera = Renderer::GetInstance()->getCamera();
	Vector3 offset = this->transform.position - camera->transform.position;
	float phi = atan2f(offset.z, offset.x) - 0.5f*PI;

	Vector3 move;
	move.x = control.x*cosf(phi) - control.z*sinf(phi);
	move.z = control.x*sinf(phi) + control.z*cosf(phi);

	// 移動量を反応
	this->transform.position += move * this->speed * Time::DeltaTime();

	// 向きの設定
	this->transform.setFront(move);
}

void Player::AttackControl(void)
{
	if (GetKeyboardTrigger(KeyAtkShort) || IsButtonTriggered(0, BtnAtkShort))
	{
		this->init_attack = [&] {
			this->SetAnime(AnimeSet::ShootBulletShort, false);
			this->bullet_timer.Reset(0.03f);
			this->update_attack = [&] {
				if (this->anime_timer.Elapsed() > 0.3f)
					return;

				if (this->bullet_timer.TimeUp())
				{
					ShootBulletShort();
					this->bullet_timer.Reset();
				}
				this->bullet_timer++;
			};
		};
	}

	else if (GetKeyboardTrigger(KeyAtkLong) || IsButtonTriggered(0, BtnAtkLong))
	{
		this->init_attack = [&] {
			this->SetAnime(AnimeSet::AttackLong, false);
			this->bullet_timer.Reset(0.04f);
			this->update_attack = [&] {
				// 弾発射処理
				if (this->anime_timer.Elapsed() < 0.3f || this->anime_timer.Elapsed() > 0.7f)
					return;

				if (this->bullet_timer.TimeUp())
				{
					ShootBulletLong();
					this->bullet_timer.Reset();
				}
				this->bullet_timer++;

				// 回転処理
				float control_len = this->control.length();
				if (control_len > 0.01f)
				{
					auto camera = Renderer::GetInstance()->getCamera();
					Vector3 offset = this->transform.position - camera->transform.position;
					float phi = atan2f(offset.z, offset.x) - 0.5f*PI;

					Vector3 move;
					move.x = control.x*cosf(phi) - control.z*sinf(phi);
					move.z = control.x*sinf(phi) + control.z*cosf(phi);

					// 向きの設定
					this->transform.setFront(move);
				}

			};

		};
	}

	else if (GetKeyboardTrigger(KeyAtkArea) || IsButtonTriggered(0, BtnAtkArea))
	{
		this->init_attack = [&] {
			this->SetAnime(AnimeSet::AttackArea, false);
			this->bullet_timer.Reset(0.005f);
			this->update_attack = [&] {
				// 弾発射処理
				if (this->anime_timer.Elapsed() > 0.2f)
					return;

				if (this->bullet_timer.TimeUp())
				{
					ShootBulletArea();
					this->bullet_timer.Reset();
				}
				this->bullet_timer++;
			};

		};
	}
	else return;

	this->current_state->SetState(StateName::Attack);
}

void Player::ShootBulletShort(void)
{
	Transform t = this->transform;
	t.rotate(0.0f, Deg2Rad(Lerpf(50.0f, -50.0f, this->anime_timer.Elapsed()/0.3f)), 0.0f);
	t.position += t.getFront()*5.0f;
	t.position.y += 3.0f;
	new PlayerBulletShort(t, this->atk, 0.3f - this->anime_timer.Elapsed());
}

void Player::ShootBulletLong(void)
{
	Transform t = this->transform;
	t.position += t.getFront()*5.0f;
	t.position.y += 3.0f;
	new PlayerBulletLong(t, this->atk);
}

void Player::ShootBulletArea(void)
{
	Transform t = this->transform;
	float theta = Lerpf(0.0f, 2.0f*PI, this->anime_timer.Elapsed() / 0.2f);
	t.setRotation(0.0f, theta, 0.0f);
	t.position.y += 10.0f;
	new PlayerBulletArea(t, this->atk, 9.0f);

	t.setRotation(0.0f, theta, 0.0f);
	new PlayerBulletArea(t, this->atk, 11.0f);

	t.setRotation(0.0f, theta, 0.0f);
	new PlayerBulletArea(t, this->atk, 13.0f);
}



//=============================================================================
// State
//=============================================================================

void Player::State::SetState(StateName state)
{
	this->player->current_state->OnExit();
	this->player->current_state = player->state[(int)state].get();
	this->player->current_state->OnEnter();
}


//=============================================================================
// StateIdle
//=============================================================================

void Player::StateIdle::OnEnter(void)
{
	this->player->SetAnime(AnimeSet::Idle);
}

void Player::StateIdle::Update(void)
{
}

void Player::StateIdle::SetState(StateName state)
{
	switch (state)
	{
	case StateName::Move:
	case StateName::Attack:
	case StateName::Damage:
		State::SetState(state);
	}
}


//=============================================================================
// StateMove
//=============================================================================

void Player::StateMove::OnEnter(void)
{
	this->player->SetAnime(AnimeSet::Running);
}

void Player::StateMove::Update(void)
{
	float control_len = this->player->control.length();
	if (control_len > 0.01f)
	{
		this->player->Move();
		this->player->model->SetAnimeSpeedScale(control_len);
	}
	else
		this->SetState(StateName::Idle);
}

void Player::StateMove::OnExit(void)
{
	this->player->model->SetAnimeSpeedScale(1.0f);
}

void Player::StateMove::SetState(StateName state)
{
	switch (state)
	{
	case StateName::Idle:
	case StateName::Attack:
	case StateName::Damage:
		State::SetState(state);
	}
}


//=============================================================================
// StateAttack
//=============================================================================

void Player::StateAttack::OnEnter(void)
{
	this->player->init_attack();
	this->timer.Reset(0.5f);
}

void Player::StateAttack::Update(void)
{
	this->player->update_attack();

	if (this->player->anime_timer.TimeUp())
		SetState(StateName::Idle);

	this->player->anime_timer++;
	this->timer++;
}

void Player::StateAttack::SetState(StateName state)
{
	switch (state)
	{
	case StateName::Idle:
		State::SetState(state);
		break;
	case StateName::Attack:
		if(this->timer.TimeUp())
			State::SetState(state);
		break;
	}
}


//=============================================================================
// StateDamage
//=============================================================================

void Player::StateDamage::OnEnter(void)
{
	this->player->SetAnime(AnimeSet::Injure, false);
}

void Player::StateDamage::Update(void)
{
	if (this->player->anime_timer.TimeUp())
		SetState(StateName::Idle);
	this->player->anime_timer++;
}

void Player::StateDamage::SetState(StateName state)
{
	if(state == StateName::Idle)
		State::SetState(state);
}
