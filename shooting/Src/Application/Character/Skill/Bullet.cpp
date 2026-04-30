#include"Bullet.h"
#include"../../Scene.h"
#include"../Player/Player.h"
#include"../../Scene/SceneBase.h"
C_Bullet::C_Bullet()
{
}

C_Bullet::~C_Bullet()
{
}

bool C_Bullet::Shot( Math::Vector2& pos,  Math::Vector2& move)
{
	Math::Vector2 PlayerScroll = SCENE.GetNowScene()->GetPlayer()->GetScroll();

	if (m_shot)
	{
		return true;
	}
	m_shot = true;
	m_pos = pos;
	m_move = move;
	

if(Off_SCreen(pos - PlayerScroll))
{
		m_FadeIn = true;

	}
	else
	{
		m_FadeIn = false;
	}
return false;

}

void C_Bullet::Update()
{
	Math::Vector2 PlayerScroll = SCENE.GetNowScene()->GetPlayer()->GetScroll();
	if (!freze)
	{
		m_pos += m_move;
	}
	
	if (Off_SCreen(m_pos - PlayerScroll))
	 {
		if (!m_FadeIn)
		{
		m_shot = false;

		}
		else
		{
			TimeoutCount--;
			if (TimeoutCount<=0)
			{
				TimeoutCount = Timeout;
				m_FadeIn = false;
			}
		}
	}
	else if (m_FadeIn)
	{
		m_FadeIn = false;
	}

	m_mat = Math::Matrix::CreateTranslation(m_pos.x-PlayerScroll.x, m_pos.y-PlayerScroll.y, 0);
	//m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}
void C_Bullet::Init()
{
	m_shot = false;
}
void C_Bullet::Draw(bool isRed)
{
	if (m_shot)
	{


		if (isRed)
		{
			SHADER.m_spriteShader.SetMatrix(m_mat);
			SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle{ 16,0,16,16 }, 1.0f);


		}
		else
		{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle{ 0,0,16,16 }, 1.0f);

		}
	}
}