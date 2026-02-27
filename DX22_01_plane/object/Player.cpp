#include "Player.h"
#include "Game.h"
#include "Player/PlayerIdleState.h"
#include "Player/PlayerMoveState.h"

//=======================================
// 初期化処理
//=======================================
Player::Player()
{
	SetType(ObjectType::PLAYER);
	m_hp = m_maxHp;
	m_speed = m_maxSpeed;
}

Player::~Player()
{

}


void Player::Init()
{

	//メッシュを読み込み
	StaticMesh staticmesh;

	//3Dモデルデータ
	std::u8string modelFile = u8"assets/model/player/car.fbx";

	//テクスチャディレクトリ
	std::string texDirectory = "assets/model/player/";

	LoadModel(modelFile, texDirectory, Vector3(2.0f, 2.0f, 2.0f));

	m_states.push_back(new PlayerIdleState(this));
	m_states.push_back(new PlayerMoveState(this));
	//////////////////////////////
	// ステートマシン情報入力
	//////////////////////////////
	for (StateBase* state : m_states)
	{
		state->RegisterState(m_stateMachine);
	}
	//最初はIdleステート
	m_stateMachine.ChangeState("Idle");
	

	
}

//=======================================
//更新処理
//=======================================
void Player::Update()
{
	HandlePlayerStateMachine(1.0f/60.0f); //change 1/60 after test

}

//=======================================
//描画処理
//=======================================
void Player::Draw(Camera* cam)
{
	cam->SetCamera();
	cam->SetTarget(GetPosition());
	
	Object::Draw(cam);
}

//=======================================
//終了処理
//=======================================
void Player::Uninit()
{
	for (auto state : m_states)
		delete state;

	m_states.clear();
}

//=======================================
//  Getter/ Setter
//=======================================
float Player::GetHp() const
{
	return m_hp;
}

void Player::SetHp(float value)
{
	m_hp = value;
}

float Player::GetSpeed() const
{
	return m_speed;
}

void Player::SetSpeed(float value)
{
	m_speed = value;
}

void Player::HandlePlayerStateMachine(const float& _dt)
{
	this->m_stateMachine.Update(_dt);

}