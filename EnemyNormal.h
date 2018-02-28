#pragma once
#include "Core/Core.h"

#define ENEMYNORMAL_MAX (70)

class EnemyNormal : public Object
{
public:
	Object* target;

	EnemyNormal(void);
	void Update(void) override;

};