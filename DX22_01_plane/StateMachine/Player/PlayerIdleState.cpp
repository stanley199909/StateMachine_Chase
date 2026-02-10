#include "PlayerIdleState.h"
#include "PlayerMoveState.h"
#include <iostream>
#include "input.h"
void PlayerIdleState::OnEntry()
{
    //m_player->PlayAnimation("Idle", true);

}

void PlayerIdleState::OnUpdate(float dt)
{
    // if press any button, change to Move
    if (Input::GetKeyPress(VK_W) ||
        Input::GetKeyPress(VK_A) ||

        Input::GetKeyPress(VK_S) ||
        Input::GetKeyPress(VK_D))
    {
        m_player->GetStateMachine()->ChangeState("Move");
    }

}

void PlayerIdleState::OnExit()
{


}