#include "GameScene.h"
#include"../Character/Player/Player.h"
#include"../Character/Enemy/Enemy.h"
#include"../Character/Enemy/EnemyTurret.h"
#include"../Character/Hit/Hit.h"
#include"../Background/Background.h"
#include"../Background/Object.h"
#include"../Character/Player/UI.h"
#include "../Scene.h"
#include"../Character/Enemy/Boss.h"
GameScene::GameScene()
{
	AllNew();
	HpBarMaxTex.Load("Texture/HpMaxBar.png");
	HpBarTex   .Load("Texture/HpBar.png");
	HpTex      .Load("Texture/HpText.png");

	NumDecoTex.Load("Texture/Number5.png");

	NumberTex.Load("Texture/Number4.png");

	bossgalasstex.Load("Texture/Grass3.png");
	bossTex.Load("Texture/Boss.png");
	LaserTex.Load("Texture/laser.png");
	barnerTex.Load("Texture/Exhaust-0001.png");


	ComboTextTex.Load("Texture/ComboText2.png");
//	player->SebBarnerTex(&barnerTex);

	boss = std::make_shared<C_BOSS>(); 

	boss->setlasertex(&LaserTex);
	boss->SetTex(&bossTex);
	boss->setgallastex(&bossgalasstex);
	boss->Init(0);

	m_ui->SetScoreDecoTex(&NumDecoTex);

	m_ui->SetComboTextTex(&ComboTextTex);
	

	m_ui->SetNumTex(&NumberTex);
	CountDounRect = { 0,0,220,160 };
	m_ui->SetHptex(&HpBarTex, &HpTex, &HpBarMaxTex);
	count = countMax;
	IsCountDown = true;


	CountDounPictAnim = NumberOneSec*4;
	AllInit();
	PreUpdate();


	SCENE.SetClearFlag(false);
	SCENE.SetScore(0);
	SCENE.SetKillcount(0);
	SCENE.SetMaxCombo(0);
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
		


			player->Action();
			if (!gameStart)
			{
				if (GetAsyncKeyState(VK_RBUTTON))
				{


					gameStart = true;
				}
			}
			else
			{
			if (BossBattleStart)
			{
				boss->Update();
				hit->Boss_BulletHit();
				if (GetAsyncKeyState(VK_RETURN)&0x8000)
				{
					boss->Damage(boss->GetHp());
				}

			}

			for (auto& i : enemy)
			{
				i->Action();


			}


			if (GetAsyncKeyState('E')&0x8000)
			{
				if (!DebugInvincibleKeyFlg)
				{
					debugInvincible = !debugInvincible;
					DebugInvincibleKeyFlg = true;
				}
			}
			else
			{
				DebugInvincibleKeyFlg = false;
			}
			if (!debugInvincible)
			{
			hit->Turret_playerHit();
			hit->Enemy_PlayerHit();


			}
			
			hit->Enemy_BulletHit();

			hit->Enemy_EnemyHit();
			hit->Turret_BulletHit();



			for (auto& i : enemy)
			{
				i->Update();


			}
			for (auto& t : m_turret)
			{
				t->Update();
			}
			if (SCENE.GetScore() > 200000 && !BossBattleStart)
			{
				BossBattleStart = true;
				AllEnemy_Kills();
			}
			else
			{
				if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
				{
					SCENE.SetScore(200000);
				}
			}
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

	

	
	if (!player->GetAlive()||SCENE.GetClearFlag())
	{
		SCENE.SetKillcount(player->GetKillCount());
		if (SCENE.GetClearFlag())
		{
			SCENE.SetScore(SCENE.GetScore() * 2);
		}
		SCENE.ChengeScene(result);
		return;
	}
	m_ui->ScoreUpdate();
	
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

		backobj[0]->Draw({ 288,192 });
		backobj[1]->Draw({ 320,320 });
		
		boss->Draw();


			for (auto& i : enemy)
			{
				i->Draw();
			}

			for (auto& i : m_turret)
			{
				i->Draw();
			}

			player->Draw();

			m_ui->Draw();


			m_ui->ScoreDraw();

			CountDounDraw();

			m_ui->DrawCursor();

}

void GameScene::CountDounDraw()
{
	D3D.SetBlendState(BlendMode::Add);

	Math::Color color = { 0,1,1,1 };
	SHADER.m_spriteShader.SetMatrix(CountDounMat);
	SHADER.m_spriteShader.C_DrawTex(&NumberTex, CountDounRect, color);
	D3D.SetBlendState(BlendMode::Add);
	SHADER.m_spriteShader.SetMatrix(NumDecoMat);
	SHADER.m_spriteShader.C_DrawTex(&NumDecoTex, Math::Rectangle {0,0,155,126}, color);
	D3D.SetBlendState(BlendMode::Alpha);
}

void GameScene::CountDounUpdate()
{
	NumDecoMat = Math::Matrix::CreateScale(1) ;
	CountDounMat = Math::Matrix::CreateScale(3) * Math::Matrix::CreateTranslation(0, 0, 0);
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


	CountDounRect = { 0, (int)CountDounPictAnim, 30, 30 };

	if (CountDounPictAnim> number * NumberOneSec ||(count<=0&&CountDounPictAnim>-NumberOneSec))
	{
		CountDounPictAnim -= 3;
	}
}

void GameScene::ImGuiUpdate()
{
	boss->ImGUIUpdate();
}

