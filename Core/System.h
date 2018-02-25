#pragma once

#include "Common.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
class System
{
public:
	static HRESULT Init(void);	//システムの初期化処理
	static void Uninit(void);	//システムの終了処理
};