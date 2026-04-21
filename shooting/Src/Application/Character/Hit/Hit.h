#pragma once
class C_Hit
{
public:
	C_Hit();
	~C_Hit();
	void Enemy_EnemyHit();
	void Enemy_BulletHit();

	void Enemy_PlayerHit();	

private:

	const float PlayerInvincibleMaxTime = 120;
	float PlayerInvincibleTime = PlayerInvincibleMaxTime;

};


