#pragma once
class C_Object
{
public:
	C_Object() {
		//m_pos = { 999,999 };
		m_scale = 0;
	};
	~C_Object() {};
	void SetObjectTex(KdTexture* tex) { m_tex = tex; }


	void Update();
	void Draw(Math::Vector2 size);
	void Init();

	void SetTex(KdTexture *tex) { m_tex = tex; }
	


private:


	KdTexture *m_tex=nullptr;
	Math::Matrix m_mat;
	Math::Vector2 m_pos;
	Math::Vector2 m_playermove;
	Math::Vector2 m_size;
	Math::Matrix m_sizemat;
	Math::Matrix m_rotatemat;

	float m_rotate;
	float m_scale;
	static const int WindowWIDTH = 1280;
	static const int WindowHEIGHT = 720;

	static const int FadeMargin = 100;

};