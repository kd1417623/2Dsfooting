#pragma once
class C_Nois
{
public:
	C_Nois();
	~C_Nois();

	void Emit();
	void Update();
	void Init(Math::Vector2 LeftUp, Math::Vector2 _mBlockSize,Math::Vector2 EffectMaxPos);
	void Draw();


	void SetTex(KdTexture* _tex) { m_tex = _tex; }
private:


	float Rnd() { return rand() / (float)RAND_MAX; };


	Math::Rectangle BlockSize;
	KdTexture* m_tex;
	Math::Matrix m_mat;
	Math::Vector2 m_pos;

	Math::Vector2 m_LeftUp;
	Math::Vector2 m_RightDown;
	
	
	const float Timer = 6;
	float WateTime=Timer;
	

	Math::Color color;

	Math::Vector2 FirstBlockSize;
};

