#include"UI.h"
#include"../../Scene.h"
#include"../../Scene/GameScene.h"
#include"Player.h"
UI::UI()
{
}

UI::~UI()
{
}

void UI::Draw()
{
	Math::Color m_color = { 1.0f- (PlayerHp / 100),(PlayerHp / 100),0.0f};
	 PlayerHp = SCENE.GetNowScene()->GetPlayer()->GetHp();
	SHADER.m_spriteShader.SetMatrix(HpTextMat);
	SHADER.m_spriteShader.DrawTex(HpTex, Math::Rectangle{ 0,0,100,40 }, 1.0f);
	
		SHADER.m_spriteShader.SetMatrix(HpBarMaxMat);
	SHADER.m_spriteShader.DrawTex(HpBarMaxTex, Math::Rectangle{ 0,0,100,40 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(HpBarMat);
	SHADER.m_spriteShader.C_DrawTex(HpBarTex, Math::Rectangle{ 0,0,(int)PlayerHp,40 },m_color );
	

}

void UI::Update()
{
	HpBarPosX = -400 - ((PlayerHpmax - PlayerHp) * 1.5);

	HpTextMat =Math::Matrix::CreateScale(3)* Math::Matrix::CreateTranslation(-500, 320, 0.0f);

	HpBarMat = Math::Matrix::CreateScale(3) * Math::Matrix::CreateTranslation(HpBarPosX, 320, 0);
	HpBarMaxMat = Math::Matrix::CreateScale(3) * Math::Matrix::CreateTranslation(-400, 320, 0);
}


void UI::ScoreDraw()
{
	D3D.SetBlendState(BlendMode::Add);

	for (int i = 0; i < ScoreNumMax; i++)
	{


		SHADER.m_spriteShader.SetMatrix(ScoreMat[i]);
		SHADER.m_spriteShader.DrawTex(NumerTex, Math::Rectangle{ 0,(int)ScoreRectY[i],30, 30 }, 1.0f);
	}
	SHADER.m_spriteShader.SetMatrix(NumDecoMat[0]);
	SHADER.m_spriteShader.DrawTex(NumDecoTex, Math::Rectangle{ 0,0,50,126 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(NumDecoMat[1]);
	SHADER.m_spriteShader.DrawTex(NumDecoTex, Math::Rectangle{ 100,0,50,126 }, 1.0f);
	D3D.SetBlendState(BlendMode::Alpha);

}

void UI::ScoreUpdate()
{
	int ScoreRectYGall[ScoreNumMax];
	SCENE.CalcScoreNum(SCENE.GetScore());
	for (int i = 0; i < ScoreNumMax; i++)
	{
		 ScoreRectYGall[i] = (SCENE.GetScoreNum(i) * 30)+30;

	}
	for (int i = 0; i < ScoreNumMax; i++)
	{
		if (ScoreRectY[i]<ScoreRectYGall[i])
		{

			ScoreRectY[i] += 3;
		
		}
		else if (ScoreRectY[i] > ScoreRectYGall[i])
		{
			ScoreRectY[i] = 0;

		}
	
		ScoreMat[i] = Math::Matrix::CreateScale(2) * Math::Matrix::CreateTranslation(600 - (i * 40), -300, 0);

		NumDecoMat[0] = Math::Matrix::CreateScale(1) * Math::Matrix::CreateTranslation(640 - (ScoreNumMax * 40), -300, 0);
		NumDecoMat[1] = Math::Matrix::CreateScale(1) * Math::Matrix::CreateTranslation(610, -300, 0);


	}
}

