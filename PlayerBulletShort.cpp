#include "PlayerBulletShort.h"

PlayerBulletShort::PlayerBulletShort(Vector3 pos)
{
	AddComponent<Billboard>("player_bullet");
	AddComponent<SphereCollider>()->radius = 1.5f;

	this->type = ObjectType::Bullet;
	this->transform.position = pos;
	this->transform.scale *= 3.0f;
	this->timer.Reset(0.7f);
}

void PlayerBulletShort::Update(void)
{
	if (this->timer.TimeUp())
	{
		this->Destroy();
	}

	this->timer++;
}

void PlayerBulletShort::OnCollision(Object * other)
{
	if (other->type == ObjectType::Enemy)
	{
		this->Destroy();
	}
}

void PlayerBulletShort::OnDraw(void)
{
	auto pDevice = Direct3D::GetDevice();

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
}

void PlayerBulletShort::AfterDraw(void)
{
	auto pDevice = Direct3D::GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
