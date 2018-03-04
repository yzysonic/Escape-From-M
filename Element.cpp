#include "Element.h"

Element::Element(Vector3 pos)
{
	this->type = ObjectType::Element;

	AddComponent<Billboard>("element", Layer::UI_00);
	AddComponent<SphereCollider>()->radius = 3.0f;
	this->transform.position = pos;
	this->transform.scale = 2.0f*Vector3::one;
	this->target = &ObjectManager::GetObjectByType(ObjectType::Player)->transform;
	this->delay_timer.Reset(Randomf(0.0f, 0.5f));
}

void Element::Update(void)
{
	if (!this->target)
		return;

	if(this->delay_timer.TimeUp())
		this->transform.position = Vector3::Lerp(this->transform.position, this->target->position+Vector3(0.0f, 4.0f, 0.0f), 0.05f);
	else
		this->delay_timer++;
}

void Element::OnCollision(Object * other)
{
	if (other->type == ObjectType::Player)
		this->Destroy();
}

void Element::OnDraw(void)
{
	auto pDevice = Direct3D::GetDevice();

	// 加算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ライトなし
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

}

void Element::AfterDraw(void)
{
	auto pDevice = Direct3D::GetDevice();

	// 通常ブレンド
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ライトあり
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
