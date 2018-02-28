#include "MagicSquare.h"

MagicSquare::MagicSquare(void)
{
	AddComponent<RectPolygon>("magic_square")->SetSize(Vector2(50.0f, 50.0f));
	this->transform.position.y += 0.01f;
	this->transform.setRotation(0.5f*PI, 0.0f, 0.0f);

	this->rotation_speed = 0.01f;
	this->color_change_speed = 1.0f;
}

void MagicSquare::Update(void)
{
	this->transform.rotate(0.0f, rotation_speed, 0.0f);

	char c = (UCHAR)(255 * (0.7f + 0.3f*sinf(color_change_speed*this->timer.Elapsed()*2.0f + PI)));
	this->GetComponent<RectPolygon>()->SetColor(Color(c, c, 255, 255));

	this->timer++;
}

void MagicSquare::OnDraw(void)
{
	auto pDevice = Direct3D::GetDevice();

	// 加算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ライトなし
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

}

void MagicSquare::AfterDraw(void)
{
	auto pDevice = Direct3D::GetDevice();

	// 通常ブレンド
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ライトあり
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
