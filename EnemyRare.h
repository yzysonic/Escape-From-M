#pragma once
#include "Core/Core.h"

#define ENEMY_RARE (30)
#define SPEED (1.0f)

class EnemyRare : public Object
{
public:
	Object* target;
	FrameTimer timer;

	EnemyRare(void);
	void Update(void) override;
	//D3DXVECTOR3 GetPositionEnemyRare(void);

};