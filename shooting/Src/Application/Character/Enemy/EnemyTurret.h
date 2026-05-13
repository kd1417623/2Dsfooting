#pragma once
#include"../CharacterBase.h"
#include"../Skill/Bullet.h"
class Grass;

class EnemyTurret : public C_Character
{
public:
	static const int BulletNum = 20;
	C_Bullet bullet[BulletNum];
	static const int GrassNum = 20;
	std::shared_ptr<Grass> grass[GrassNum];
	EnemyTurret();
	~EnemyTurret();

	void Update() override;
	void Draw() override;
	void Init(float	 circlesize) override;
	void Damage(float _damage) override { HP -= _damage; if (HP < 0) { HP = 0; }}

	void SetBulletTex(KdTexture *tex) { for (auto& i : bullet) { i.SetTexture(tex); } }

	C_Bullet* GetBullet(int num) { return &bullet[num]; }
	int GetBulletNum() { return BulletNum; }
	void Reborn();


	void GrassSetTex(KdTexture* _tex);
private:
	bool Death_CoolDown;

	Math::Vector2 AimVec;
};
