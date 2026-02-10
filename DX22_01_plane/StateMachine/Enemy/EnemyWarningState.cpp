#include "EnemyWarningState.h"
#include "Game.h"
void EnemyWarningState::OnEntry()
{
	std::cout << "Enemy Enter Warning State" << std::endl;
    m_alertTimer = 0.0f;
    Game::PlaySound(SOUND_LABEL_SE000);
}

void EnemyWarningState::OnUpdate(float dt)
{
    Player* player = m_enemy->GetPlayer();
    if (m_enemy->IsPlayerInSight())  
    {
        
        m_alertTimer += dt;

      
        if (m_alertTimer >= ALERT_INTERVAL)
        {
            m_alertTimer -= ALERT_INTERVAL;  

           
            Vector3 toPlayer = player->GetPosition() - m_enemy->GetPosition();
            float dist = toPlayer.Length();

           
            float rate = 100.0f - (dist / MAX_DETECTION_DIST) * 90.0f;
            rate = std::fmax(rate, 30.0f);  
            rate = std::fmin(rate, 100.0f);  

           
            float newAlertValue = m_enemy->GetAlertValue() + rate;
            m_enemy->SetAlertValue(newAlertValue);

            std::cout << "Enemy AlertValue: " << m_enemy->GetAlertValue()
                << " (+" << rate << ")" << std::endl;

           
            if (m_enemy->GetAlertValue() >= 100.0f)
            {
                m_enemy->SetAlertValue(100.0f);
                m_enemy->GetStateMachine()->ChangeState("Chasing");
            }
        }
    }
    else  
    {
        float newAlertValue = m_enemy->GetAlertValue() - 25.0f * dt;
        m_enemy->SetAlertValue(newAlertValue);

        if (m_enemy->GetAlertValue() <= 0.0f)
        {
            m_enemy->SetAlertValue(0.0f);
            m_alertTimer = 0.0f;  
            m_enemy->GetStateMachine()->ChangeState("Search");
        }
    }
}

void EnemyWarningState::OnExit()
{
    Game::StopSound(SOUND_LABEL_SE000);
    m_alertTimer = 0.0f;
}
