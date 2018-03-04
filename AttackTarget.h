#pragma once
#include "Core\Core.h"
#include "UIHP.h"

class AttackTarget : public Object
{
public:
	Event event_death;
	Event event_damage;

	AttackTarget(void);
	~AttackTarget(void);
	virtual int GetHp(void);
	virtual Vector3 GetAtkPos(Object* attacker);
	virtual void Damage(int point);

protected:
	int hp;
	int max_hp;
	float radius;
	UIHP* uihp;
	FrameTimer damage_timer;
};