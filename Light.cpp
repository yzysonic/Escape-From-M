#include "Light.h"
#include "Core/Direct3D.h"

#define	NUM_LIGHT (2)	// ���C�g�̐�

D3DLIGHT9 g_aLight[NUM_LIGHT];	// ���C�g���

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetDevice();
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	// ���C�g0�̃^�C�v�̐ݒ�
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g0�̊g�U���̐ݒ�
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aLight[0].Ambient = D3DXCOLOR(0.7f, 0.76f, 0.8f, 1.0f);

	// ���C�g0�̕����̐ݒ�
	vecDir = D3DXVECTOR3(968.0f, -934.0f, 2689.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);

	// ���C�g0�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(0, &g_aLight[0]);

	// ���C�g0���g�p�g�p��Ԃ�
	pDevice->LightEnable(0, TRUE);


	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&g_aLight[1], sizeof(D3DLIGHT9));

	// ���C�g1�̃^�C�v�̐ݒ�
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g1�̊g�U���̐ݒ�
	g_aLight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//g_aLight[1].Ambient = D3DXCOLOR(0.7f, 0.76f, 0.8f, 1.0f);

	// ���C�g1�̕����̐ݒ�
	vecDir = D3DXVECTOR3(968.0f, -934.0f, 2689.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1].Direction, &vecDir);

	// ���C�g1�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(1, &g_aLight[1]);

	// ���C�g1�̐ݒ�
	pDevice->LightEnable(1, TRUE);

	// ���C�e�B���O���[�h��ON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.7f, 0.76f, 0.8f, 1.0f));
}
