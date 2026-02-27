#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Object.h"
#include "Material.h"

class Tree : public Object
{

	// 頂点データ
	std::vector<VERTEX_3D> m_Vertices;

	//インデックスデータ
	std::vector<unsigned int> m_Indices;

	// 描画の為の情報（メッシュに関わる情報）
	IndexBuffer	 m_IndexBuffer; // インデックスバッファ
	VertexBuffer<VERTEX_3D>	m_VertexBuffer; // 頂点バッファ

	// 描画の為の情報（見た目に関わる部分）
	//Shader m_Shader; // シェーダー
	Texture m_Texture; //テクスチャ
	std::unique_ptr<Material> m_Material; //マテリアル

	int m_SizeX = 0; //横サイズ
	int m_SizeZ = 0; //縦サイズ
public:
	Tree();
	~Tree();
	void Init()override;
	void Update()override;
	void Draw(Camera* cam)override;
	void Uninit()override;
	//頂点情報を取得
	std::vector<VERTEX_3D> GetVertices();
};