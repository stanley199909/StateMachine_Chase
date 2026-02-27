#include "Goal.h"
#include "stb_image.h"
Goal::Goal()
{
	SetType(ObjectType::GOAL);
}

Goal::~Goal()
{

}

//=======================================
//初期化処理
//=======================================
void Goal::Init()
{
	// 3Dモデルデータ (Mayaで出力した床のFBX)
	std::u8string modelFile = u8"assets/model/golf_pole/golf_pole_NO_HOLE.obj";

	// テクスチャディレクトリ
	std::string texDirectory = "assets/model/golf_pole";

	// モデル読み込み (Objectクラスの機能を使用)

	LoadModel(modelFile, texDirectory, Vector3(10.0f, 10.0f, 10.0f));

	// 位置設定 (Pivotが底面なら y=0 でOK)
	SetPosition(Vector3(200.0f, 0.0f, 0.0f));
}

//=======================================
//更新処理
//=======================================
void Goal::Update()
{

}

//=======================================
//描画処理
//=======================================
void Goal::Draw(Camera* cam)
{
	cam->SetCamera();


	Object::Draw(cam);
}

//=======================================
//終了処理
//=======================================
void Goal::Uninit()
{

}

