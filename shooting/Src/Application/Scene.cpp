#include "main.h"
#include "Scene.h"

void Scene::Draw2D()
{
	// 文字列表示

	player.Draw();

	for (auto& i : enemy)
	{
		i.Draw();
	}

	if (!player.GetAlive())
	{
		SHADER.m_spriteShader.DrawString(100, 100, "GameOver", Math::Vector4(1, 0, 0, 1));
	}
}

void Scene::Update()
{
	if (!player.GetAlive())
	{
		if (GetAsyncKeyState(VK_RETURN)&0x8000)
		{
			Restart();
		}
	}
	player.Action();
	player.Update();
	for (auto& i : enemy)
	{
		i.Action();

	}
	hit.Enemy_EnemyHit();
	hit.Enemy_BulletHit();

	hit.Enemy_PlayerHit();
	for (auto& i : enemy)
	{
		i.Update();


	}
}

void Scene::Restart()
{
	player.Init(100);
	for (auto& i : enemy)
	{
		i.Init(300);
		i.SetAlive(true);
		i.SetHP(100);
	}
	player.SetAlive(true);
	player.SetHP(100);
}

void Scene::Init()
{	srand(time(0));


	playerTex.Load("Texture/player.png");
	player.SetTex(&playerTex);
	// 画像の読み込み処理
	charaTex.Load("player.png");	
	player.Init(100);

	bulletTex.Load("Texture/bullet.png");
	player.BulletSetTex(&bulletTex);

	enemyTex.Load("Texture/enemy.png");

	for(auto&i:enemy)
	{
i.SetTex(&enemyTex);
i.SetBulletTex(&bulletTex);
i.Init(300);
	}


}

void Scene::Release()
{
	// 画像の解放処理
	charaTex.Release();
}

void Scene::ImGuiUpdate()
{
	

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		player.ImGuiUpdate();
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
