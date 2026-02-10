#pragma once
#include "Enemy.h"

class EnemyPatrolState : public StateBase
{
private:
    Enemy* m_enemy;
    size_t m_currentIndex = 0;

public:
    EnemyPatrolState(Enemy* enemy) : m_enemy(enemy) {}
    virtual std::string GetStateName() const override { return "Patrol"; }


    virtual void OnEntry() override;
    virtual void OnUpdate(float dt) override;
    virtual void OnExit() override;
};