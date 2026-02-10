#include "GameClearScene.h"
#include "Game.h"
#include "Input.h"
#include "Texture2D.h"

// コンストラクタ
GameClearScene::GameClearScene()
{
	Init();
}

// デストラクタ
GameClearScene::~GameClearScene()
{
	Uninit();
}

// 初期化
void GameClearScene::Init()
{
	//背景画像オブジェクトを作成
	Texture2D* pt = Game::GetInstance()->AddObject<Texture2D>();
	pt->SetTexture("assets/texture/GameClearScene.png"); //画像を指定
	pt->SetScale(1280.0f, 720.0f, 0.0f); //大きさを指定
	m_MySceneObjects.emplace_back(pt);

	Texture2D* pt2 = Game::GetInstance()->AddObject<Texture2D>();
	pt2->SetTexture("assets/texture/GameClearLogo.png"); //画像を指定
	pt2->SetPosition(0.0f, 200.0f, 0.0f); //位置を指定
	pt2->SetRotation(0.0f, 0.0f, 0.0f); //角度を指定
	pt2->SetScale(1000.0f, 480.0f, 0.0f); //大きさを指定
	m_MySceneObjects.emplace_back(pt2);

	////人オブジェクトを作成
	//Texture2D* pt3 = Game::GetInstance()->AddObject<Texture2D>();
	//pt3->SetTexture("assets/texture/golf_jou_man.png"); //画像を指定
	//pt3->SetPosition(-300.0f, 0.0f, 0.0f); //位置を指定
	//pt3->SetScale(361.0f, 400.0f, 0.0f); //大きさを指定
	//m_MySceneObjects.emplace_back(pt3);

}

// 更新
void GameClearScene::Update()
{
	// エンターキーを押してタイトルへ
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Game::StopSound(SOUND_LABEL_SE002);
		Game::GetInstance()->ChangeScene(TITLE);
	}
}

// 終了処理
void GameClearScene::Uninit()
{
	// このシーンのオブジェクトを削除する
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
	m_MySceneObjects.clear();
}

//スコアを設定
void GameClearScene::SetScore(int c)
{
	////リザルト文字列オブジェクト
	//Texture2D* stringObj = dynamic_cast<Texture2D*>(m_MySceneObjects[1]);

	//switch (c)
	//{
	//case -4:
	//	stringObj->SetUV(1, 2, 1, 13); //-4
	//	break;
	//case -3:
	//	stringObj->SetUV(1, 3, 1, 13); //-3	
	//	break;
	//case -2:
	//	stringObj->SetUV(1, 4, 1, 13); //-2	
	//	break;
	//case -1:
	//	stringObj->SetUV(1, 5, 1, 13); //-1	
	//	break;
	//case 0:
	//	stringObj->SetUV(1, 6, 1, 13); //0	
	//	break;
	//case 1:
	//	stringObj->SetUV(1, 7, 1, 13); //1	
	//	break;
	//case 2:
	//	stringObj->SetUV(1, 8, 1, 13); //2	
	//	break;
	//case 3:
	//	stringObj->SetUV(1, 9, 1, 13); //3	
	//	break;
	//case 4:
	//	stringObj->SetUV(1, 10, 1, 13); //4	
	//	break;
	//case 5:
	//	stringObj->SetUV(1, 11, 1, 13); //5	
	//	break;
	//case 6:
	//	stringObj->SetUV(1, 12, 1, 13); //6	
	//	break;
	//case 7:
	//	stringObj->SetUV(1, 13, 1, 13); //7	
	//	break;



	//}
}