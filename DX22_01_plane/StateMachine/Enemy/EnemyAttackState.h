#pragma once
#include "Enemy.h"

class EnemyAttackState : public StateBase
{
private:
    Enemy* m_enemy;


public:
    EnemyAttackState(Enemy* enemy) : m_enemy(enemy) {}
    virtual std::string GetStateName() const override { return "Attack"; }


    virtual void OnEntry() override;
    virtual void OnUpdate(float dt) override;
    virtual void OnExit() override;
};