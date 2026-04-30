#include"SceneBase.h"
#include"../Character/Player/Player.h"
#include"../Character/Enemy/Enemy.h"
#include"../Character/Enemy/EnemyTurret.h"
#include"../Character/Hit/Hit.h"
#include"../Background/Background.h"
#include"../Background/Object.h"
void SceneBase::AllNew()
{// 画像の読み込み処理
	BackObjTex[0].Load("Texture/object.png");
	BackObjTex[1].Load("Texture/object2.png");
	playerTex.Load("Texture/player.png");
	charaTex.Load("player.png");
	enemyTex.Load("Texture/enemy.png");
	grassTex.Load("Texture/Grass3.png");
	TurretTex.Load("Texture/enemy2.png");
	bulletTex.Load("Texture/bullet.png");

	player = std::make_shared< C_Player>();
	hit = std::make_shared< C_Hit>();

	background = std::make_shared< C_Background>();
	for (auto& i : backobj)
	{
		i = std::make_shared<C_Object>();


	}
	for (auto& i : m_turret)
	{
		i = std::make_shared< EnemyTurret>();
		i->SetTex(&TurretTex);
		i->SetBulletTex(&bulletTex);
	}

	for (auto& i : enemy)
	{
		i = std::make_shared < C_Enemy>();
		i->SetTex(&enemyTex);
		i->SetGrassTex(&grassTex);
	}

	player->SetTex(&playerTex);
	backobj[0]->SetTex(&BackObjTex[0]);
	backobj[1]->SetTex(&BackObjTex[1]);
	player->BulletSetTex(&bulletTex);


}

void SceneBase::Restart()
{
	player->Init(100);
	for (auto& i : enemy)
	{
		i->Init(300);
		i->SetAlive(true);
		i->SetHP(100);
	}
	player->SetAlive(true);
	player->SetHP(100);
}

void SceneBase::AllEnemy_Kills()
{
	for (auto& i : enemy)
	{
		i->Damage(1000);
	}
	for (auto& i : m_turret)
	{
		i->Damage(1000);
	}
}

void SceneBase::AllInit()
{
	for (auto& i : m_turret)
	{
		i->Init(0);
	}

	player->Init(100);



	for (auto& i : enemy)
	{
		i->Init(300);
	}
	for (auto& i : m_turret)
	{
		i->Init(0);
	}



	backobj[0]->Init();
	backobj[1]->Init();
	background->Init();
}

