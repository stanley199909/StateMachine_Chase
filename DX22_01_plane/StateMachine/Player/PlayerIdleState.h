#pragma once
#include "Player.h"
class PlayerIdleState : public StateBase
{
private:
    Player* m_player;
public:
    PlayerIdleState(Player* p) : m_player(p) {}
    virtual std::string GetStateName() const override { return "Idle"; }

    virtual void OnEntry() override;
    virtual void OnUpdate(float dt) override;
    virtual void OnExit() override;
};
