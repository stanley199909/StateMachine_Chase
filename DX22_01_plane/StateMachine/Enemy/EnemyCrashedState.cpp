#include "EnemyCrashedState.h"
#include "Game.h"
#include <iostream>

void EnemyCrashedState::OnEntry()
{
    
    m_FlyDirection = Vector3(
        (rand() % 200 - 100) / 100.0f,  
        1.0f,                         
        (rand() % 200 - 100) / 100.0f  
    );
    m_FlyDirection.Normalize();


    m_CrashTimer = 0.0f;

 
  
}

void EnemyCrashedState::OnUpdate(float dt)
{
    m_CrashTimer += dt;


    Vector3 rotation = m_enemy->GetRotation();
    rotation.y += m_RotationSpeed * dt;  
    m_enemy->SetRotation(rotation);

    Vector3 pos = m_enemy->GetPosition();
    pos += m_FlyDirection * 150.0f * dt;  
    pos.y += 50.0f * dt;  
    m_enemy->SetPosition(pos);

   
    if (m_CrashTimer >= CRASH_DURATION)
    {
        m_enemy->SetMarkedForDelete(true);
        Game::PlaySound(SOUND_LABEL_SECrashed);
    }
}

void EnemyCrashedState::OnExit()
{
}
