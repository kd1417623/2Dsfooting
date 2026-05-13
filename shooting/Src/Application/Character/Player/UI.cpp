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
	ComboDraw();
	

}

void UI::Update()
{
	HpBarPosX = -400 - ((PlayerHpmax - PlayerHp) * 1.5);

	HpTextMat =Math::Matrix::CreateScale(3)* Math::Matrix::CreateTranslation(-500, 320, 0.0f);

	HpBarMat = Math::Matrix::CreateScale(3) * Math::Matrix::CreateTranslation(HpBarPosX, 320, 0);
	HpBarMaxMat = Math::Matrix::CreateScale(3) * Math::Matrix::CreateTranslation(-400, 320, 0);

	ComboUpdate();
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

void UI::ComboDraw()
{
	Math::Color m_color;
	D3D.SetBlendState(BlendMode::Add);
	if (SCENE.GetMaxCombo()<SCENE.GetComboCount())
	{
		m_color = { 1.0f,1.0f,0.0f,1.0f };
	}
	else
	{

	
	m_color = { 0.5f + (SCENE.GetComboCount() / 100),0.5f + (SCENE.GetComboCount() / 100),0.5f + (SCENE.GetComboCount() / 100),1.0f };
	}
	SHADER.m_spriteShader.SetMatrix(ComboMat[0]);
	SHADER.m_spriteShader.C_DrawTex(NumerTex, Math::Rectangle{ 0,(int)ComboRectY[0],30,30}, m_color);
																
	SHADER.m_spriteShader.SetMatrix(ComboMat[1]);				
	SHADER.m_spriteShader.C_DrawTex(NumerTex, Math::Rectangle{ 0,(int)ComboRectY[1],30,30}, m_color);
																 
	SHADER.m_spriteShader.SetMatrix(ComboMat[2]);				 
	SHADER.m_spriteShader.C_DrawTex(NumerTex, Math::Rectangle{ 0,(int)ComboRectY[2],30,30}, m_color);

	SHADER.m_spriteShader.SetMatrix(ComboTextMat);
	SHADER.m_spriteShader.C_DrawTex(ComboTextTex, Math::Rectangle{ 20,0,200,100 }, m_color);
	D3D.SetBlendState(BlendMode::Alpha);
}

void UI::ComboUpdate()
{
	int ComboRectYGall[ComboNumMax];
	int ComboTrueNum= 0;
	SCENE.CalcScoreNum(SCENE.GetScore());
	for (int i = 0; i < ComboNumMax; i++)
	{
		if (SCENE.GetComboNum(i)||i==0||(i==1&&SCENE.GetComboCount()>=10))
		{
			ComboTrueNum = 1;
		}
		else
		{
			ComboTrueNum = 0;
		}
		ComboRectYGall[i] = (SCENE.GetComboNum(i) * 30)+ (ComboTrueNum * 30);
	}
	for (int i = 0; i < ComboNumMax; i++)
	{
		if (ComboRectY[i] < ComboRectYGall[i])
		{

			ComboRectY[i] += 3;

		}
		else if (ComboRectY[i] > ComboRectYGall[i])
		{
			ComboRectY[i] = 0;

		}

	}
		
		for (int i = 0; i <3; i++)
	{
	
		ComboMat[i] = Math::Matrix::CreateScale(1) * Math::Matrix::CreateTranslation(440- (i * 40), 300 , 0);

	}

		ComboTextMat = Math::Matrix::CreateScale(1) * Math::Matrix::CreateTranslation(550, 300, 0);
}

void UI::DrawCursor()
{
	D3D.SetBlendState(BlendMode::Add);
	Math::Color m_color = { 0,1.0f,1.0f,1.0f };

	Math::Matrix m_mat = Math::Matrix::CreateScale(0.7) * Math::Matrix::CreateTranslation((float)SCENE.getMousePos().x, (float)SCENE.getMousePos().y, 0);
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.C_DrawTex(CursorTex, Math::Rectangle{ 0,0,100,100 }, m_color);

	D3D.SetBlendState(BlendMode::Alpha);

}

