#pragma once
class C_Bullet
{
public:
	C_Bullet();
	~C_Bullet();

	bool Shot( Math::Vector2& pos,  Math::Vector2& move);
	Math::Vector2 GetPos() const { return m_pos; }
	Math::Vector2 GetMove() const { return m_move; }
	void Update();
	void Init();
	void Draw(bool isRed);
	void SetTexture(KdTexture* tex) { m_tex = tex; }
	bool IsShot() const { return m_shot; }

	void SetFreeze(bool isFreeze) { freze = isFreeze; }


	void Setshot(bool isShot) { m_shot = isShot; }
private:
	bool m_shot;
	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	Math::Matrix m_mat;
	KdTexture* m_tex;


	bool freze = false;
};

