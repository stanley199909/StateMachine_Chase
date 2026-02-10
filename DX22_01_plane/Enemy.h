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
#include "Player.h"

class Enemy : public Object {
private:

    //=======================================
    //  敵ステータス
    //=======================================
    const float m_maxSpeed = 40.0f;
    float m_speed;
    const float m_maxAlertValue = 100.0f;
    const float m_lowestAlertValue = 0.0f;
    float m_alertValue; //警戒値
    bool m_alive;
    //=======================================
    //  StateMachine
    //=======================================
    StateMachine m_stateMachine;
    std::vector<StateBase*> m_states;
    //=======================================
    //  索敵範囲描画
    //=======================================
    ID3D11Buffer* m_SightVB = nullptr;  //Vertex Buffer
    ID3D11Buffer* m_SightIB = nullptr;  //Index Buffer
    bool m_ShowSight = true;
    //=======================================
    //  索敵巡査
    //=======================================
    std::vector<Vector3> m_wayPoints;
    //=======================================
    //  プレイヤー
    //=======================================
    Player* m_player = nullptr;
public:
    Enemy();
    ~Enemy();
    void Init() override;
    void Update() override;
    void Draw(Camera* cam) override;
    void Uninit() override;

    //=======================================
    //  Getter/Setter
    //=======================================
    float GetSpeed()const;
        //// movement helper
    float GetAlertValue()const;
    void SetAlertValue(float alertValue);


    //=======================================
    //  StateMachine
    //=======================================
    // StateMachine access
    StateMachine* GetStateMachine() { return &m_stateMachine; }
 
    //StateMachine
    void HandleEnemyStateMachine(const float& _dt);

    //=======================================
    //  プレイヤーの位置を取得するための関数
    //=======================================
    bool IsPlayerInSight(float fovDegrees = 60.0f) const; //プレイヤーが
    Vector3 GetForward() const;
    Player* GetPlayer() const;
    void SetPlayer(Player* player);
    //=======================================
    //  索敵範囲描画
    //=======================================
    void InitSearchPlayer();
    void DrawSearchPlayer();
    //=======================================
    //  索敵巡査
    //=======================================
    std::vector<Vector3> GetWayPoints() const;
    void SetWayPoints(const std::vector<Vector3>& waypoints);
};