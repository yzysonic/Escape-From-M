#pragma once
#include "Core/Core.h"
#include "EnemyNormal.h"
#include "EnemyBullet.h"
#include "EnemyRare.h"
#include "EnemyBig.h"

class SceneMakotoTest : public Scene
{
public:
	void Init(void)override;
	void Update(void)override;

private:
	Object* test_obj;
	Object* test_obj1;
	Object* test_obj2;
	EnemyNormal* player;
	EnemyBullet* bullet;
	EnemyRare* rare;
	EnemyBig* big;
	Camera* camera;
};