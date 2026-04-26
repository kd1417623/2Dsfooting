#pragma once
class C_Hit
{
public:
	C_Hit();
	~C_Hit();
	void Enemy_EnemyHit();
	void Enemy_BulletHit();

	void Enemy_PlayerHit();	

	void Turret_playerHit();
	void Turret_BulletHit();



	Math::Vector2 DisCompare();//プレイヤーに近い方の座標を返す


private:

	const float PlayerInvincibleMaxTime = 60;
	float PlayerInvincibleTime = PlayerInvincibleMaxTime;

	void CheckClose(Math::Vector2& pos, Math::Vector2& playerPos,
		float& closeDist, Math::Vector2& returnPos)
	{
		float dist = SquaredDist(pos, playerPos);

		if (dist < closeDist)
		{
			closeDist = dist;
			returnPos = pos;
		}
	}

	float SquaredDist(Math::Vector2 pos1, Math::Vector2 pos2)
	{
		float dx = pos1.x - pos2.x;
		float dy = pos1.y - pos2.y;
		float dist = dx * dx + dy * dy;

		return dist;
	}

};


