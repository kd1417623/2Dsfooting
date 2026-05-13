#include"ResultScene.h"
#include"../Background/Background.h"
#include"../Scene.h"
#include"../Character/Player/UI.h"
ResultScene::ResultScene()
{
	AllNew();
	Init();
}

ResultScene::~ResultScene()
{
	NumDecoTex.Release();
	NumerTex.Release();
}

void ResultScene::Update()
{
	m_GameOverMat = Math::Matrix::CreateScale(1.5) * Math::Matrix::CreateTranslation(0, 230, 0);
	

	int ScoreRectYGall[ScoreNumMax];
	SCENE.CalcScoreNum(SCENE.GetScore());
	for (int i = 0; i < ScoreNumMax; i++)
	{
		ScoreRectYGall[i] = (SCENE.GetScoreNum(i) * 30) + 30;

	}
	for (int i = 0; i < ScoreNumMax; i++)
	{
		if (ScoreRectY[i] < ScoreRectYGall[i])
		{

			ScoreRectY[i] += 3;

		}
		else if (ScoreRectY[i] > ScoreRectYGall[i])
		{
			ScoreRectY[i] = 0;

		}
		ScoreMat[i] = Math::Matrix::CreateScale(2) * Math::Matrix::CreateTranslation(450 - (i * 40), 30, 0);

		NumDecoMat[0] = Math::Matrix::CreateScale(1) * Math::Matrix::CreateTranslation(490 - (ScoreNumMax * 40),30, 0);
		NumDecoMat[1] = Math::Matrix::CreateScale(1) * Math::Matrix::CreateTranslation(460, 30, 0);


	}

	if (AimTitle())
	{
		TitleButtonScale = 1.2;
		if (GetAsyncKeyState(VK_LBUTTON)&0x8000)
		{
			ClickMouse = true;

		}
		else if (ClickMouse)
		{
			SCENE.ChengeScene(title);
			return;
		}

	}
	else
	{
		TitleButtonScale = 1.0f;

	}
	


		if (TitleButtonAnim&&! AimTitle())
		{
			TitlebuttonAlpha -= 0.02f;
			if (TitlebuttonAlpha <= 0.3f)
			{
				TitleButtonAnim = false;
			}

		}
		else
		{
			if (TitlebuttonAlpha >= 1.0f)
			{
				TitleButtonAnim = true;
			}
			else
			{			TitlebuttonAlpha += 0.02f;


			}
		}
	
	ScoreTextMat = Math::Matrix::CreateScale(2) * Math::Matrix::CreateTranslation(-150, 30, 0);

	m_TitleButtonMat = Math::Matrix::CreateScale(TitleButtonScale) * Math::Matrix::CreateTranslation(TitleButtonPos.x, TitleButtonPos.y, 0);


}

void ResultScene::Init()
{
	AllInit();

	NumDecoTex.Load("Texture/Number5.png");
	NumerTex.Load("Texture/Number4.png");
	ScoreTextTex.Load("Texture/ScoreText2.png");
	m_TitleButtonTex.Load("Texture/TitleText.png");
	m_GameOverTex.Load("Texture/GaeOverText2.png");
	m_clearTex.Load("Texture/CLEARText.png");
}

void ResultScene::Draw()
{
	background->Draw();
	D3D.SetBlendState(BlendMode::Add);

	if (SCENE.GetClearFlag())
	{

	
		NumberDraw();
		SHADER.m_spriteShader.SetMatrix(m_GameOverMat);
		SHADER.m_spriteShader.DrawTex(&m_clearTex, Math::Rectangle{ 0,0,200,53 }, 1.0f);

	}
	else
	{
		NumberDraw();
		SHADER.m_spriteShader.SetMatrix(m_GameOverMat);
		SHADER.m_spriteShader.DrawTex(&m_GameOverTex, Math::Rectangle{ 0,0,238,158 }, 1.0f);
	}


	SHADER.m_spriteShader.SetMatrix(ScoreTextMat);
	SHADER.m_spriteShader.DrawTex(&ScoreTextTex, Math::Rectangle{ 0,0,224,100 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_TitleButtonMat);
	SHADER.m_spriteShader.DrawTex(&m_TitleButtonTex, Math::Rectangle{ 0,0,227,100 }, TitlebuttonAlpha);


	D3D.SetBlendState(BlendMode::Alpha);

	m_ui->DrawCursor();


}

void ResultScene::PreUpdate()
{
}

void ResultScene::NumberDraw()
{

	for (int i = 0; i < ScoreNumMax; i++)
	{


		SHADER.m_spriteShader.SetMatrix(ScoreMat[i]);
		SHADER.m_spriteShader.DrawTex(&NumerTex, Math::Rectangle{ 0,(int)ScoreRectY[i],30, 30 }, 1.0f);
	}


	SHADER.m_spriteShader.SetMatrix(NumDecoMat[0]);
	SHADER.m_spriteShader.DrawTex(&NumDecoTex, Math::Rectangle{ 0,0,50,126 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(NumDecoMat[1]);
	SHADER.m_spriteShader.DrawTex(&NumDecoTex, Math::Rectangle{ 100,0,50,126 }, 1.0f);
}

bool ResultScene::AimTitle()
{

	mousePos = Math::Vector2{ (float)SCENE.getMousePos().x, (float)SCENE.getMousePos().y };

	if (abs(mousePos.x) < 110 && mousePos.y<-167 && mousePos.y>-234)
	{
		return true;
	}
	return false;
}

