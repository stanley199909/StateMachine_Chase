#pragma once
#include "Player.h"

class PlayerMoveState : public StateBase
{
private:
    Player* m_player;
public:
    PlayerMoveState(Player* p) : m_player(p) {}
    virtual std::string GetStateName() const override { return "Move"; }
   
    virtual void OnEntry() override;
    virtual void OnUpdate(float dt) override;
    virtual void OnExit() override;
};