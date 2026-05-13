#pragma once
#include "SceneBase.h"
class Glassval2;
class C_Nois;
	class TitleScene :public SceneBase
{
public:
	TitleScene ();
	~TitleScene ();

	void Update() override;
	void Init() override;
	void Draw() override;
	void PreUpdate() override;
	bool AimPlay();

	void ImGuiUpdate() override;
private:
	Math::Matrix TitleLogoMat;
	Math::Matrix StartButtonMat;

	KdTexture TitleLogoTex;
	KdTexture StartButtonTex;

	Math::Vector2 PlayButtonPos = { 0,-200 };

	float PlayButtonScale = 1.0f;

	Math::Vector2 mousePos;


	bool PlayButtonAnim = false;
	float PlaybuttonAlpha = 1.0f;


	std::shared_ptr<Glassval2> grass[100];
	std::shared_ptr<C_Nois> nois[5];
	

	bool ClickMouse = false;



	float TitleRogoAlpha = 1.0f;
	bool TitleRogoAnim = false;

	bool PlayAnim = false;
	float RogoAnim = 1.0f;


	KdTexture NoisTex;

	float Rnd() { return rand() / (float)RAND_MAX; };


};

