
#include "TitleScene.h"
#include "Game.h"
#include "Input.h"
#include "Texture2D.h"



// コンストラクタ
TitleScene::TitleScene()
{

	Init();
}

// デストラクタ
TitleScene::~TitleScene()
{
	Uninit();
}

// 初期化
void TitleScene::Init()
{
	//背景画像オブジェクトを作成
	Texture2D* pt = Game::GetInstance()->AddObject<Texture2D>();
	pt->SetTexture("assets/texture/TitleScene.png"); //画像を指定
	pt->SetPosition(0.0f, 0.0f, 0.0f); //位置を指定
	pt->SetRotation(0.0f, 0.0f, 0.0f); //角度を指定
	pt->SetScale(1280.0f, 720.0f, 0.0f); //大きさを指定
	m_MySceneObjects.emplace_back(pt);

	Texture2D* pt2 = Game::GetInstance()->AddObject<Texture2D>();
	pt2->SetTexture("assets/texture/TitleLogo.png"); //画像を指定
	pt2->SetPosition(0.0f, 300.0f, 0.0f); //位置を指定
	pt2->SetRotation(0.0f, 0.0f, 0.0f); //角度を指定
	pt2->SetScale(500.0f, 240.0f, 0.0f); //大きさを指定
	m_MySceneObjects.emplace_back(pt2);

	Game::PlaySound(SOUND_LABEL_BGM000);

}

// 更新
void TitleScene::Update()
{
	// エンターキーを押してステージ1へ
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Game::StopSound(SOUND_LABEL_BGM000);
		Game::GetInstance()->ChangeScene(LOADINGSTAGE1);
	}
}

// 終了処理
void TitleScene::Uninit()
{
	// このシーンのオブジェクトを削除する
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
	m_MySceneObjects.clear();

}
