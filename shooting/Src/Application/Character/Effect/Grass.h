#pragma once
class Grass
{
public:
	Grass();
	~Grass();
	void Update(float movespeed);
	void Init();
	void settex(KdTexture* tex) { m_pTex = tex; }
	void Emit(const Math::Vector2& pos);
	void Draw(Math::Color color)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.C_DrawTex(m_pTex, Math::Rectangle(0, 0, 32, 32), color);
	}
	float Rnd() { return rand() / (float)RAND_MAX; };

private:
	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	Math::Color m_color;
	Math::Matrix m_mat;
	Math::Vector2 m_scale;
	Math::Matrix m_scaleMat;
	KdTexture* m_pTex = nullptr;

	float cycle;
	Math::Vector2 m_scalespeed;

};


