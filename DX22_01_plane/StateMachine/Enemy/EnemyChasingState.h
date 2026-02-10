#pragma once
#include "Enemy.h"

class EnemyChasingState : public StateBase
{
private:
    Enemy* m_enemy;
    Player* m_player;
public:
    EnemyChasingState(Enemy* enemy) : m_enemy(enemy) {}
    virtual std::string GetStateName() const override { return "Chasing"; }

    virtual void OnEntry() override;
    virtual void OnUpdate(float dt) override;
    virtual void OnExit() override;
};