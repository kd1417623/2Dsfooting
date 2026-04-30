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

	int Score = 0;
	static const int ScoreNumMax = 10;
	int ScoreNumber[ScoreNumMax] = { {} };

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


	void SetScore(int score) { Score = score; }
	int GetScore() { return Score; }

	void CalcScoreNum(int score) {
		for (int i = 0; i < ScoreNumMax; i++)
		{
			ScoreNumber[i] = score % 10;
			score /= 10;
		}
	}
	int GetScoreNum(int num) { return ScoreNumber[num]; }

	static const int GetScoreNumMax() { return ScoreNumMax; }


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
