#pragma once
#include"../CharacterBase.h"
#include"../Skill/Bullet.h"
class EnemyTurret : public C_Character
{
public:
	static const int BulletNum = 20;
	C_Bullet bullet[BulletNum];
	EnemyTurret();
	~EnemyTurret();

	void Update() override;
	void Draw() override;
	void Init(float	 circlesize) override;

	void SetBulletTex(KdTexture *tex) { for (auto& i : bullet) { i.SetTexture(tex); } }

	C_Bullet* GetBullet(int num) { return &bullet[num]; }
	int GetBulletNum() { return BulletNum; }


private:

};
