#pragma once
#include "Core/Core.h"
#include "Shadow.h"

class Player : public Object
{
public:
	enum class AnimeState
	{
		Running,
		Idle,
	} anime_state;

	Event event_move;

	Player(void);
	~Player(void);
	void Update(void) override;

private:
	SkinnedModel* model;
	Shadow* shadow;
	Vector3 control;
	float speed;

	void Move(void);
};