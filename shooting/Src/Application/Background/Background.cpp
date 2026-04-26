#include"Background.h"
#include"../Scene.h"
#include"../Character/Player/Player.h"
C_Background::C_Background()
{
}

C_Background::~C_Background()
{
}

void C_Background::Update()
{
	PlayerScroll = SCENE.GetPlayer()->GetScroll();

}

void C_Background::Draw()
{
	Math::Color color = Math::Color(0, 0, 0, 1);

	
		SHADER.m_spriteShader.SetMatrix(mat);
		SHADER.m_spriteShader.DrawBox(0, 0, 1280, 720, &color, true);
	


	//SHADER.m_spriteShader.DrawTex(backtex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	//for (int i = 0; i < objectnum; i++)
	//{
	//	SHADER.m_spriteShader.SetMatrix(objmat[i]);
	//	SHADER.m_spriteShader.DrawTex(objecttex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
	//}
}

void C_Background::Init()
{
}
