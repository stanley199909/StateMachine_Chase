#pragma once
#include "Scene.h"
#include "Object.h"
#include "Sound.h"
#include "Game.h"
// Loading Sceneクラス
class LoadingScene : public Scene
{
private:
	std::vector<Object*> m_MySceneObjects; // このシーンのオブジェクト
	SceneName m_NextScene = SceneName::TITLE;
	int m_LoadingProgress = 0;

	void Init() override; // 初期化
	void Uninit() override; // 終了処理
	//使わない可能性があります
	Sound m_Sound;

public:
	LoadingScene(SceneName nextScene); // コンストラクタ
	~LoadingScene(); // デストラクタ
	void Update() override; // 更新
};