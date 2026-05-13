#pragma once
#include "SceneBase.h"
class ResultScene:public SceneBase
{
public:
	ResultScene();
	~ResultScene();
	void Update() override;
	void Init() override;
	void Draw() override;

	void PreUpdate() override;

	void NumberDraw();
	bool AimTitle();

private:

	static const int ScoreNumMax = 10;
	KdTexture NumerTex;
	Math::Matrix ScoreMat[ScoreNumMax];

	float ScoreRectY[ScoreNumMax] = { {} };


	Math::Matrix NumDecoMat[2];
	KdTexture NumDecoTex;


	KdTexture ScoreTextTex;
	Math::Matrix ScoreTextMat;

	Math::Matrix m_TitleButtonMat;
	KdTexture m_TitleButtonTex;


	Math::Vector2 TitleButtonPos = { 0,-200 };

	float TitleButtonScale = 1.0f;

	Math::Vector2 mousePos;


	bool TitleButtonAnim = false;
	float TitlebuttonAlpha = 1.0f;

	bool ClickMouse = false;


	KdTexture m_GameOverTex;
	Math::Matrix m_GameOverMat;
	KdTexture m_clearTex;


const float NumHeight = 1000.0f;

};
