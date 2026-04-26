#pragma once
#include"../CharacterBase.h"
class C_Bullet;
class C_Player:public C_Character
{
public:
	static const int BulletNum = 50;
	C_Bullet *m_bullet[BulletNum];
	C_Bullet* GetBullet(int num);
	C_Player();
	~C_Player();

	void Update() override;
	void Draw() override;
	void Init(float	 circlesize) override;
	void Action();
	void ImGuiUpdate();
	void BulletSetTex(KdTexture* tex);

	void Death() override {
		alive = false;
	}
	void Damage(float _damage) override { m_color = { 1,0,0,1 };
	HP -= _damage; 
	if (HP < 0) { HP = 0; }
	}
	int GetBulletNum() { return BulletNum; }

	void SetKillCount(float _KillCount) { KillCount = _KillCount; }
	float GetKillCount() { return KillCount; }
	Math::Vector2 GetScroll() { return scroll; }

private:
	Math::Vector2 movecount{};
	Math::Vector2 posMax{};
	float angle = 0.0f;
	float radius = 200.0f;
	Math::Vector2 center = { 0, 000 };
	POINT mousePos = {};
	float mouseangle=0.0f;


	float KillCount = 0;


	Math::Vector2 scroll = { 0,0 };

	float playeranimX=0;


	float OverHeat=0;
	const float OverHeatMax=100;
	bool OverHeatflg = false;
	Math::Color m_color = {1,1,1,1};

	bool AutoShot = false;
	float CloseEnemyAngle = 0;
};
