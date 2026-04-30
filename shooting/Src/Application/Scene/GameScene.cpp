#include "GameScene.h"
#include"../Character/Player/Player.h"
#include"../Character/Enemy/Enemy.h"
#include"../Character/Enemy/EnemyTurret.h"
#include"../Character/Hit/Hit.h"
#include"../Background/Background.h"
#include"../Background/Object.h"
#include"../Character/Player/UI.h"
#include "../Scene.h"

GameScene::GameScene()
{
	AllNew();
	m_ui = std::make_shared<UI>();
	HpBarMaxTex.Load("Texture/HpMaxBar.png");
	HpBarTex   .Load("Texture/HpBar.png");
	HpTex      .Load("Texture/HpText.png");


	NumberTex.Load("Texture/Number2.png");
	CountDounRect = { 0,0,220,160 };
	m_ui->SetHptex(&HpBarTex, &HpTex, &HpBarMaxTex);
	count = countMax;
	IsCountDown = true;


	CountDounPictAnim = NumberOneSec*4;
	AllInit();
	PreUpdate();
}

GameScene::~GameScene()
{
	HpBarMaxTex.Release();
	   HpBarTex.Release();
		  HpTex.Release();

		  NumberTex.Release();


}

void GameScene::Update()
{
	if (!IsCountDown)

	{

		for (auto& i : enemy)
		{
			i->Action();


		}
		player->Action();

		hit->Enemy_EnemyHit();
		hit->Enemy_BulletHit();
		hit->Turret_playerHit();
		hit->Enemy_PlayerHit();
		hit->Turret_BulletHit();
		for (auto& i : enemy)
		{
			i->Update();


		}
		for (auto& t : m_turret)
		{
			t->Update();
		}
	}
	else
	{
		count--;
		CountDounUpdate();
		if (count<=0)
		{
			IsCountDown = false;
		}
	}


	m_ui->Update();
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		AllEnemy_Kills();
	}


	
	for (auto& i : backobj)
	{
		i->Update();
	}

	player->Update();

	

	
	if (!player->GetAlive())
	{
		SCENE.SetKillcount(player->GetKillCount());
		SCENE.ChengeScene(result);
		return;
	}
}

void GameScene::PreUpdate()
{
	for (auto& i : backobj)
	{
		i->Update();
	}
	m_ui->Update();
	for (auto& i : enemy)
	{
		i->Action();
		i->Update();


	}
	for (auto& t : m_turret)
	{
		t->Update();
	}
	player->Action();
	player->Update();

	CountDounUpdate();

}

void GameScene::Init()
{
	AllInit();
}

void GameScene::Draw()
{
	background->Draw();
	CountDounDraw();

		backobj[0]->Draw({ 288,192 });
		backobj[1]->Draw({ 320,320 });
		player->Draw();
		



			for (auto& i : enemy)
			{
				i->Draw();
			}

			for (auto& i : m_turret)
			{
				i->Draw();
			}

			m_ui->Draw();


		


}

void GameScene::CountDounDraw()
{
	SHADER.m_spriteShader.SetMatrix(CountDounMat);
	SHADER.m_spriteShader.DrawTex(&NumberTex, CountDounRect, 1.0f);
}

void GameScene::CountDounUpdate()
{
	CountDounMat = Math::Matrix::CreateTranslation(0, 0, 0);
//	CountDounRect = { 0,(int)CountDounPictAnim,220,160 };
////	CountDounPictAnim--;
//	if (count<=120)
//	{
//		if (CountDounPictAnim>NumberOneSec*2&&count>=60)
//		{
//			CountDounPictAnim-=5;
//		}
//		if (CountDounPictAnim>NumberOneSec&&count>=10)
//		{
//			CountDounPictAnim-=5;
//		}
//
//	}

	int number = count / 60; 

	CountDounRect = { 0, (int)CountDounPictAnim, 220, 170 };

	if (CountDounPictAnim> number * NumberOneSec ||(count<=0&&CountDounPictAnim>-NumberOneSec))
	{
		CountDounPictAnim -= 5;
	}
}
