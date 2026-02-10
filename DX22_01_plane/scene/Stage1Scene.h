#pragma once
#include "Scene.h"
#include "Object.h"

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




public:
	Stage1Scene(); // コンストラクタ
	~Stage1Scene(); // デストラクタ

	void Update() override; // 更新
	void InitStageData();
	int GetScore() const; //スコアを取得

	void StopAllSE();
};

