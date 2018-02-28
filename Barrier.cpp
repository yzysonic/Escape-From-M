#include "Barrier.h"

Barrier::Barrier(void)
{
	AddComponent<StaticModel>("barrier", Layer::MASK);
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
