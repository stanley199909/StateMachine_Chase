#include "PlayerMoveState.h"
#include <iostream>
#include "input.h"
#include "MathCommon.h"
void PlayerMoveState::OnEntry()
{
  /*  m_player->PlayAnimation("Move", true);*/
    std::cout << "Enter Move State" << std::endl;
}

void PlayerMoveState::OnUpdate(float dt)
{
    Vector3 pos = m_player->GetPosition();
    Vector3 moveDirection(0.0f, 0.0f, 0.0f);
    // ˆÚ“®
    if (Input::GetKeyPress(VK_A)) moveDirection.x -= m_player->GetSpeed()* dt;
    if (Input::GetKeyPress(VK_D)) moveDirection.x += m_player->GetSpeed() * dt;
    if (Input::GetKeyPress(VK_W)) moveDirection.z += m_player->GetSpeed() * dt;
    if (Input::GetKeyPress(VK_S)) moveDirection.z -= m_player->GetSpeed() * dt;

    if (moveDirection.LengthSquared() > 0.0f)
    {

        moveDirection.Normalize();


        pos += moveDirection * m_player->GetSpeed() * dt;

   
        float targetAngle = std::atan2(moveDirection.x, moveDirection.z);

       
        m_player->SetRotation(Vector3(0.0f, targetAngle, 0.0f));
    }

    m_player->SetPosition(pos);

 
    if (moveDirection.LengthSquared() < 0.01f)
    {
        m_player->GetStateMachine()->ChangeState("Idle");
      
    }

}

void PlayerMoveState::OnExit()
{


}