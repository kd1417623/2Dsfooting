#include"Object.h"
#include"../Scene.h"
#include"../Character/Player/Player.h"

#include"../Scene/SceneBase.h"
void C_Object::Update()
{
	auto p = SCENE.GetNowScene()->GetPlayer();
	if (p) {
		m_playermove = p->GetMove();
	}
	else {
	}

	m_pos -= m_playermove;


	if (m_pos.x > 640 + m_size.x)
	{
		m_pos.y = (rand() % 700 - 350);
		m_pos.x = -639 - m_size.x;
		m_scale = (float)rand() / RAND_MAX+ (1.0f / m_size.x);
		m_rotate = rand() % 360 - 180;

	}

	if (m_pos.x <- 640 - m_size.x)
	{
		m_pos.y = (rand() % 700 - 350);
		m_pos.x = 639 + m_size.x;
		m_scale = (float)rand() / RAND_MAX+(1.0f/m_size.x);
		m_rotate = rand() % 360 - 180;

	}

	if (m_pos.y > 640 + m_size.y)
	{
		m_pos.x = (rand() % 1240 - 620);
		m_pos.y = -300 - m_size.x;
		m_scale = ((float)rand() / RAND_MAX)+ (1.0f / m_size.x);
		m_rotate = rand() % 360 - 180;

	}

	if (m_pos.y <- 640 - m_size.y)
	{
		m_pos.x = (rand() % 1240 - 620);
		m_pos.y = 300 + m_size.x;
		m_scale = (float)rand() / RAND_MAX+ (1.0f / m_size.x);
		m_rotate = rand() % 360 - 180;


	}
	m_rotatemat = Math::Matrix::CreateRotationZ(ToRadians(m_rotate));
	m_sizemat = Math::Matrix::CreateScale(m_scale);
	m_mat =
		m_sizemat *
		 m_rotatemat *
		Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
}

void C_Object::Draw(Math::Vector2 size)
{
	m_size = size;
	Math::Rectangle rect = { 0,0,(long)size.x,(long)size.y };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, rect, 1.0f);
}

void C_Object::Init()
{
	
	


}
