#pragma once
#include "Camera.h"
#include "Shader.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "StaticMesh.h"
#include "MathCommon.h"

struct AABB {
	Vector3 min;
	Vector3 max;
};
class Object {
public:
	enum class ObjectType {
		PLAYER,
		ENEMY,
		WALL,
		GROUND,
		GOAL,
		BUILDING,
		ENVIRONMENT,
		OTHER //今後追加 
	};
protected:
	// SRT情報（姿勢情報）
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	// 描画の為の情報（見た目に関わる部分）
	Shader m_Shader; // シェーダー

	//オブジェクトの種類を分ける
	ObjectType m_Type = ObjectType::OTHER;

	// 描画の為の情報（メッシュに関わる情報）
	MeshRenderer m_MeshRenderer; // 頂点バッファ・インデックスバッファ・インデックス数

	// 描画の為の情報（見た目に関わる部分）
	std::vector<std::unique_ptr<Material>> m_Materials;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // テクスチャ
public:
	virtual ~Object() {} //仮想デスクラクタ
	virtual void Init()=0;
	virtual void Update() = 0;
	virtual void Draw(Camera* cam) = 0;
	virtual void Uninit() = 0;

	// 位置の取得
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_Position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) { m_Position = pos; }
	void SetRotation(const DirectX::SimpleMath::Vector3& rot) { m_Rotation = rot; }
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_Scale = scale; }

	//オブジェクト
	ObjectType GetType() const { return m_Type; }
	void SetType(ObjectType type) { m_Type = type; }
	//自分が追加した機能
	virtual void LoadModel(const std::u8string& modelPath,
		const std::string& textureDirectory,
		const Vector3& scale);
	//=======================================
	//当たり判定ボックスを取得
	//=======================================
	virtual AABB GetAABB(const Vector3& _localMin, const Vector3& _localMax) const;
};
