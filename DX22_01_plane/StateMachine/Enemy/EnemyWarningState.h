#pragma once
#include "Enemy.h"
class EnemyWarningState : public StateBase
{
private:
    Enemy* m_enemy;
    
    float m_alertTimer = 0.0f;  // タイムカウンター
    //索敵難易度調整
    const float ALERT_INTERVAL = 0.25f;  // タイムカウンター
    const float MAX_DETECTION_DIST = 50.0f; //最大索敵範囲の長さ(Enemy.cpp(Draw))
public:
    EnemyWarningState(Enemy* e) : m_enemy(e) {}
    virtual std::string GetStateName() const override { return "Warning"; }
    
    virtual void OnEntry() override;
    virtual void OnUpdate(float dt) override;
    virtual void OnExit() override;
};