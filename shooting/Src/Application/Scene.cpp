#include "main.h"
#include "Scene.h"
#include"Scene/GameScene.h"
#include"Scene/SceneBase.h"
#include"Scene/TitleScene.h"
#include"Scene/ResultScene.h"
void Scene::Draw2D()
{
	// 文字列表示

//	player.Draw();




	m_nowScene->Draw();
	
	
}

void Scene::Update()
{
	if (m_nowScene==nullptr)
	{
		return;
	}
	m_nowScene->Update();
	




}


void Scene::Init()
{
	srand(time(0));
	m_nowScene = std::make_shared<TitleScene>();



}

void Scene::Release()
{

}

void Scene::ImGuiUpdate()
{
	return;
	

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
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

void Scene::ChengeScene(GameFase NextFase)
{
	if (nowFase!=NextFase)
	{
		nowFase = NextFase;
		switch (NextFase)
		{
		case title:
			m_nowScene = std::make_shared<TitleScene>();
			break;
		case main:m_nowScene = std::make_shared<GameScene>();
			break;
		case result:m_nowScene = std::make_shared<ResultScene>();
			break;
		default:
			break;
		}

		m_nowScene->Init();
	}
}

