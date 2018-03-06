#include "AttackTarget.h"

AttackTarget::AttackTarget(void)
{
	this->hp = this->max_hp = 1;
	this->uihp = new UIHP(this);
	this->uihp->SetOpacity(0.0f);
	this->radius = 0.0f;
	this->damage_timer.Reset(0.0f);
}

AttackTarget::~AttackTarget(void)
{
	this->uihp->Destroy();
}

int AttackTarget::GetHp(void)
{
	return this->hp;
}

Vector3 AttackTarget::GetAtkPos(Object * attacker)
{
	return this->radius*(attacker->transform.position - this->transform.position).normalized() + this->transform.position;
}

void AttackTarget::Damage(int point)
{
	if (!this->damage_timer.TimeUp())
		return;

	if (this->hp > 0)
	{
		this->uihp->SetOpacity(1.0f);
		this->hp -= point;
		this->uihp->SetPercent((float)this->hp / max_hp);

		if (this->hp == 0)
			this->event_death();
	}

	this->event_damage();

	this->damage_timer.Reset();

}
