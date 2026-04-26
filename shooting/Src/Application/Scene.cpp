#include "main.h"
#include "Scene.h"
#include"Character/Player/Player.h"
#include"Character/Enemy/Enemy.h"
#include"Character/Enemy/EnemyTurret.h"
#include"Character/Hit/Hit.h"
#include"Background/Background.h"
#include"Background/Object.h"
void Scene::Draw2D()
{
	// 文字列表示

//	player.Draw();
			background->Draw();
		
				backobj[0]->Draw({288,192});
				backobj[1]->Draw({320,320});
			

	char killstext[50];
	sprintf_s(killstext, "GameOver\n %dKills", (int)player->GetKillCount());
		switch (nowscene)
		{
		case Scene::title:	
			SHADER.m_spriteShader.DrawString(100, 100, "title", Math::Vector4(1, 1, 1, 1));

			break;
		case Scene::main:

			player->Draw();
			for (auto& i : enemy)
			{
				i->Draw();
			}
			for (auto& i : m_turret)
			{
				i->Draw();
			}

			break;
		case Scene::result:

			SHADER.m_spriteShader.DrawString(100, 100, killstext, Math::Vector4(1, 0, 0, 1));

			break;
		default:
			break;
		}
	
}

void Scene::Update()
{
	for (auto& i : m_turret)
	{
		i->Update();
	}
	switch (nowscene)
	{
	case Scene::title:
		for (auto& i : backobj)
		{
			i->Update();
		}
		if (GetAsyncKeyState(VK_RETURN)&0x8000)
		{
			nowscene = main;

		}
		break;
	case Scene::main:

		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			AllEnemy_Kills();
		}


		if (!player->GetAlive())
		{
			nowscene = result;
		}
			player->Action();
			for (auto& i : backobj)
			{
				i->Update();
			}

			player->Update();
			for (auto& i : enemy)
			{
				i->Action();

			}
			hit->Enemy_EnemyHit();
			hit->Enemy_BulletHit();
			hit->Turret_playerHit();
			hit->Enemy_PlayerHit();
			hit->Turret_BulletHit();
			for (auto& i : enemy)
			{
				i->Update();


			}
		
		break;
	case Scene::result:
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			nowscene = title;
			Restart();
		}
		break;
	default:
		break;
	}
	if (!player->GetAlive())
	{
	
	}

}

void Scene::Restart()
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

void Scene::Init()
{	srand(time(0));

player = new C_Player();
background = std::make_shared< C_Background>();
hit = new C_Hit();
for (auto &i :backobj)
{
	i= std::make_shared<C_Object>();


}
for (auto& i : m_turret)
{
	i = new EnemyTurret;
	i->Init(0);
}
	playerTex.Load("Texture/player.png");
	player->SetTex(&playerTex);
	// 画像の読み込み処理
	charaTex.Load("player.png");	
	player->Init(100);

	bulletTex.Load("Texture/bullet.png");
	player->BulletSetTex(&bulletTex);

	enemyTex.Load("Texture/enemy.png");
	grassTex.Load("Texture/Grass3.png");
	for(auto&i:enemy)
	{
		i = std::make_shared < C_Enemy>();
i->SetTex(&enemyTex);
i->Init(300);
i->SetGrassTex(&grassTex);
	}
	TurretTex.Load("Texture/enemy2.png");
	for (auto& i : m_turret)
	{
		i = new EnemyTurret;
		i->Init(0);
		i->SetTex(&TurretTex);
		i->SetBulletTex(&bulletTex);
	}

	BackObjTex[0].Load("Texture/object.png");
	BackObjTex[1].Load("Texture/object2.png");
	
	backobj[0]->Init();
	backobj[1]->Init();
	backobj[0]->SetTex(&BackObjTex[0]);
	backobj[1]->SetTex(&BackObjTex[1]);

}

void Scene::Release()
{
	// 画像の解放処理
	charaTex.Release();


	delete player;
	delete hit;
	
	playerTex.Release();
	bulletTex.Release();
	grassTex.Release();
	enemyTex.Release();

}

void Scene::ImGuiUpdate()
{
	

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		player->ImGuiUpdate();
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}

POINT Scene::getMousePos()
{
	POINT mousepos;
	GetCursorPos(&mousepos);//ディスプレイが基準

	ScreenToClient(APP.m_window.GetWndHandle(), &mousepos);//ウィンドウ座標に変換
	// マウス座標を表示

	mousepos.x -= WindowWIDTH / 2;
	mousepos.y -= WindowHEIGHT / 2;
	mousepos.y *= -1;//Yを反転
	return mousepos;
}

void Scene::AllEnemy_Kills()
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
