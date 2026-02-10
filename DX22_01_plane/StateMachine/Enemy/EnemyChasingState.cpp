#include "EnemyChasingState.h"
#include "EnemyWarningState.h"
#include "Game.h"
void EnemyChasingState::OnEntry()
{
    std::cout << "Enemy Enter Chasing State" << std::endl;
	m_player = m_enemy->GetPlayer();
    Game::PlaySound(SOUND_LABEL_SE001);
}

void EnemyChasingState::OnUpdate(float dt)
{
    if (!m_player) return;
    Vector3 enemyPos = m_enemy->GetPosition();
    Vector3 playerPos = m_player->GetPosition();

    Vector3 dir = playerPos - enemyPos;
    float dist = dir.Length();

   
    if (dist < 2.0f)  
    {
        m_enemy->GetStateMachine()->ChangeState("Attack");
        return;
    }

   
    dir.Normalize();
    enemyPos += dir * m_enemy->GetSpeed() * dt;  
    m_enemy->SetPosition(enemyPos);

    float angle = std::atan2(dir.x, dir.z);
    m_enemy->SetRotation(Vector3(0.0f, angle, 0.0f));

    if (!m_enemy->IsPlayerInSight())
    {
        m_enemy->GetStateMachine()->ChangeState("Search");
    }
}

void EnemyChasingState::OnExit()
{
    Game::StopSound(SOUND_LABEL_SE001);
}
