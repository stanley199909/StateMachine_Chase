#include "EnemyAttackState.h"
#include "Game.h"

void EnemyAttackState::OnEntry()
{
	std::cout << "Enemy Enter Attack State" << std::endl;
}

void EnemyAttackState::OnUpdate(float dt)
{
	std::cout << "Game Over! Enemy attacked player." << std::endl;
	//change to result scene;
	Game::StopSound(SOUND_LABEL_BGMStage1);
	Game::PlaySound(SOUND_LABEL_SEDefeat);
	Game::GetInstance()->ChangeScene(GAMEOVER);
	
}

void EnemyAttackState::OnExit()
{

}
