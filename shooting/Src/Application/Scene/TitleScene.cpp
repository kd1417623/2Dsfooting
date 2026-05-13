#include"TitleScene.h"
#include"../Character/Player/Player.h"
#include"../Character/Enemy/Enemy.h"
#include"../Character/Enemy/EnemyTurret.h"
#include"../Character/Hit/Hit.h"
#include"../Background/Background.h"
#include"../Background/Object.h"
#include"../Character/Player/UI.h"
#include"../Character/Effect/Glassval2.h"
#include"../Character/Effect/Nois.h"
#include"../Scene.h"
TitleScene::TitleScene()
{	
	TitleLogoTex.Load("Texture/TitleLogo.png");
	StartButtonTex.Load("Texture/PlayText.png");
	
	NoisTex.Load("Texture/nois.png");
	
	AllNew();
	for (auto & g:grass)
	{
		g = std::make_shared<Glassval2>();
		g->settex(&grassTex);
		g->Init();
		//g->Emit(Math::Vector2{ 0,-380 }, false);


	}

	for (auto& n : nois)
	{
		n = std::make_shared<C_Nois>();
		n->SetTex(&NoisTex);
		n->Init(Math::Vector2{ -300,20 }, Math::Vector2{ 100,20 }, Math::Vector2{ -100,-100 });
	}
	float RogoAnim = 0.8f;

}

TitleScene::~TitleScene()
{
	TitleLogoTex.Release();
	StartButtonTex.Release();
}

void TitleScene::Update()
{

	for (auto& n : nois)
	{
		n->Update();
	}
	for (auto& g : grass)
	{
	
			if (g->GetPos().y<-360||!g->GetFirst())
			{
			//	g->Emit({0,360 }, false);
			}

		
		
		g->Update();
	}
	for (auto& i : backobj)
	{
		i->Update();
	}

	if (PlayButtonAnim&&! AimPlay())
	{
		PlaybuttonAlpha -= 0.02f;
		if (PlaybuttonAlpha <= 0.3f)
		{
			PlayButtonAnim = false;
		}

	}
	else
	{
		if (PlaybuttonAlpha>=1.0f)
		{
			PlayButtonAnim = true;
		}
		else
		{
		PlaybuttonAlpha += 0.02f;

		}
	}

	if (AimPlay())
	{
		PlayButtonScale = 1.2;
	}
	else
	{
		PlayButtonScale = 1.0f;

	}
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			ClickMouse = true;

		}
		else if (ClickMouse)
		{
			RogoAnim -= 0.02;
		
			SCENE.ChengeScene(main);
			return;

			
		}

	

	for (auto& g : grass)
	{
		g->Update();
	}

	if (TitleRogoAnim)
	{
		if (TitleRogoAlpha>=1.0f)
		{
			TitleRogoAnim = false;


		}
		else
		{
		TitleRogoAlpha += 0.01f;

		}
	}
	else
	{
		if (TitleRogoAlpha <= 0.9f)
		{
			TitleRogoAnim = true;


		}
		else
		{
			TitleRogoAlpha -= 0.01f;

		}
	
	}
	Math::Vector2 RogoScale = { 0.8f,0.8 };
	TitleLogoMat = Math::Matrix::CreateScale(Math::Vector3{ RogoScale.x, RogoScale.y, 1.0f }) * Math::Matrix::CreateTranslation(0, 80, 0);
	StartButtonMat = Math::Matrix::CreateScale(PlayButtonScale) * Math::Matrix::CreateTranslation(PlayButtonPos.x, PlayButtonPos.y, 0);
}

void TitleScene::Init()
{

	AllInit();
}

void TitleScene::Draw()
{
	background->Draw();
	D3D.SetBlendState(BlendMode::Add);
	for (auto& n : nois)
	{
		n->Draw();
	}
	SHADER.m_spriteShader.SetMatrix(TitleLogoMat);
	SHADER.m_spriteShader.DrawTex(&TitleLogoTex, Math::Rectangle{ 0,0,1000,562 }, 1.0f);
	//SHADER.m_spriteShader.DrawTex(&TitleLogoTex, Math::Rectangle{ 0,0,1000,562 }, TitleRogoAlpha);

	SHADER.m_spriteShader.SetMatrix(StartButtonMat);
	SHADER.m_spriteShader.DrawTex(&StartButtonTex, Math::Rectangle{ 0,0,238,100 }, PlaybuttonAlpha);
	for (auto& g : grass)
	{
		g->Draw();
	}
	D3D.SetBlendState(BlendMode::Alpha);


	m_ui->DrawCursor();


}

void TitleScene::PreUpdate()
{
}

bool TitleScene::AimPlay()
{

	mousePos = Math::Vector2{ (float)SCENE.getMousePos().x, (float)SCENE.getMousePos().y };

	if (abs(mousePos.x)<110&&mousePos.y<-167&&mousePos.y>-234)
	{
		return true;
	}
	return false;
}

void TitleScene::ImGuiUpdate()
{

	ImGui::Text("mousePosX:%f", mousePos.x);
	ImGui::Text("mousePosY:%f", mousePos.y);
}
