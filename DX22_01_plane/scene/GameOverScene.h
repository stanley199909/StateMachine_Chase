#pragma once
#include "Scene.h"
#include "Object.h"

// ResultSceneクラス
class GameOverScene : public Scene
{
private:
	std::vector<Object*> m_MySceneObjects; // このシーンのオブジェクト

	void Init(); // 初期化
	void Uninit(); // 終了処理

public:
	GameOverScene(); // コンストラクタ
	~GameOverScene(); // デストラクタ

	void Update() override; // 更新

	void SetScore(int c); //スコア設定
};

