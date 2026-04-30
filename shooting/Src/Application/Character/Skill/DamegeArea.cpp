#include"DamegeArea.h"
#include"../../Scene.h"
#include"../Player/Player.h"
#include".././../Scene/SceneBase.h"
DamegeArea::DamegeArea()
{
}

DamegeArea::~DamegeArea()
{
}

void DamegeArea::Init()
{
}

void DamegeArea::Update()
{
	m_size--;
	m_life-=0.01;
	if (m_size<=0||m_life<=0)
	{
		m_flg = false;
	}
}

void DamegeArea::Draw()
{
	Math::Vector2 scroll = SCENE.GetNowScene()->GetPlayer()->GetScroll();
	if (m_flg)
	{

	Math::Color color = { 1,1,1,m_life };
	Math::Matrix mat= Math::Matrix::CreateTranslation({ 0,0,0 });
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawCircle((int)m_pos.x-scroll.x, (int)m_pos.y-scroll.y,m_size, &color,true);
	}
}

void DamegeArea::Smit(Math::Vector2 pos, float life, float size)
{
	if (!m_flg)
	{
		m_pos = pos;
		m_life = life;
		m_size = size;
		m_flg = true;
	}
}
