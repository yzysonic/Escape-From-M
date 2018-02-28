#include "EnemyBullet.h"

Vector3 BulletSpeed; // 速さ

EnemyBullet::EnemyBullet(void)
{
	this->AddComponent<RectPolygon>("bullet01");
	this->transform.position = Vector3(0.0f, 0.0f, 0.0f);
}

void EnemyBullet::Update(void)
{

	this->transform.position += Vector3(-20.0f, 0.0f, 0.0f);
}

//void EnemyBullet::SetBullet(Vector3 pos, Vector3 speed)
//{
//	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
//	for (int i = 0; i < BULLET_MAX; i++)
//	{
//		if (use == false)		// 未使用状態のバレットを見つける
//		{
//			use = true;		// 使用状態へ変更する
//			this->transform.position = pos;		// 座標をセット
//			BulletSpeed = speed;	// スピード
//
//			return;		// 1発セットしたので終了する
//		}
//	}
//}
