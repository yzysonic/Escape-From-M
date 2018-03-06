#include "PlayerBullet.h"
#include "AttackTarget.h"

PlayerBullet::PlayerBullet(Transform transform, int atk)
{
	this->type = ObjectType::Bullet;

	this->transform.position = transform.position;
	this->transform.setRotation(transform.getRotation());
	this->transform.scale *= InitSize;

	this->billboard = AddComponent<Billboard>("bullet_player");
	this->collider = AddComponent<SphereCollider>();
	this->collider->radius = 0.5f*InitSize;

	this->timer.Reset(0.1f);
	this->atk = atk;
}

void PlayerBullet::OnCollision(Object * other)
{
	if (other->type == ObjectType::Enemy)
	{
		auto target = dynamic_cast<AttackTarget*>(other);
		target->Damage(atk);
	}
	else if (other->type == ObjectType::Bullet_E)
	{
		other->Destroy();
	}

}

void PlayerBullet::OnDraw(void)
{
	auto pDevice = Direct3D::GetDevice();

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
}

void PlayerBullet::AfterDraw(void)
{
	auto pDevice = Direct3D::GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
