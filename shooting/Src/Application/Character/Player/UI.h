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


};

