#include"Nois.h"

C_Nois::C_Nois()
{
}

C_Nois::~C_Nois()
{
}

void C_Nois::Emit()
{
}

void C_Nois::Update()
{
	if (WateTime <= 0)
	{


		if (rand() % 100 > 50)
		{
			BlockSize = { 0,0,(long)(Rnd()*FirstBlockSize.x),(long)(Rnd()*FirstBlockSize.y) };



			m_pos.x = rand() % (int)(m_RightDown.x - m_LeftUp.x) + (int)m_LeftUp.x;
			m_pos.y = rand() % (int)(m_RightDown.y - m_LeftUp.y) + (int)m_LeftUp.y;
		}
		WateTime = Rnd()*Timer;
	}
	else
	{
		WateTime--;

	}

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);


}

void C_Nois::Init(Math::Vector2 LeftUp, Math::Vector2 _mBlockSize, Math::Vector2 _RightDown)
{
	color = { 1.0f,1.0f,1.0f,Rnd()+0.5f};

	m_LeftUp = LeftUp;
	m_RightDown = _RightDown;
	BlockSize = { 0,0,(long)_mBlockSize.x,(long)_mBlockSize.y };
	FirstBlockSize = _mBlockSize;
}

void C_Nois::Draw()
{

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.C_DrawTex(m_tex, BlockSize, color);
}
