#include "Stage1Scene.h"
#include "Game.h"
#include "Input.h"
#include "Player.h"
#include "Ground.h"
#include "BigGround.h"
#include "House.h"
#include "Tree.h"
#include "Texture2D.h"
#include "Goal.h"
#include "Enemy.h"

// コンストラクタ
Stage1Scene::Stage1Scene()
{
	Init();
}

// デストラクタ
Stage1Scene::~Stage1Scene()
{
	Uninit();
}

// 初期化
void Stage1Scene::Init()
{
    InitStageData();
}

//更新
void Stage1Scene::Update()
{
   
	Player* player = dynamic_cast<Player*>(m_MySceneObjects[0]);
	Goal* goal = dynamic_cast<Goal*>(m_MySceneObjects[2]);
	Vector3 playerPos = player->GetPosition();
	Vector3 goalPos = goal->GetPosition();
	if ((playerPos - goalPos).Length() < 5.0f)  
	{
       /* std::cout << "MissionComplete" << std::endl;*/
        Game::StopSound(SOUND_LABEL_BGM001);
        Game::PlaySound(SOUND_LABEL_SE002);
		Game::GetInstance()->ChangeScene(GAMECLEAR);
        return;
	}

    
    if (std::abs(playerPos.x) > MAP_BOUNDARY_X || 
        std::abs(playerPos.z) > MAP_BOUNDARY_Z)
    {
        Game::StopSound(SOUND_LABEL_BGM001);
        Game::PlaySound(SOUND_LABEL_SE003);
        Game::GetInstance()->ChangeScene(GAMEOVER);
        return;
    }
}

void Stage1Scene::InitStageData()
{
        Game::PlaySound(SOUND_LABEL_BGM001);
      
        
        /*m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Skybox>());*/
        m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Player>()); //0
        m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Ground>()); //1
        m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Goal>());   //2
        m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<BigGround>()); //3
        m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<House>()); //4
        m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Tree>()); //5
        
        //m_MySceneObjects.emplace_back(Game::GetInstance()->AddObject<Enemy>());  //3
        //auto AddWall = [&](float x, float y, float z)
        //	{
        //		Wall* wall = Game::GetInstance()->AddObject<Wall>();
        //		wall->SetPosition(Vector3(x, y, z));
        //		m_MySceneObjects.emplace_back(wall);
        //	};

        //AddWall(0.0f, 20.0f, -500.0f);     // 北
        //AddWall(0.0f, 20.0f, 500.0f);     // 南
        //AddWall(-500.0f, 20.0f, 0.0f);     // 西
        //AddWall(500.0f, 20.0f, 0.0f);     // 東

        Player* player = dynamic_cast<Player*>(m_MySceneObjects[0]);

        auto AddEnemy = [&](float x, float z, const std::vector<Vector3>& waypoints = {})
            {
                Enemy* enemy = Game::GetInstance()->AddObject<Enemy>();
                enemy->SetPlayer(player);
                enemy->SetPosition(Vector3(x, 0.0f, z));
                enemy->SetWayPoints(waypoints);
                m_MySceneObjects.emplace_back(enemy);

                enemy->GetStateMachine()->ChangeState("Patrol");

            };
        Vector3 playerSpawnPosition = Vector3(0, 0, -200);
        player->SetPosition(playerSpawnPosition);
        // =======================================
        //  Ground 設定（地面）
        // =======================================
        Ground* ground = dynamic_cast<Ground*>(m_MySceneObjects[1]);
        if (ground) {
            ground->SetPosition(Vector3(0.0f, -10.0f, 0.0f));
            ground->SetScale(Vector3(0.2f, 0.5f, 0.5f)); //100*250
        }
        // =======================================
        // マップレイアウト（100x250 マップ）
        // =======================================

        // 【第1層】 (Z: -180 to -100)
        //  比較的簡単
        AddEnemy(-50.0f, -150.0f, {
            Vector3(-50, 0, -150),
            Vector3(50, 0, -150),
            Vector3(-50, 0, -150)
            });

        AddEnemy(60.0f, -130.0f, {
            Vector3(60, 0, -180),
            Vector3(60, 0, -100),
            Vector3(60, 0, -180)
            });

        AddEnemy(-60.0f, -130.0f, {
            Vector3(-60, 0, -100),
            Vector3(-60, 0, -180),
            Vector3(-60, 0, -100)
            });

        // 【第2層】(Z: -100 to 0)
        //　交差パトロール
        AddEnemy(-80.0f, -50.0f, {
            Vector3(-80, 0, -80),
            Vector3(-80, 0, -20),
            Vector3(-40, 0, -20),
            Vector3(-40, 0, -80),
            Vector3(-80, 0, -80)
            });

        AddEnemy(80.0f, -50.0f, {
            Vector3(80, 0, -80),
            Vector3(80, 0, -20),
            Vector3(40, 0, -20),
            Vector3(40, 0, -80),
            Vector3(80, 0, -80)
            });

        AddEnemy(0.0f, -60.0f, {
            Vector3(-70, 0, -60),
            Vector3(70, 0, -60),
            Vector3(-70, 0, -60)
            });

        AddEnemy(-50.0f, -30.0f, {
            Vector3(-50, 0, -30),
            Vector3(50, 0, -70),
            Vector3(-50, 0, -30)
            });

        // 【第3層】 (Z: 0 to 120)
        //  狭い通路
        AddEnemy(-40.0f, 60.0f, {
            Vector3(-40, 0, 40),
            Vector3(-40, 0, 80),
            Vector3(-40, 0, 40)
            });

        AddEnemy(40.0f, 60.0f, {
            Vector3(40, 0, 40),
            Vector3(40, 0, 80),
            Vector3(40, 0, 40)
            });

        AddEnemy(0.0f, 70.0f, {
            Vector3(-30, 0, 70),
            Vector3(30, 0, 70),
            Vector3(-30, 0, 70)
            });

        AddEnemy(-60.0f, 100.0f, {
            Vector3(-60, 0, 80),
            Vector3(60, 0, 120),
            Vector3(-60, 0, 80)
            });

        // 【第4層】 (Z: 120 to 220)
        //  ゴール前の密集防御
        AddEnemy(-50.0f, 160.0f, {
            Vector3(-50, 0, 140),
            Vector3(-50, 0, 180),
            Vector3(-20, 0, 180),
            Vector3(-20, 0, 140),
            Vector3(-50, 0, 140)
            });

        AddEnemy(50.0f, 160.0f, {
            Vector3(50, 0, 140),
            Vector3(50, 0, 180),
            Vector3(20, 0, 180),
            Vector3(20, 0, 140),
            Vector3(50, 0, 140)
            });

        AddEnemy(0.0f, 170.0f, {
            Vector3(-40, 0, 170),
            Vector3(40, 0, 170),
            Vector3(-40, 0, 170)
            });

        AddEnemy(0.0f, 200.0f, {
            Vector3(-30, 0, 190),
            Vector3(30, 0, 210),
            Vector3(-30, 0, 190)
            });

        // =======================================
        //  Goal 設定（ゴール地点）
        // =======================================
        Goal* goal = dynamic_cast<Goal*>(m_MySceneObjects[2]);
        if (goal) {
            goal->SetPosition(Vector3(0.0f, 0.0f, 220.0f));
            goal->SetScale(Vector3(8.0f, 8.0f, 8.0f));
        }
        // =======================================
        //  BigGround 設定（大地面）
        // =======================================
        BigGround* bigGround = dynamic_cast<BigGround*>(m_MySceneObjects[3]);
        if (bigGround) {
            bigGround->SetPosition(Vector3(0.0f, -100.0f, 0.0f));
            bigGround->SetScale(Vector3(1.0f, 1.0f, 1.0f));
        }
    
        // =======================================
        //  建物設定（屋敷）
        // =======================================
        House* house = dynamic_cast<House*>(m_MySceneObjects[4]);
        if (house) {
            house->SetPosition(Vector3(-200.0f, -80.0f, 0.0f));
            house->SetScale(Vector3(1.0f, 1.0f, 1.0f));

        // =======================================
        //  樹
        // =======================================
        auto AddTree = [&](float x, float z)
            {
                Tree* tree = Game::GetInstance()->AddObject<Tree>();
                tree->SetPosition(Vector3(x, -80.0f, z));
                tree->SetScale(Vector3(1.0f, 1.0f, 1.0f));
            
                m_MySceneObjects.emplace_back(tree);
            };
        AddTree(-150.0f, -100.0f); //屋敷の下
        AddTree(150.0f, -200.0f); //最初のところの右側
        AddTree(150.0f, -100.0f); //その上

        }
}

// 終了処理
void Stage1Scene::Uninit()
{
	// このシーンのオブジェクトを削除する
	for (auto& o : m_MySceneObjects) {
		Game::GetInstance()->DeleteObject(o);
	}
	m_MySceneObjects.clear();

}

//スコアを取得
int Stage1Scene::GetScore() const
{
	return 0;
}

void Stage1Scene::StopAllSE()
{
    Game::StopSound(SOUND_LABEL_SE000);
    Game::StopSound(SOUND_LABEL_SE001);
}

