#include "Enemy.h"
#include "Game.h"
#include "EnemyIdleState.h"
#include "EnemyPatrolState.h"
#include "EnemyWarningState.h"
#include "EnemyChasingState.h"
#include "EnemySearchState.h"
#include "EnemyAttackState.h"

//=======================================
// 初期化処理
//=======================================
Enemy::Enemy() : m_player(nullptr)
{
	SetType(ObjectType::ENEMY);
	m_alive = true;
	m_alertValue = m_lowestAlertValue;
	m_speed = m_maxSpeed;
	GetPlayer();
}

Enemy::~Enemy()
{
	
}

void Enemy::Init()
{
	//メッシュを読み込み
	StaticMesh staticmesh;

	//3Dモデルデータ
	std::u8string modelFile = u8"assets/model/enemy/police.FBX";

	//テクスチャディレクトリ
	std::string texDirectory = "assets/model/enemy/";

	LoadModel(modelFile, texDirectory, Vector3(0.1f, 0.1f, 0.1f));

	m_states.push_back(new EnemyIdleState(this));
	m_states.push_back(new EnemyPatrolState(this));
	m_states.push_back(new EnemyWarningState(this));
	m_states.push_back(new EnemySearchState(this));
	m_states.push_back(new EnemyChasingState(this));
	m_states.push_back(new EnemyAttackState(this));
	//////////////////////////////	
	// ステートマシン情報入力
	//////////////////////////////
	for (StateBase* state : m_states)
	{
		state->RegisterState(m_stateMachine);
	}
	////最初はIdleステート
	//m_stateMachine.ChangeState("Idle");
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	//=======================================
	//  索敵範囲描画
	//=======================================
	InitSearchPlayer();
}

void Enemy::Update()
{
	HandleEnemyStateMachine(1.0f / 60.0f); //change 1/60 after test
}

void Enemy::Draw(Camera* cam)
{
	cam->SetCamera();
	

	Object::Draw(cam);
	//=======================================
	//  索敵範囲描画
	//=======================================
	DrawSearchPlayer();
}

void Enemy::Uninit()
{
	for (auto state : m_states)
		delete state;

	m_states.clear();
	//=======================================
	//  索敵範囲描画
	//=======================================
	SAFE_RELEASE(m_SightVB);
	SAFE_RELEASE(m_SightIB);
}

float Enemy::GetSpeed() const
{
	return m_speed;
}

float Enemy::GetAlertValue() const
{
	return m_alertValue;
}

void Enemy::SetAlertValue(float alertValue)
{
	m_alertValue = alertValue;
}

void Enemy::HandleEnemyStateMachine(const float& _dt)
{
	this->m_stateMachine.Update(_dt);
}

bool Enemy::IsPlayerInSight(float fovDegrees) const
{

	if (!m_player) return false; // プレイヤーが検索範囲外ならfalse処理
	Vector3 toPlayer = m_player->GetPosition() - GetPosition();
	float dist = toPlayer.Length();
	if (dist > 45.0f) return false;  

	toPlayer.Normalize();
	Vector3 forward = GetForward();
	forward.Normalize();
	float dot = toPlayer.Dot(forward);
	float halfAngle = fovDegrees / 2.0f;
	float rad = halfAngle * PI / 180.0f;
	float threshold = std::cos(rad);
	return dot > threshold;
}

Vector3 Enemy::GetForward() const
{
	float yaw = m_Rotation.y;  
	float cosYaw = std::cos(yaw);
	float sinYaw = std::sin(yaw);

	
	return Vector3(sinYaw, 0.0f, cosYaw);

}

Player* Enemy::GetPlayer() const
{
	return m_player;
}

void Enemy::SetPlayer(Player* player)
{
	m_player = player;
}

void Enemy::InitSearchPlayer()
{
	VERTEX_3D vertices[3] = {};
	vertices[0].position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[0].color = Color(1.0f, 0.0f, 0.0f, 0.5f);
	vertices[0].normal = Vector3(0, 1, 0);
	vertices[0].uv = Vector2(0, 0);
	float halfRad = 30.0f * PI / 180.0f;
	vertices[1].position = Vector3(std::sin(-halfRad) * 50.0f, 0.0f, std::cos(-halfRad) * 50.0f); // 左
	vertices[1].color = Color(1.0f, 0.0f, 0.0f, 0.5f);
	vertices[1].normal = Vector3(0, 1, 0);
	vertices[1].uv = Vector2(0, 0);
	vertices[2].position = Vector3(std::sin(halfRad) * 50.0f, 0.0f, std::cos(halfRad) * 50.0f); // 右
	vertices[2].color = Color(1.0f, 0.0f, 0.0f, 0.5f);
	vertices[2].normal = Vector3(0, 1, 0);
	vertices[2].uv = Vector2(0, 0);
	unsigned int indices[3] = { 0, 1, 2 };
	Renderer::CreateVertexBuffer(sizeof(VERTEX_3D), 3, vertices, &m_SightVB);
	Renderer::CreateIndexBuffer(3, indices, &m_SightIB);
}

void Enemy::DrawSearchPlayer()
{
	if (m_ShowSight)
	{
		Matrix4x4 world = Matrix4x4::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z) * Matrix4x4::CreateTranslation(GetPosition());
		Renderer::SetWorldMatrix(&world);
		Renderer::SetBlendState(BS_ALPHABLEND);
		ID3D11DeviceContext* ctx = Renderer::GetDeviceContext();
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		ctx->IASetVertexBuffers(0, 1, &m_SightVB, &stride, &offset);
		ctx->IASetIndexBuffer(m_SightIB, DXGI_FORMAT_R32_UINT, 0);
		ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		ctx->DrawIndexed(3, 0, 0);
		Renderer::SetBlendState(BS_NONE);
	}
}

std::vector<Vector3> Enemy::GetWayPoints() const
{
	return m_wayPoints;
}

void Enemy::SetWayPoints(const std::vector<Vector3>& waypoints)
{
	 m_wayPoints = waypoints; 
}
