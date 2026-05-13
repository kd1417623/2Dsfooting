#include"Player.h"
#include"../../Scene.h"
#include"../Hit/Hit.h"
#include "../Skill/Bullet.h"
#include"../../Scene/SceneBase.h"
C_Player::C_Player()
{
	for (auto& bullet : m_bullet)
	{
		bullet = std::make_shared<C_Bullet>();
	}
	angle = 0.0f;
	center = { 0.0f, 0.0f };
	pos = { 0,0 };
	scroll = { 0,0 };
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
	scroll = pos;
	move = { 0,0 };
	
	if (AutoShot)
	{
		AimVec = { SCENE.GetNowScene()->GetHit()->DisCompare() - pos  };
		mouseangle = atan2f(
			AimVec.y,
			AimVec.x
		);


	}
	else
	{
		AimVec = { SCENE.getMousePos().x - pos.x, SCENE.getMousePos().y - pos.y };
		mouseangle = atan2f(
			AimVec.y + scroll.y,
			AimVec.x + scroll.x
		);


	}
	mouseangle -= ToRadians(90);
	Math::Vector2 BarnerVec = AimVec;
	BarnerVec.Normalize();
	BarnerVec *= 50;
	mat = 		Math::Matrix::CreateScale(1.5f, 1.5f, 1.0f) *Math::Matrix::CreateRotationZ(mouseangle) *
		
		Math::Matrix::CreateTranslation(pos.x- scroll.x, pos.y - scroll.y, 0);


	
}


void C_Player::Draw()
{
	if (!alive)
	{
		return;
	}
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.C_DrawTex(tex, Math::Rectangle{(int)playeranimX*64,0,71,76 }, m_color);


	for(auto& bullet : m_bullet)
	{
		bullet->Draw(false);
	}
	m_color = { 1,1,1,1 };

}

void C_Player::Init(float	 circlesize)
{
	radius = circlesize;

	pos = Math::Vector2(0, 0);
	move = { 0,0 };
	movecount = { 0,0 };
	posMax = { radius,radius };

	AimVec = { SCENE.getMousePos().x - pos.x,
		SCENE.getMousePos().y - pos.y };
	 mouseangle = atan2f(
		AimVec.y,
		AimVec.x
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
	if (alive)
	{
	
	
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
				Math::Vector2 ShotDir;
				if (AutoShot)
				{
					ShotDir = AimVec;

				}
				else
				{
					ShotDir = AimVec + scroll;

				}
				ShotDir.Normalize();
				if (!i->Shot(pos, ShotDir * 20))
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
		}}
		
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
		if (!ShotKeyFlg)
		{
		AutoShot= ! AutoShot;
		ShotKeyFlg = true;

		}
	

	}
	else
	{
		ShotKeyFlg = false;

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
	return m_bullet[num].get();
}
