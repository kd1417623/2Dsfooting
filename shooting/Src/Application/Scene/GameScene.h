#pragma once
#include"SceneBase.h"
class UI;
class GameScene :public SceneBase
{
public:

	GameScene();
	~GameScene();

	void Update() override;
	void PreUpdate() override;
	void Init() override;
	void Draw() override;



	void CountDounDraw();
	void CountDounUpdate(); 

	int GetScore() { return Score; }
	
	void ImGuiUpdate() override;



private:


	KdTexture HpTex, HpBarTex, HpBarMaxTex;



	const float countMax=240;
	float count = countMax;;

	bool IsCountDown=true;



	KdTexture NumberTex;
	Math::Matrix CountDounMat;

	Math::Rectangle CountDounRect;

	bool gameStart = false;

	float CountDounPictAnim;
	const float NumberOneSec = 30;

	int Score = 0;


	KdTexture NumDecoTex;
	Math::Matrix NumDecoMat;



	KdTexture bossTex;
	KdTexture LaserTex;

	KdTexture bossgalasstex;

	KdTexture barnerTex;

	KdTexture ComboTextTex;



	bool debugInvincible = false;
	bool DebugInvincibleKeyFlg = false;


};