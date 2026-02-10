#pragma once
#include "Enemy.h"
class EnemyIdleState : public StateBase
{
private:
    Enemy* m_enemy;
public:
    EnemyIdleState(Enemy* e) : m_enemy(e) {}
    virtual std::string GetStateName() const override { return "Idle"; }

    virtual void OnEntry() override;
    virtual void OnUpdate(float dt) override;
    virtual void OnExit() override;
};