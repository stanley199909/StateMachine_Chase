#pragma once
#include "Scene.h"
#include "Object.h"
#include "Sound.h"
// TitleSceneクラス
class TitleScene : public Scene
{
private:
	std::vector<Object*> m_MySceneObjects; // このシーンのオブジェクト

	void Init() override; // 初期化
	void Uninit() override; // 終了処理
	Sound m_Sound;

public:
	TitleScene(); // コンストラクタ
	~TitleScene(); // デストラクタ

	void Update() override; // 更新
};

