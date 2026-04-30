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

private:
	std::shared_ptr<UI> m_ui;

	KdTexture HpTex, HpBarTex, HpBarMaxTex;



	const float countMax=240;
	float count = countMax;;

	bool IsCountDown=true;



	KdTexture NumberTex;
	Math::Matrix CountDounMat;

	Math::Rectangle CountDounRect;



	float CountDounPictAnim;
	const float NumberOneSec = 160;
};