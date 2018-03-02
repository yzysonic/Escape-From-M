//=============================================================================
//
// ファイル名：main.cpp
// 作者：GP11A143 38 楊子毅
//
//=============================================================================
#include "Core/System.h"
#include "Core/Window.h"
#include "Core/Game.h"
#include "Core/GameManager.h"
#include "SceneGlobal.h"

#ifdef _DEBUG
#include "SceneTest.h"
#include "SceneMakotoTest.h"
#endif

// メモリリークの自動検出
#ifdef _DEBUG
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // メモリリーク自動検出
#endif

	// タイトル
	SystemParameters::windowTitle = "Escape From M";

	// システム初期化
	if (FAILED(System::Init()))
		return 1;

	// システムカーソルを隠す
	ShowCursor(true);

#ifndef _DEBUG
	Window::SetWindowMode(false);
#endif

	// ゲーム初期化
	Game::Init();

	// シーン初期化
	GameManager::GetInstance()->SetGlobalScene(new SceneGlobal);
#ifndef _DEBUG
	GameManager::GetInstance()->SetScene(new SceneTitle);
#else
	GameManager::GetInstance()->SetScene(new SceneTest);
#endif

	// ゲームループ
	Game::Run();

	// 終了
	Game::Uninit();
	System::Uninit();

	return 0;
}
