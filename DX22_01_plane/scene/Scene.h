#pragma once
#include <memory>
#include "Camera.h"
enum SceneName
{
	TITLE,
	LOADINGSTAGE1,
	STAGE1,
	GAMEOVER,
	GAMECLEAR
};
//Scene クラス
class Scene
{
public:

	Scene(); // コンストラクタ
	virtual ~Scene(); // デストラクタ(virtualが必要)

	
	virtual void Init() {}  // （純粋仮想関数）
	virtual void Update() = 0; // （純粋仮想関数）
	virtual void Draw(Camera* cam) {}  // （純粋仮想関数）
	virtual void Uninit() {}  // （純粋仮想関数）
};
