#pragma once
#include "Core\Core.h"
#include "AttackTarget.h"
#include "UIHP.h"

class Barrier : public AttackTarget
{
public:
	static constexpr int MaxHp = 20;
	static constexpr float Radius = 24.0f;

	Barrier(void);
	void Uninit(void) override;
	void OnDraw(void) override;
	void AfterDraw(void) override;

};