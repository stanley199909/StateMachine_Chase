#include "PlayerDashState.h"
#include <iostream>
#include "input.h"
#include "MathCommon.h"
#include "Game.h"
#include "Enemy.h"
void PlayerDashState::OnEntry()
{
    m_DashTimer = 0.0f;
    Game::PlaySound(SOUND_LABEL_SEDash);
}

void PlayerDashState::OnUpdate(float dt)
{
    m_DashTimer += dt;

  
    Vector3 forward = m_player->GetFoward();  

    
    float dashSpeed = 100.0f;  
    Vector3 dashStep;
    dashStep.x = forward.x * dashSpeed * dt;
    dashStep.y = forward.y * dashSpeed * dt;
    dashStep.z = forward.z * dashSpeed * dt;

   
    Vector3 currentPos = m_player->GetPosition();
    currentPos.x += dashStep.x;
    currentPos.y += dashStep.y;
    currentPos.z += dashStep.z;
    m_player->SetPosition(currentPos);

    auto enemies = Game::GetInstance()->GetObjects<Enemy>();
    for (auto enemy : enemies)
    {
        float dist = Vector3::Distance(m_player->GetPosition(), enemy->GetPosition());
        if (dist < 10.0f)
        {
           enemy->GetStateMachine()->ChangeState("Crashed");
         
        }
    }

    // Dash Œ‹‘©
    if (m_DashTimer >= DASH_DURATION)
    {
        m_player->GetStateMachine()->ChangeState("Idle");
    }
}

void PlayerDashState::OnExit()
{
    m_DashTimer = 0.0f;
}
