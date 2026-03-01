#pragma once
#include "Player.h"

class PlayerDashState : public StateBase
{
private:
    Player* m_player;

    float m_DashTimer = 0.0f;
    const float DASH_DURATION = 0.5f;  

public:
    PlayerDashState(Player* p) : m_player(p) {}
    virtual std::string GetStateName() const override { return "Dash"; }

    virtual void OnEntry() override;
    virtual void OnUpdate(float dt) override;
    virtual void OnExit() override;
};