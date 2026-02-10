#include "Game.h"
#include "Renderer.h"
#include "Input.h"

Game* Game::m_Instance; //ゲームインスタンス
Sound Game::g_Sound;
bool Game::s_SoundReady = false;
ID3D11Buffer* Game::s_FadeVB = nullptr;
ID3D11Buffer* Game::s_FadeIB = nullptr;
ID3D11RasterizerState* Game::s_ScissorState = nullptr;
// コンストラクタ
Game::Game()
{
	m_Scene = nullptr;
	
}

// デストラクタ
Game::~Game()
{
	delete m_Scene;
	DeleteAllObject(); //すべてのオブジェクトを削除する
}

// 初期化
void Game::Init()
{
	//インスタンス作成
	m_Instance = new Game;

	// 描画終了処理
	Renderer::Init();

	// 入力処理初期化
	Input::Create();

	// カメラ初期化
	m_Instance->m_Camera.Init();
	m_Instance->m_Scene = new TitleScene;
	//=======================================
	//  サウンドシステム
	//=======================================
	if (!s_SoundReady) {
		HRESULT hr = g_Sound.Init();
		if (SUCCEEDED(hr)) s_SoundReady = true;
	}
	

}

// 更新
void Game::Update()
{
	//入力処理更新
	Input::Update();

	//シーン更新
	m_Instance->m_Scene->Update();

	// カメラ更新
	m_Instance->m_Camera.Update();

	
	//オブジェクト更新
		//for (auto& o : m_Instance->m_Objects)
		//{
		//	o->Update();
		//}
	for (size_t i = 0; i < m_Instance->m_Objects.size(); )
	{
		if (m_Instance->m_Objects[i]) {
			m_Instance->m_Objects[i]->Update();
			++i;	
		}
		else {
		
			m_Instance->m_Objects.erase(m_Instance->m_Objects.begin() + i);
		}
	}

}

// 描画
void Game::Draw()
{
	// 描画前処理
	Renderer::DrawStart();


	//オブジェクト描画
	for (auto& o : m_Instance->m_Objects)
	{
		o->Draw(&m_Instance->m_Camera);
	}

	// 描画後処理
	Renderer::DrawEnd();

}

// 終了処理
void Game::Uninit()
{
	// カメラ終了処理
	m_Instance->m_Camera.Uninit();
	g_Sound.Uninit();

	//オブジェクト終了処理
	for (auto& o : m_Instance->m_Objects)
	{
		o->Uninit();
	}
	//入力処理終了
	Input::Release();
	// 描画終了処理
	Renderer::Uninit();

	//インスタンス削除
	delete m_Instance;
	if (s_FadeVB) s_FadeVB->Release();
	if (s_FadeIB) s_FadeIB->Release();
	if (s_ScissorState) s_ScissorState->Release();
}

//インスタンスを取得
Game* Game::GetInstance()
{
	return m_Instance;
}

//シーンを切り替える
void Game::ChangeScene(SceneName sName)
{
	
	////読み込み済みのシーンがあれば削除
	//int score = 0;
	if (m_Instance->m_Scene != nullptr)
	{
		////消そうとしているシーンがStage1ならスコアを保存しておく
		//if (Stage1Scene* sObj = dynamic_cast<Stage1Scene*>(m_Instance->m_Scene))
		//{
		//	score = sObj->GetScore();
		//}
		delete m_Instance->m_Scene;
		m_Instance->m_Scene = nullptr;
	}

	switch (sName)
	{
	case TITLE:	
		m_Instance->m_Scene = new TitleScene; //メモリを確保
		break;
	case LOADINGSTAGE1:
		m_Instance->m_Scene = new LoadingScene(STAGE1);
		break;
	case STAGE1:
		m_Instance->m_Scene = new Stage1Scene; //メモリを確保
		break;
	case GAMEOVER:
		m_Instance->m_Scene = new GameOverScene; //メモリを確保
		/*dynamic_cast<GameOverScene*>(m_Instance->m_Scene)->SetScore(score);*/ //スコアを設定
		break;
	case GAMECLEAR:
		m_Instance->m_Scene = new GameClearScene; //メモリを確保
		/*dynamic_cast<GameOverScene*>(m_Instance->m_Scene)->SetScore(score);*/ //スコアを設定
		break;
	}
}

//オブジェクトを削除する
void Game::DeleteObject(Object* pt)
{
	if (pt == NULL)
		return;
	pt->Uninit(); //終了処理

	//要素を削除する
	erase_if(m_Instance->m_Objects, [pt](const std::unique_ptr<Object>& element)
		{
			return element.get() == pt;
		});
	m_Instance->m_Objects.shrink_to_fit();
}

//オブジェクトをすべて削除する
void Game::DeleteAllObject()
{
	//オブジェクト終了処理
	for (auto& o : m_Instance->m_Objects)
	{
		o->Uninit();
	}
	m_Instance->m_Objects.clear(); //すべて削除
	m_Instance->m_Objects.shrink_to_fit();
}

void Game::PlaySound(SOUND_LABEL label)
{
	if (!s_SoundReady) {
		HRESULT hr = g_Sound.Init();
		if (SUCCEEDED(hr)) {
			s_SoundReady = true;
			std::cout << "Sound auto-init OK" << std::endl;
		}
		else {
			std::cout << "Sound auto-init failed: " << hr << std::endl;
			return;
		}
	}
	g_Sound.Play(label);
}

void Game::StopSound(SOUND_LABEL label)
{
	g_Sound.Stop(label);
}

void Game::ResumeSound(SOUND_LABEL label)
{
	g_Sound.Resume(label);
}

