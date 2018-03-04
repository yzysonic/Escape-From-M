#include "SceneTitle.h"
#include "Core\Game.h"
#include "FadeScreen.h"
#include "SceneGame.h"

// 初期化
void SceneTitle::Init(void)
{
	this->background = new Object;
	this->background->AddComponent<RectPolygon2D>("forest", Layer::BG_00)->SetSize((float)SystemParameters::ResolutionX, (float)SystemParameters::ResolutionY);

	this->logo = (new Object);
	this->logo->AddComponent<RectPolygon2D>("title_logo", Layer::UI_00);
	this->logo->transform.position = Vector3(0, SystemParameters::ResolutionY / 2.f - 200, 0);

	this->info = (new Object);
	this->info->AddComponent<RectPolygon2D>("title_info", Layer::UI_00);
	this->info->transform.position.x = SystemParameters::ResolutionX / 2 - this->info->GetComponent<RectPolygon2D>()->pTexture->size.x / 2 - 30;
	this->info->transform.position.y = -SystemParameters::ResolutionY / 2 + this->info->GetComponent<RectPolygon2D>()->pTexture->size.y + 10;
	this->info->transform.position.z = 0;

	this->cursor = (new Object);
	this->cursor->AddComponent<RectPolygon2D>("title_cursor", Layer::UI_00);
	this->cursor->transform.position = Vector3(-90, SystemParameters::ResolutionY / 2.f - 415, 0);

	this->start = (new Object);
	this->start->AddComponent<RectPolygon2D>("title_start", Layer::UI_00);
	this->start->transform.position = Vector3(40, SystemParameters::ResolutionY / 2.f - 415, 0);
	
	this->exit = (new Object);
	this->exit->AddComponent<RectPolygon2D>("title_exit", Layer::UI_00);
	this->exit->transform.position = Vector3(40 + 0.5f*(this->exit->GetComponent<RectPolygon2D>()->GetSize().x - this->start->GetComponent<RectPolygon2D>()->GetSize().x), SystemParameters::ResolutionY / 2.f - 500, 0);

	// カメラの初期化
	this->camera = new Camera;
	this->camera->setBackColor(10, 10, 10, 255);
	Renderer::GetInstance()->setCamera(this->camera);

	// ライティングオフ
	Direct3D::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	// フェイトイン
	FadeScreen::FadeIn(Color::black, 0.7f);

	this->state = StateWaitFade;
	this->com = COM_OP;
	this->cursorPos = 0;

	
}

// 更新処理
void SceneTitle::Update(void)
{
	switch (this->state)
	{
	case StateWaitFade:

		if (FadeScreen::Finished())
		{
			switch (this->com)
			{
			case COM_OP:

				// BGM再生
				//SetVolume(BGM_TITLE, -1800);
				//PlayBGM(BGM_TITLE);


				// 状態遷移
				this->state = StateNormal;
				break;

			case COM_START:
				// シーン遷移
				GameManager::SetScene(new SceneGame);
				break;

			case COM_EXIT:
				// ゲーム終了
				Game::Stop();
				break;
			}
		}


		break;

	// メニュー操作
	case StateNormal:

		if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(0, BUTTON_UP))
		{
			if (this->cursorPos > 0)
			{
				this->cursor->transform.position.y += 85;
				this->cursorPos--;
			}
		}
		if (GetKeyboardTrigger(DIK_DOWN) || IsButtonTriggered(0, BUTTON_DOWN))
		{
			if (this->cursorPos < 1)
			{
				this->cursor->transform.position.y -= 85;
				this->cursorPos++;
			}
		}
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_CI))
		{
			this->com = (Command)this->cursorPos;

			this->state = StateWaitFade;
			FadeScreen::FadeOut(Color::black);
		}

		break;
	}


}

// 終了処理
void SceneTitle::Uninit(void)
{
	//StopSound(BGM_TITLE);
	Renderer::GetInstance()->setCamera(nullptr);
}