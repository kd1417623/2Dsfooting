#pragma once
#include"../CharacterBase.h"
#include"Bullet.h"
class C_Player:public C_Character
{
public:
	static const int BulletNum = 30;
	C_Bullet m_bullet[BulletNum];
	C_Player();
	~C_Player();

	void Update() override;
	void Draw() override;
	void Init(float	 circlesize) override;
	void Action();
	void ImGuiUpdate();
	void BulletSetTex(KdTexture* tex);

	void Damage(float _damage) override { HP -= _damage; if (HP < 0) { HP = 0; } }
	int GetBulletNum() { return BulletNum; }
private:
	Math::Vector2 movecount;
	Math::Vector2 posMax;
	float angle = 0.0f;
	float radius = 200.0f;
	Math::Vector2 center = { 0, 000 };
	POINT mousePos;
	float mouseangle;




	float playeranimX=0;

};
