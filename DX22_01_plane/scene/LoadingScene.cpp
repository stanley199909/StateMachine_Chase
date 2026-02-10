#include "LoadingScene.h"
#include "Texture2D.h"

LoadingScene::LoadingScene(SceneName nextScene) : m_NextScene(nextScene)
{
	Init();
}

LoadingScene::~LoadingScene()
{
	Uninit();
}

void LoadingScene::Init()
{
    Texture2D* bg = Game::GetInstance()->AddObject<Texture2D>();
    bg->SetTexture("assets/texture/loading.png");  
    bg->SetScale(1280.0f, 720.0f, 0.0f);
    m_MySceneObjects.emplace_back(bg);

    m_LoadingProgress = 0;
}



void LoadingScene::Update()
{   
    m_LoadingProgress += 20;
    if (m_LoadingProgress >= 100)
    {
        Game::GetInstance()->ChangeScene(m_NextScene);
    }
}

void LoadingScene::Uninit()
{
    for (auto& o : m_MySceneObjects) {
        Game::GetInstance()->DeleteObject(o);
    }
    m_MySceneObjects.clear();
}