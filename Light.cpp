#include "Light.h"
#include "Core/Direct3D.h"

D3DLIGHT9 Light::light[NUM_LIGHT];
Light* Light::instance = nullptr;

//=============================================================================
// ライトの初期化処理
//=============================================================================
void Light::Init(void)
{
	if (instance == nullptr)
		instance = new Light;

	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetDevice();
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&light[0], sizeof(D3DLIGHT9));

	// ライト0のタイプの設定
	light[0].Type = D3DLIGHT_DIRECTIONAL;

	// ライト0の拡散光の設定
	light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//g_aLight[0].Ambient = D3DXCOLOR(0.7f, 0.76f, 0.8f, 1.0f);

	// ライト0の方向の設定
	vecDir = D3DXVECTOR3(968.0f, -934.0f, 2689.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light[0].Direction, &vecDir);

	// ライト0をレンダリングパイプラインに設定
	pDevice->SetLight(0, &light[0]);

	// ライト0を使用使用状態に
	pDevice->LightEnable(0, TRUE);


	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&light[1], sizeof(D3DLIGHT9));

	// ライト1のタイプの設定
	light[1].Type = D3DLIGHT_DIRECTIONAL;

	// ライト1の拡散光の設定
	light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//g_aLight[1].Ambient = D3DXCOLOR(0.7f, 0.76f, 0.8f, 1.0f);

	// ライト1の方向の設定
	vecDir = D3DXVECTOR3(968.0f, -934.0f, 2689.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light[1].Direction, &vecDir);

	// ライト1をレンダリングパイプラインに設定
	pDevice->SetLight(1, &light[1]);

	// ライト1の設定
	pDevice->LightEnable(1, TRUE);

	// ライティングモードをON
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
