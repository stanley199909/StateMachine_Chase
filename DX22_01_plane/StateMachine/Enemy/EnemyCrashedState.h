#pragma once
#include "Enemy.h"

class EnemyCrashedState : public StateBase
{
private:
    Enemy* m_enemy;

    float m_CrashTimer = 0.0f;
    const float CRASH_DURATION = 2.0f; 
    Vector3 m_FlyDirection;  
    float m_RotationSpeed = 720.0f;  

public:
    EnemyCrashedState(Enemy* enemy) : m_enemy(enemy) {}
    virtual std::string GetStateName() const override { return "Crashed"; }


    virtual void OnEntry() override;
    virtual void OnUpdate(float dt) override;
    virtual void OnExit() override;

};