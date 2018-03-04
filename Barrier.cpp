#include "Barrier.h"

Barrier::Barrier(void)
{
	this->type = ObjectType::EnemyTarget;

	AddComponent<StaticModel>("barrier", Layer::MASK);
	AddComponent<SphereCollider>()->radius = Radius;

	// AttackTarget‰Šú‰»
	this->uihp->offset_y = Radius + 3.0f;
	this->uihp->SetColor(Color::blue);
	this->uihp->SetOpacity(0.0f);
	this->uihp->SetSize(70.0f, UIHP::Height);
	this->hp = this->max_hp = MaxHp;
	this->radius = Radius;
	this->event_death += [&]
	{
		this->uihp->SetOpacity(0.0f);
		this->SetActive(false);
	};
}

void Barrier::Uninit(void)
{
	this->uihp->Destroy();
}

void Barrier::OnDraw(void)
{
	//PixelShader* shader = PixelShader::Get("BarrierPS");
	//Direct3D::GetDevice()->SetPixelShader(shader->pD3DShader);
	//shader->SetFloatArray("view", (float*)&(this->transform.position-Renderer::GetInstance()->getCamera()->transform.position), 3);
}

void Barrier::AfterDraw(void)
{
	//Direct3D::GetDevice()->SetPixelShader(NULL);
}