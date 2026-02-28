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
    //  “GƒXƒe[ƒ^ƒX
    //=======================================
    const float m_maxSpeed = 40.0f;
    float m_speed;
    const float m_maxAlertValue = 100.0f;
    const float m_lowestAlertValue = 0.0f;
    float m_alertValue; //Œx‰ú’l
    bool m_alive;
    //=======================================
    //  StateMachine
    //=======================================
    StateMachine m_stateMachine;
    std::vector<StateBase*> m_states;
    //=======================================
    //  õ“G”ÍˆÍ•`‰æ
    //=======================================
    ID3D11Buffer* m_SightVB = nullptr;  //Vertex Buffer
    ID3D11Buffer* m_SightIB = nullptr;  //Index Buffer
    const float SIGHT_RANGE = 45.0f;  // IsPlayerInSight ‚Ì dist > 45.0f ‚Æˆê’v
    const float SIGHT_FOV = 50.0f;    // IsPlayerInSight ‚Ì fovDegrees ‚Æˆê’v
    bool m_ShowSight = true;
    //=======================================
    //  õ“G„¸
    //=======================================
    std::vector<Vector3> m_wayPoints;
    //=======================================
    //  ƒvƒŒƒCƒ„[
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
    //  ƒvƒŒƒCƒ„[‚ÌˆÊ’u‚ğæ“¾‚·‚é‚½‚ß‚ÌŠÖ”
    //=======================================
    bool IsPlayerInSight(float fovDegrees = 60.0f) const; //ƒvƒŒƒCƒ„[‚ª
    Vector3 GetForward() const;
    Player* GetPlayer() const;
    void SetPlayer(Player* player);
    //=======================================
    //  õ“G”ÍˆÍ•`‰æ
    //=======================================
    void InitSearchPlayer();
    void DrawSearchPlayer();
    //=======================================
    //  õ“G„¸
    //=======================================
    std::vector<Vector3> GetWayPoints() const;
    void SetWayPoints(const std::vector<Vector3>& waypoints);
};