#include "EnemyPatrolState.h"
#include "EnemyWarningState.h"

void EnemyPatrolState::OnEntry()
{
    std::cout << "Enemy Enter Patrol State" << std::endl;
}

void EnemyPatrolState::OnUpdate(float dt)
{
    const std::vector<Vector3>& waypoints = m_enemy->GetWayPoints();
    if (waypoints.empty())
    {
        return;
    }
    Vector3 pos = m_enemy->GetPosition();
    Vector3 target = waypoints[m_currentIndex];


    Vector3 dir = target - pos;
    float dist = dir.Length();

    if (dist > 1.0f)
    {
        dir.Normalize();
        pos += dir * m_enemy->GetSpeed() * dt;
        m_enemy->SetPosition(pos);

        float angle = std::atan2(dir.x, dir.z);
        m_enemy->SetRotation(Vector3(0.0f, angle, 0.0f));
    }
    else
    {
        m_currentIndex = (m_currentIndex + 1) % waypoints.size();
    }

    if (m_enemy->IsPlayerInSight())
    {
        std::cout << "Patrol detected player! Switch to Warning" << std::endl;
        m_enemy->GetStateMachine()->ChangeState("Warning");
    }
  
}

void EnemyPatrolState::OnExit()
{
}
