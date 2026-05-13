#include"Glassval2.h"
#include"../../Scene/SceneBase.h"
#include"../../Scene.h"
#include"../Player/Player.h"
Glassval2::Glassval2()
{
	m_first = false;
}
Glassval2::~Glassval2()
{
}
void Glassval2::Init()
{
	m_pos = { 0.0f,0.0f };
	m_move = { 0.0f,0.0f };
	m_color = { 1.0f,1.0f,1.0f,0 };
	m_scale = { 0.0f,0.0f };
	m_screenout = false;
}
void Glassval2::Update()
{
	cycle += Rnd() * 10;

	m_pos += m_move;

	m_scale.y -= 0.01f;
	m_scale.x -= 0.01f;
	if (m_scale.x < 0.0f) m_scale = { 0.0f, 0.0f };

	Math::Vector2 Scroll = SCENE.GetNowScene()->GetPlayer()->GetScroll();

	m_mat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(cycle)) *
		Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1.0f) *

		Math::Matrix::CreateTranslation(m_pos.x - Scroll.x, m_pos.y - Scroll.y, 0.0f);


}

void Glassval2::Emit(Math::Vector2 pos,bool vartical)
{
	m_first = true;
	m_vartical = vartical;
	m_color = { 0.0f,0.8f,1.0f,Rnd()*2 };
	m_scale = { Rnd() * 1.5f,Rnd() * 1.5f };

	Math::Vector2 Scroll = SCENE.GetNowScene()->GetPlayer()->GetScroll();
	
	if (vartical)
	{
 m_pos = { pos.x,Rnd() * (640 * 2) - 640+Scroll.y };

	}
	else
	{
	m_pos = { Rnd() * (640 * 2) - 640+Scroll.x,pos.y };

	}

	

	m_move = { Rnd() * 10 - 5,Rnd() * 10-5 };
	m_scalespeed = { Rnd() * 0.1f + 0.05f,Rnd() * 0.1f + 0.05f };
	cycle = Rnd() * 360;

}

Math::Vector2 Glassval2::GetPos()
{
	return m_pos - SCENE.GetNowScene()->GetPlayer()->GetScroll();
}

