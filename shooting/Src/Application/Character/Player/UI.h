#pragma once
class UI
{
public:
	UI();
	~UI();
	void SetHptex(KdTexture* _hpBar, KdTexture* _hpText, KdTexture* _hpBarMax)
	{
		HpBarTex = _hpBar;
		HpTex = _hpText;
		HpBarMaxTex = _hpBarMax;
	};
	void Draw();
	void Update();
	void Init();


	void ScoreDraw();
	void ScoreUpdate();
	void SetNumTex(KdTexture* _tex) { NumerTex = _tex; }


	void SetScoreDecoTex(KdTexture* _tex) { NumDecoTex = _tex; }


	void ComboDraw();
	void ComboUpdate();


	void SetComboTextTex(KdTexture* _tex) { ComboTextTex = _tex; }

	void DrawCursor();

	void SetCursorTex(KdTexture* _tex) { CursorTex = _tex; }

	
private:
	KdTexture* HpBarTex;
	KdTexture* HpBarMaxTex;
	KdTexture* HpTex;

	Math::Matrix HpTextMat;
	Math::Matrix HpBarMat;
	Math::Matrix HpBarMaxMat;

	const float PlayerHpmax = 100;
	
	float HpBarPosX = -400;
	float PlayerHp;


	static const int ScoreNumMax = 10;
	KdTexture* NumerTex;
	Math::Matrix ScoreMat[ScoreNumMax];

	float ScoreRectY[ScoreNumMax] = { {} };

	Math::Matrix NumDecoMat[2];
	KdTexture* NumDecoTex;


	static const int ComboNumMax = 3;
	Math::Matrix ComboMat[ComboNumMax];

	float ComboRectY[ComboNumMax] = { {} };

	Math::Matrix ComboTextMat;
	KdTexture* ComboTextTex;


	KdTexture* CursorTex;

};

