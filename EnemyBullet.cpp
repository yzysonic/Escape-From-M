#include "EnemyBullet.h"

Vector3 BulletSpeed; // ����

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
//	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
//	for (int i = 0; i < BULLET_MAX; i++)
//	{
//		if (use == false)		// ���g�p��Ԃ̃o���b�g��������
//		{
//			use = true;		// �g�p��Ԃ֕ύX����
//			this->transform.position = pos;		// ���W���Z�b�g
//			BulletSpeed = speed;	// �X�s�[�h
//
//			return;		// 1���Z�b�g�����̂ŏI������
//		}
//	}
//}
