#include "Object.h"
#include <iostream>
using namespace DirectX::SimpleMath;

//今のところ記述内容は無し
void Object::LoadModel(
    const std::u8string& modelPath,
    const std::string& textureDirectory,
    const Vector3& scale
)
{
    StaticMesh staticmesh;
    std::string modelPathStr(
        reinterpret_cast<const char*>(modelPath.c_str()),
        modelPath.size());
    // ファイル読み込み
    staticmesh.Load(modelPathStr, textureDirectory);

    // MeshRenderer 初期化
    m_MeshRenderer.Init(staticmesh);

    // シェーダー（必要に応じて引数化も可能）
    m_Shader.Create("shader/litTextureVS.hlsl", "shader/litTexturePS.hlsl");

    // サブセット
    m_subsets = staticmesh.GetSubsets();

    // テクスチャ
    m_Textures = staticmesh.GetTextures();

    // マテリアル
    auto mats = staticmesh.GetMaterials();
    for (auto& mat : mats)
    {
        auto m = std::make_unique<Material>();
        m->Create(mat);
        m_Materials.push_back(std::move(m));
    }

    // スケール設定
    m_Scale = scale;


}
//=======================================
//当たり判定ボックスを取得
//=======================================
AABB Object::GetAABB(const Vector3& _localMin, const Vector3& _localMax) const
{
    // ローカルAABB (モデルサイズに基づく: width(x) , height (y), depth (z), Pivot底面中心)
    Vector3 localMin(_localMin.x, _localMin.y, _localMin.z);
    Vector3 localMax(_localMax.x, _localMax.y, _localMax.z);

    // AABBの8つの角を定義
    std::vector<Vector3> corners = {
        localMin,
        Vector3(localMin.x, localMin.y, localMax.z),
        Vector3(localMin.x, localMax.y, localMin.z),
        Vector3(localMin.x, localMax.y, localMax.z),
        Vector3(localMax.x, localMin.y, localMin.z),
        Vector3(localMax.x, localMin.y, localMax.z),
        Vector3(localMax.x, localMax.y, localMin.z),
        localMax
    };
    // ワールド変換行列を作成
    Matrix r = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
    Matrix t = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
    Matrix s = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);
    Matrix worldmtx = s * r * t;

    // 各角をワールド変換し、min/maxを計算
    Vector3 worldMin(FLT_MAX, FLT_MAX, FLT_MAX);
    Vector3 worldMax(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    for (auto& corner : corners) {
        corner = Vector3::Transform(corner, worldmtx);
        worldMin = Vector3::Min(worldMin, corner);
        worldMax = Vector3::Max(worldMax, corner);
    }

    return { worldMin, worldMax };
}

void Object::Draw(Camera* cam)
{
    // カメラをGPUへセット（必要なら）
    cam->SetCamera();

    // == SRT ==
    Matrix r = Matrix::CreateFromYawPitchRoll(
        m_Rotation.y, m_Rotation.x, m_Rotation.z);

    Matrix t = Matrix::CreateTranslation(
        m_Position.x, m_Position.y, m_Position.z);

    Matrix s = Matrix::CreateScale(
        m_Scale.x, m_Scale.y, m_Scale.z);

    Matrix world = s * r * t;

    // World 行列送信
    Renderer::SetWorldMatrix(&world);

    // Shader セット
    m_Shader.SetGPU();

    // 頂点バッファ・インデックスバッファ
    m_MeshRenderer.BeforeDraw();

    // サブセットごとに描画
    for (int i = 0; i < m_subsets.size(); i++)
    {
        int matIndex = m_subsets[i].MaterialIdx;

        // Material を GPU にセット
        m_Materials[matIndex]->SetGPU();

        // Texture 必要なときだけ
        if (m_Materials[matIndex]->isTextureEnable())
        {
            m_Textures[matIndex]->SetGPU();
        }

        // Draw call
        m_MeshRenderer.DrawSubset(
            m_subsets[i].IndexNum,
            m_subsets[i].IndexBase,
            m_subsets[i].VertexBase);
    }
}