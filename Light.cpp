#include "Light.h"
#include "Core/Direct3D.h"

D3DLIGHT9 Light::light[NUM_LIGHT];
Light* Light::instance = nullptr;

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void Light::Init(void)
{
	if (instance == nullptr)
		instance = new Light;

	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetDevice();
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&light[0], sizeof(D3DLIGHT9));

	// ���C�g0�̃^�C�v�̐ݒ�
	light[0].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g0�̊g�U���̐ݒ�
	light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//g_aLight[0].Ambient = D3DXCOLOR(0.7f, 0.76f, 0.8f, 1.0f);

	// ���C�g0�̕����̐ݒ�
	vecDir = D3DXVECTOR3(968.0f, -934.0f, 2689.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light[0].Direction, &vecDir);

	// ���C�g0�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(0, &light[0]);

	// ���C�g0���g�p�g�p��Ԃ�
	pDevice->LightEnable(0, TRUE);


	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&light[1], sizeof(D3DLIGHT9));

	// ���C�g1�̃^�C�v�̐ݒ�
	light[1].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g1�̊g�U���̐ݒ�
	light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//g_aLight[1].Ambient = D3DXCOLOR(0.7f, 0.76f, 0.8f, 1.0f);

	// ���C�g1�̕����̐ݒ�
	vecDir = D3DXVECTOR3(968.0f, -934.0f, 2689.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light[1].Direction, &vecDir);

	// ���C�g1�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(1, &light[1]);

	// ���C�g1�̐ݒ�
	pDevice->LightEnable(1, TRUE);

	// ���C�e�B���O���[�h��ON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(233, 255, 210, 255));
}

Light* Light::GetInstance(void)
{
	return instance;
}

HRESULT Light::OnLostDevice(void)
{
	return S_OK;
}

HRESULT Light::OnResetDevice(void)
{
	Init();
	return S_OK;
}
