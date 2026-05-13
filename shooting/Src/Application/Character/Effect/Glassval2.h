#pragma once
class Glassval2
{
public:
	Glassval2();
	~Glassval2();
	void Update();
	void Init();
	void settex(KdTexture* tex) { m_pTex = tex; }
	void Emit(Math::Vector2 pos, bool vartical);
	void Draw()
	{
		D3D.SetBlendState(BlendMode::Add);

		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.C_DrawTex(m_pTex, Math::Rectangle(0, 0, 32, 32), m_color);
		D3D.SetBlendState(BlendMode::Alpha);

	}
	float Rnd() { return rand() / (float)RAND_MAX; };


	Math::Vector2 GetPos();


	bool GetFirst() { return m_first; }
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


	bool m_vartical;
	bool m_screenout=false;


	bool m_first = false;
};

