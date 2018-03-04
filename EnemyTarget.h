#pragma once
#include "Core\Core.h"

class EnemyTarget : public Object
{
public:
	virtual int GetHp(void) = 0;
	virtual Vector3 GetAtkPos(Object* enemy) = 0;
};