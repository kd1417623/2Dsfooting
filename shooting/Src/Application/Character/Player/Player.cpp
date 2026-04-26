#include"Player.h"
#include"../../Scene.h"
#include"../Hit/Hit.h"
#include "../Skill/Bullet.h"
C_Player::C_Player()
{
	for (auto& bullet : m_bullet)
	{
		bullet = new C_Bullet();
	}
	angle = 0.0f;
	center = { 0.0f, 0.0f };
}
C_Player::~C_Player()
{
	for (auto& bullet : m_bullet)
	{
		delete bullet;
	}
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
	scroll = pos;
	move = { 0,0 };
	
	if (AutoShot)
	{
		mouseangle = atan2f(
			SCENE.GetHit()->DisCompare().y - pos.y ,
			SCENE.GetHit()->DisCompare().x - pos.x 
		);


	}
	else
	{
		mouseangle = atan2f(
			SCENE.getMousePos().y - pos.y + scroll.y,
			SCENE.getMousePos().x - pos.x + scroll.x
		);


	}
	mouseangle -= ToRadians(90);

	mat = Math::Matrix::CreateRotationZ(mouseangle) *
		//Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		Math::Matrix::CreateTranslation(pos.x- scroll.x, pos.y - scroll.y, 0);
	playeranimX+=0.5;
}


void C_Player::Draw()
{
	if (!alive)
	{
		return;
	}
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.C_DrawTex(tex, Math::Rectangle{(int)playeranimX*64,0,64,64 }, m_color);
	for(auto& bullet : m_bullet)
	{
		bullet->Draw(false);
	}
	m_color = { 1,1,1,1 };

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

	for (auto& bullet : m_bullet)
	{
	
		bullet->Init();
	}


}

void C_Player::Action()
{
	if (!alive)
	{
		return;
	}
	//èâä˙àƒ==============================
	//if (GetAsyncKeyState('A') & 0x8000)
	//{
	//	angle += 0.05f; // ç∂âÒì]
	//}

	//if (GetAsyncKeyState('D') & 0x8000)
	//{
	//	angle -= 0.05f; // âEâÒì]
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
	if (GetAsyncKeyState(VK_LBUTTON)&0x8000||AutoShot)
	{
		if (OverHeat < OverHeatMax)
		{
			OverHeat++;


		}
		else
		{
			OverHeatflg = true;
		}
		//if (!OverHeatflg)
		if (1)
		{


			for (auto& i : m_bullet)
			{
				if (!i->Shot(pos, Math::Vector2(cosf(mouseangle + ToRadians(90)) * 30, sinf(mouseangle + ToRadians(90)) * 30)))
				{
					break;
				}

			}
		}
		else
		{
			OverHeat--;
			if (OverHeat <= 0)
			{
				OverHeatflg = false;

			}
		}
		
	}

 else if (GetAsyncKeyState(VK_RBUTTON)&0x8000)
	{
		for (auto& i : m_bullet)
		{
			if (!i->Shot(pos+ Math::Vector2(cosf(mouseangle + ToRadians(90)) * 50, sinf(mouseangle + ToRadians(90)) * 50)-scroll, Math::Vector2(cosf(mouseangle + ToRadians(90)) * 30, sinf(mouseangle + ToRadians(90)) * 30)))
			{				
				i->SetFreeze(true);

				break;
			}


		}
	}
	else
	{
		for (auto& i : m_bullet)
		{
			i->SetFreeze(false);
		}
	}
	for (auto& bullet : m_bullet)
	{
		bullet->Update();
	}

	if (GetAsyncKeyState('Q')&0x8000)
	{
		AutoShot = true;

	}
	else
	{
		AutoShot = false;
	}


	if (OverHeatflg)
	{
		OverHeat--;
		if (OverHeat<=0)
		{
			OverHeatflg = false;

		}
	}

	if (AutoShot)
	{

	}
}
void C_Player::ImGuiUpdate()
{
	ImGui::Text("Player Pos : (%.2f, %.2f)", pos.x, pos.y);
	ImGui::Text("Hp : %.2f", HP);
	ImGui::Text("OH%.2f",OverHeat);

}

void C_Player::BulletSetTex(KdTexture* tex)
{
	for (auto& bullet : m_bullet)
	{
		bullet->SetTexture(tex);
	}
}

C_Bullet* C_Player::GetBullet(int num)
{
	return m_bullet[num];
}
