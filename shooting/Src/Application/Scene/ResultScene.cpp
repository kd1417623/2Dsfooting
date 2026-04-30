#include"ResultScene.h"
#include"../Background/Background.h"
#include"../Scene.h"
ResultScene::ResultScene()
{
	AllNew();
	Init();
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update()
{
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		SCENE.ChengeScene(title);
	
	}

}

void ResultScene::Init()
{
	AllInit();
}

void ResultScene::Draw()
{
	background->Draw();
	char killstext[50];
	sprintf_s(killstext, "GameOver\n %dKills", SCENE.GetKillCount());



	SHADER.m_spriteShader.DrawString(100, 100, killstext, Math::Vector4(1, 0, 0, 1));
}

void ResultScene::PreUpdate()
{
}
