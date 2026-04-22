#pragma once
#include"../CharacterBase.h"
#include"../Player/Bullet.h"
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

private:

};
