#include "Shadow.h"

Shadow::Shadow(Object* target)
{
	AddComponent<RectPolygon>("shadow", Layer::MASK);
	this->transform.setRotation(0.5f*PI, 0.0f, 0.0f);
	this->transform.position.y += 0.01f;
	this->target = &target->transform;
}

void Shadow::Update(void)
{
	this->transform.position.x = this->target->position.x;
	this->transform.position.z = this->target->position.z;
}

void Shadow::OnDraw(void)
{
	auto pDevice = Direct3D::GetDevice();

	// 減算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ライトなし
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

}

void Shadow::AfterDraw(void)
{
	auto pDevice = Direct3D::GetDevice();

	// 通常ブレンド
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ライトあり
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
