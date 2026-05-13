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

	bool ClearFlag = false;

	int Score = 0;
	static const int ScoreNumMax = 10;
	int ScoreNumber[ScoreNumMax] = { {} };

	float Killcount = 0;


	const float ComboTimeMax = 120.0f;

	float ComboTime = ComboTimeMax;
	bool ComboFlag = false;
	float Combocount = 0;
	
	float ComboMax = 0;


	float ComboNum[3] = { {} };

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




	void SetMaxCombo(float combo) { ComboMax = combo; }
	float GetMaxCombo() { return ComboMax; }
	static const int GetScoreNumMax() { return ScoreNumMax; }



	void SetComboTime(float time) { ComboTime = time; }
	float GetComboTime() { return ComboTime; }
	float GetComboTimeMax() { return ComboTimeMax; }

	bool GetComboFlag() { return ComboFlag; }


	void ComboUpdate() {
		CalcComboNum(Combocount);
		if (ComboTime <= 0)
		{
			ComboFlag = false;
			if (Combocount > ComboMax)
			{
				ComboMax = Combocount;

			}
			Combocount = 0;
		}
		else
		{
			ComboFlag = true;
			ComboTime--;
		}
	}
	void ComboReset() {
		ComboTime = ComboTimeMax;
		Combocount++;

	}

	float GetComboCount() { return Combocount; }


	void CalcComboNum(int combo) {
		for (int i = 0; i < 3; i++)
		{
			ComboNum[i] = combo % 10;
			combo /= 10;
		}
	}
	float GetComboNum(int num) { 
	return ComboNum[num]; }




	int GetWindowWIDTH() { return WindowWIDTH; }
	int GetWindowHEIGHT() { return WindowHEIGHT; }



	void SetClearFlag(bool flag) { ClearFlag = flag; }
	bool GetClearFlag() { return ClearFlag; }
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
