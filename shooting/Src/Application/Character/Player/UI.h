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



	KdTexture* NumerTex;
	Math::Matrix ScoreMat;


};

