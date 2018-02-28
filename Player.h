#pragma once
#include "Core/Core.h"
#include "Shadow.h"

#define KeyAtkShort	DIK_J
#define KeyAtkLong	DIK_K
#define KeyAtkArea	DIK_L

class Player : public Object
{
public:
	static constexpr int MaxHp = 20;
	static constexpr int MaxAtk = 3;

	int hp;
	int atk;

	enum class AnimeState
	{
		Running,
		Injure,
		AttackShort,
		AttackLong,
		AttackArea,
		Idle,
	} anime_state;

	Event event_move;

	Player(void);
	~Player(void);
	void Update(void) override;

	// プレイヤーのATK値を1単位上げる、MAXになるとそれ以上増えない。
	void AtkUp(void);


private:
	SkinnedModel* model;
	Shadow* shadow;
	Vector3 control;
	FrameTimer anime_timer;
	float speed;

	void Move(void);
};