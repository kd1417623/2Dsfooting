#include"Player.h"
#include"../../Scene.h"
#include "Bullet.h"
C_Player::C_Player()
{
	angle = 0.0f;
	center = { 0.0f, 0.0f };
}
C_Player::~C_Player()
{
}

void C_Player::Update()
{

	if (HP<=0)
	{
		alive = false;

	}
	//pos.x = center.x + cosf(angle) * radius;
	//pos.y = center.y + sinf(angle) * radius;
	pos += move;
	move = { 0,0 };
	 mouseangle = atan2f(
		SCENE.getMousePos().y - pos.y,
		SCENE.getMousePos().x - pos.x
	);	
	mouseangle -= ToRadians(90);

	mat = Math::Matrix::CreateRotationZ(mouseangle) *
		Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
	playeranimX+=0.5;
}


void C_Player::Draw()
{
	if (!alive)
	{
		return;
	}
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(tex, Math::Rectangle{(int)playeranimX*64,0,64,64 }, 1.0f);
	for(auto& bullet : m_bullet)
	{
		bullet.Draw(false);
	}
}

void C_Player::Init(float	 circlesize)
{
	radius = circlesize;

	pos = Math::Vector2(0, radius);
	move = { 0,0 };
	movecount = { 0,0 };
	posMax = { radius,radius };

	 mouseangle = atan2f(
		SCENE.getMousePos().y - pos.y,
		SCENE.getMousePos().x - pos.x
	);
	mouseangle -= ToRadians(90);
	mat = Math::Matrix::CreateRotationZ(mouseangle) *
		Math::Matrix::CreateTranslation(pos.x, pos.y, 0);

	for(auto& bullet : m_bullet)
	{
		bullet.Init();
	}


}

void C_Player::Action()
{
	if (!alive)
	{
		return;
	}
	//‰ŠúˆÄ==============================
	//if (GetAsyncKeyState('A') & 0x8000)
	//{
	//	angle += 0.05f; // ¶‰ñ“]
	//}

	//if (GetAsyncKeyState('D') & 0x8000)
	//{
	//	angle -= 0.05f; // ‰E‰ñ“]
	//}

	//if (GetAsyncKeyState('W')&0x8000)
	//{

	//	radius+=5;
	//}
	//if (GetAsyncKeyState('S')&0x8000)
	//{
	//	radius-=5;
	//}
	//====================================
	if (GetAsyncKeyState('A') & 0x8000)
	{
		move.x = -21.0f;
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		move.x = 21.0f; 
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{

		move.y = 21;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		move.y =-21;
	}
	if (GetAsyncKeyState(VK_LBUTTON)&0x8000)
	{
		for (auto & i :m_bullet)
		{
		if(!i.Shot(pos, Math::Vector2(cosf(mouseangle + ToRadians(90))*30, sinf(mouseangle + ToRadians(90))*30)))
			{
				break;
		}

		}
	}
	else if (GetAsyncKeyState(VK_RBUTTON)&0x8000)
	{
		for (auto& i : m_bullet)
		{
			if (!i.Shot(pos+ Math::Vector2(cosf(mouseangle + ToRadians(90)) * 50, sinf(mouseangle + ToRadians(90)) * 50), Math::Vector2(cosf(mouseangle + ToRadians(90)) * 30, sinf(mouseangle + ToRadians(90)) * 30)))
			{				i.SetFreeze(true);

				break;
			}


		}
	}
	else
	{
		for (auto& i : m_bullet)
		{
			i.SetFreeze(false);
		}
	}
	for (auto& bullet : m_bullet)
	{
		bullet.Update();
	}
}
void C_Player::ImGuiUpdate()
{
	ImGui::Text("Player Pos : (%.2f, %.2f)", pos.x, pos.y);

}

void C_Player::BulletSetTex(KdTexture* tex)
{
	for (auto& bullet : m_bullet)
	{
		bullet.SetTexture(tex);
	}
}
