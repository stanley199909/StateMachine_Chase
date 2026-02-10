#pragma once
#include "Enemy.h"

class EnemySearchState : public StateBase
{
private:
    Enemy* m_enemy;
    float m_SearchTime = 0.0f;
    float m_NextTurnTime = 0.0f;      
    float m_CurrentTurnInterval = 0.0f; 
    const float m_MaxSearchTime = 2.0f;
    Vector3 m_SearchDirection;

public:
    EnemySearchState(Enemy* enemy) : m_enemy(enemy) {}
    virtual std::string GetStateName() const override { return "Search"; }


    virtual void OnEntry() override;
    virtual void OnUpdate(float dt) override;
    virtual void OnExit() override;
};