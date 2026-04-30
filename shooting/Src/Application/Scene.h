#pragma once
class SceneBase;

enum GameFase
{
	title, main, result,

};
class Scene
{
private:

	static const int WindowWIDTH = 1280;
	static const int WindowHEIGHT = 720;

	
	float Killcount = 0;

	GameFase nowFase;

	int KillCount;
	std::shared_ptr<SceneBase> m_nowScene;
	std::shared_ptr<SceneBase> m_NextScene;
public:

	// ‰Šúİ’è
	void Init();

	// ‰ğ•ú
	void Release();

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw2D();

	// GUIˆ—
	void ImGuiUpdate(); 

	SceneBase* GetNowScene() { return m_nowScene.get(); }

	POINT getMousePos();

	void SetFase(GameFase ChengeFase) { nowFase = ChengeFase; }
	
	void SetKillcount(int kills) { KillCount = kills; }

	int GetKillCount() { return KillCount; }

	void ChengeScene(GameFase NextFase);
private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
