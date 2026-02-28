#pragma once
#include "Scene.h"
#include "Object.h"
#include "Texture2D.h"
// Stage1Scenクラス
class Stage1Scene : public Scene
{
private:
	std::vector<Object*> m_MySceneObjects; // このシーンのオブジェクト
	// =======================================
	//  境界チェック（マップから出たらリスタート）
	// =======================================
	const float MAP_BOUNDARY_X = 100.0f;
	const float MAP_BOUNDARY_Z = 250.0f;


	void Init() override; // 初期化
	void Uninit() override; // 終了処理

	// =======================================
	//  ゲームUI相関(タイマー、操作など)
	// =======================================
	const float dt = 1.0f / 60.0f;
	
	Texture2D* m_TimerFill = nullptr;
	float m_TimerProgress = 0.0f;
	float m_TimerSpeed = 1.0f / 2000.0f;  
	bool m_TimerFullTriggered = false;

	// 警戒一番高いEnemyを表示
	Texture2D* m_HighestAlertFill = nullptr;
	float m_HighestAlertValue = 0.0f;
	

public:
	Stage1Scene(); // コンストラクタ
	~Stage1Scene(); // デストラクタ

	void Update() override; // 更新
	void InitStageData();
	void InitUIData();
	int GetScore() const; //スコアを取得
	
	// =======================================
	//  タイマーカウント
	// =======================================
	void GameLoopUIUpdate();

	void StopAllSE();


};

