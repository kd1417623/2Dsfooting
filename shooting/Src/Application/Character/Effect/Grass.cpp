#include"Grass.h"

Grass::Grass()
{
}
Grass::~Grass()
{
}
void Grass::Init()
{
    m_pos = { 0.0f,0.0f };
    m_move = { 0.0f,0.0f };
    m_color = { 1.0f,1.0f,1.0f,0 };
    m_scale = { 0.0f,0.0f };
}
void Grass::Update(float movespeed)
{
    cycle += Rnd() * 5;

    m_pos += m_move;

    m_scale.y -= 0.01f;
    m_scale.x -= 0.01f;
    if (m_scale.x < 0.0f) m_scale = { 0.0f, 0.0f };
    if (cycle == 180)
    {
        m_color = { 1.0f,1.0f,1.0f,1.0f };
    }
    else
    {
        m_color = { 1.0f,1.0f,1.0f,0.5 };

    }
    // 行列更新
    m_mat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(cycle)) *
        Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1.0f) *
        Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);

}
void Grass::Emit(const Math::Vector2& pos)
{
    m_color = { 1.0f,1.0f,1.0f,Rnd() };
    m_scale = { Rnd() * 1.5f,Rnd() * 1.5f };
    m_pos = pos;
    m_move = { Rnd() * 10 - 5,Rnd() * 10 - 5 };
    m_scalespeed = { Rnd() * 0.1f + 0.05f,Rnd() * 0.1f + 0.05f };

    cycle = Rnd() * 360;


}

