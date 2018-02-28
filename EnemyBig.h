#pragma once
#include "Core/Core.h"

class EnemyBig : public Object
{
public:
	Object* target;

	EnemyBig(void);
	void Update(void) override;

};