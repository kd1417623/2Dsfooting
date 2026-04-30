#include"TitleScene.h"
#include"../Character/Player/Player.h"
#include"../Character/Enemy/Enemy.h"
#include"../Character/Enemy/EnemyTurret.h"
#include"../Character/Hit/Hit.h"
#include"../Background/Background.h"
#include"../Background/Object.h"


#include"../Scene.h"
TitleScene::TitleScene()
{	
	
	AllNew();

}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	for (auto& i : backobj)
	{
		i->Update();
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SCENE.ChengeScene(main);
		return;

	}


}

void TitleScene::Init()
{

	AllInit();
}

void TitleScene::Draw()
{
	background->Draw();
	SHADER.m_spriteShader.DrawString(100, 100, "title", Math::Vector4(1, 1, 1, 1));



}

void TitleScene::PreUpdate()
{
}
