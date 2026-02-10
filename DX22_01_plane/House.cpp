#include "House.h"
#include "stb_image.h"
#include <iostream>
using namespace DirectX::SimpleMath;
House::House()
{
	SetType(ObjectType::BUILDING);
}

House::~House()
{
}

//=======================================
//初期化処理
//=======================================
void House::Init()
{
	// 3Dモデルデータ (Mayaで出力した床のFBX)

	std::u8string modelFile = u8"assets/model/building/house.fbx";
	

	// テクスチャディレクトリ
	std::string texDirectory = "assets/model/building";

	// モデル読み込み (Objectクラスの機能を使用)

	LoadModel(modelFile, texDirectory, Vector3(1.0f, 1.0f, 1.0f));

	//FBX のテクスチャを自分のテクスチャで置き換える
	m_Textures.clear();  // FBX から読み込んだテクスチャをクリア



	SetPosition(Vector3(0.0f, -100.0f, 0.0f));

}

//=======================================
//更新処理
//=======================================
void House::Update()
{

}

//=======================================
//描画処理
//=======================================
void House::Draw(Camera* cam)
{
	cam->SetCamera();

	m_Texture.SetGPU();

	Object::Draw(cam);
}

void House::Uninit()
{
}

std::vector<VERTEX_3D> House::GetVertices()
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
