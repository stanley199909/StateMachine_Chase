#include "EnemySearchState.h"
#include "EnemyPatrolState.h"  
#include "EnemyWarningState.h"

void EnemySearchState::OnEntry()
{
    std::cout << "Enemy Enter Search State" << std::endl;

    m_SearchTime = 0.0f;
    m_NextTurnTime = 0.0f;


    float randomAngle = (std::rand() % 360) * PI / 180.0f;
    m_SearchDirection = Vector3(std::sin(randomAngle), 0.0f, std::cos(randomAngle));
    m_SearchDirection.Normalize();

  
    m_CurrentTurnInterval = 1.0f + (std::rand() % 200) / 100.0f;
}

void EnemySearchState::OnUpdate(float dt)
{
    m_SearchTime += dt;
    if (m_SearchTime > m_MaxSearchTime)
    {
        std::cout << "Search timeout, return to Patrol" << std::endl;
        m_enemy->GetStateMachine()->ChangeState("Patrol");
        return;
    }


    if (m_enemy->IsPlayerInSight())
    {
        std::cout << "Player found during search!" << std::endl;
        m_enemy->GetStateMachine()->ChangeState("Warning");
        return;
    }


    m_NextTurnTime += dt;

 
    if (m_NextTurnTime >= m_CurrentTurnInterval)
    {
        m_NextTurnTime = 0.0f;

       
        float angleChange = ((std::rand() % 120) - 60) * PI / 180.0f; // -60Åã ~ +60Åã
        Vector3 currentDir = m_SearchDirection;
        float currentAngle = std::atan2(currentDir.x, currentDir.z);
        float newAngle = currentAngle + angleChange;

        m_SearchDirection = Vector3(std::sin(newAngle), 0.0f, std::cos(newAngle));
        m_SearchDirection.Normalize();

       
        m_CurrentTurnInterval = 1.0f + (std::rand() % 200) / 100.0f;

        std::cout << "Enemy turning, new direction: "
            << m_SearchDirection.x << ", " << m_SearchDirection.z << std::endl;
    }

 
    Vector3 pos = m_enemy->GetPosition();
    pos += m_SearchDirection * m_enemy->GetSpeed() * dt * 0.5f;
    m_enemy->SetPosition(pos);


    float angle = std::atan2(m_SearchDirection.x, m_SearchDirection.z);
    m_enemy->SetRotation(Vector3(0.0f, angle, 0.0f));
}

void EnemySearchState::OnExit()
{
    std::cout << "Enemy Exit Search State" << std::endl;
}
