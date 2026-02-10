#include "Ground.h"
#include "stb_image.h"
#include <iostream>
using namespace DirectX::SimpleMath;

Ground::Ground()
{
	SetType(ObjectType::GROUND);
}

Ground::~Ground()
{

}

//=======================================
//初期化処理
//=======================================
void Ground::Init()
{
	// 3Dモデルデータ (Mayaで出力した床のFBX)
	std::u8string modelFile = u8"assets/model/road/RoadSpare.fbx";

	// テクスチャディレクトリ
	std::string texDirectory = "assets/model/road/textures";

	// モデル読み込み (Objectクラスの機能を使用)
	
	LoadModel(modelFile, texDirectory, Vector3(1.0f, 1.0f, 1.0f));
	
	//FBX のテクスチャを自分のテクスチャで置き換える
	m_Textures.clear();  // FBX から読み込んだテクスチャをクリア


	
	SetPosition(Vector3(0.0f, -10.0f, 0.0f));



}

//=======================================
//更新処理
//=======================================
void Ground::Update()
{

}

//=======================================
//描画処理
//=======================================
void Ground::Draw(Camera* cam)
{
	cam->SetCamera();

	m_Texture.SetGPU();

	Object::Draw(cam);
}

//=======================================
//終了処理
//=======================================
void Ground::Uninit()
{

}

//=======================================
//頂点情報を取得
//=======================================
std::vector<VERTEX_3D> Ground::GetVertices()
{
	std::vector<VERTEX_3D> res;
	res.resize(m_Vertices.size());

	//頂点情報を変換
	Matrix r = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	Matrix t = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	Matrix s = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);
	Matrix worldmtx = s * r * t;

	//ワールド変換してデータを代入
	for (int i = 0; i < m_Vertices.size(); i++)
	{
		res[i].position = Vector3::Transform(m_Vertices[i].position, worldmtx);
		res[i].normal = Vector3::Transform(m_Vertices[i].normal, worldmtx);
		res[i].color = m_Vertices[i].color;
		res[i].uv = m_Vertices[i].uv;
	}
	return res;
}