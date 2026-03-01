#pragma once
#include "Scene.h"
#include "Object.h"
#include "Sound.h"
#include "Animation.h"
#include "Texture2D.h"

// TitleSceneクラス
class TitleScene : public Scene
{
private:
	std::vector<Object*> m_MySceneObjects; // このシーンのオブジェクト

	void Init() override; // 初期化
	void Uninit() override; // 終了処理
	Sound m_Sound;
	

	//=======================================
	//  ゲームスタートボタン
	//=======================================
	Texture2D* m_GameStartButton = nullptr; 
	float m_ButtonUnpressTimer = 0.0f;      
	float m_ButtonPressedTimer = 0.0f;      
	bool m_ButtonPressed = false;           
	bool m_BgmPlayed = false;

public:
	TitleScene(); // コンストラクタ
	~TitleScene(); // デストラクタ

	void Update() override; // 更新
};

