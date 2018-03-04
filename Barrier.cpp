#include "Barrier.h"

Barrier::Barrier(void)
{
	AddComponent<StaticModel>("barrier", Layer::MASK);
	this->hp = MaxHP;
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

int Barrier::GetHp(void)
{
	return this->hp;
}

Vector3 Barrier::GetAtkPos(Object* enemy)
{
	return Radius*(enemy->transform.position - this->transform.position).normalized() + this->transform.position;
}
