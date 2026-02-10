#pragma once
#include "Object.h"
#include "StateMachine.h"
#include "StateBase.h"
#include <vector>
#include <DirectXMath.h>
#include "MathCommon.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "StaticMesh.h"
#include "AssimpPerse.h"


class Player : public Object
{
public:

private:

    //=======================================
    //  プレイヤーステータス
    //=======================================
    const float m_maxHp = 100.0f;
    float m_hp;
    const float m_maxSpeed = 25.0f;
    const float m_walkSpeed = 5.0f;
    float m_speed;

    /*Vector3 m_Velocity;*/

    StateMachine m_stateMachine;
    std::vector<StateBase*> m_states;



public:
    Player();
    ~Player();
    void Init() override;
    void Update() override;
    void Draw(Camera* cam) override;
    void Uninit() override;

    //=======================================
    //  Getter/ Setter
    //=======================================
    float GetHp() const;
    void SetHp(float value);
    float GetSpeed() const;
    void SetSpeed(float value);

    //=======================================
    //  StateMachine
    //=======================================
    // StateMachine access
    StateMachine* GetStateMachine() { return &m_stateMachine; }

    //StateMachine
    void HandlePlayerStateMachine(const float& _dt);


};