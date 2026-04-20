#include"Bullet.h"
C_Bullet::C_Bullet()
{
}

C_Bullet::~C_Bullet()
{
}

bool C_Bullet::Shot( Math::Vector2& pos,  Math::Vector2& move)
{
	if (m_shot)
	{
		return true;
	}
	m_shot = true;
	m_pos = pos;
	m_move = move;
	return false;
}

void C_Bullet::Update()
{
	if (!freze)
	{
		m_pos += m_move;
	}
	if (m_pos.x>1280||m_pos.x<-1280)
	{
		m_shot = false;
	}
	if (m_pos.y>720||m_pos.y<-720)
	{
		m_shot = false;
	}
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
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