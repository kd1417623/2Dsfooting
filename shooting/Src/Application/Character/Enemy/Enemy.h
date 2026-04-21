#pragma once
#include"../CharacterBase.h"
#include"../Player/Bullet.h"
class C_Enemy:public C_Character
{
public:
	C_Enemy();
	~C_Enemy();
	C_Bullet bullet[20];
	void Update() override;
	void Draw() override;
	void Init(float	 circlesize) override;
	void Action();
	void SetTex(KdTexture* _tex) { tex = _tex; }

	void SetBulletTex(KdTexture* _tex) {
		for (int i = 0; i < 20; i++)
		{
			bullet[i].SetTexture(_tex);
		}
	}

	void Damage(float _damage) override { HP -= _damage; if (HP < 0) { HP = 0; } color = { 1, 0, 0, 1 }; }

	C_Bullet* GetBullet(int num) { return &bullet[num]; }


	void Reborn() {
		HP = maxHP;
		color = { 1,1,1,1 };
		//PlayerAlive = true;
		moveswitch = false;
		movecount = { 0,0 };
		alive = true;
		pos = Math::Vector2(rand() % 3200 - 1600, 360);
	}
	void Death() override {
		alive = false;
		color = { 1,1,1,0 };
	}
private:
	Math::Vector2 movecount;
	Math::Vector2 posMax;
	float angle = 0.0f;
	float radius = 400.0f;
	Math::Vector2 center = { 0, 0 };
	POINT mousePos;
	float mouseangle;
	bool moveswitch = false;
	float movespeed = 0.05f;

	float speed = 0;
	float pictangle;
	Math::Vector2 bulletmove={-20,-10};


	bool allshot = false;

	Math::Color color = { 1,1,1,1 };
	bool PlayerAlive = true;

};

