#include"Hit.h"
#include"../../Scene.h"
C_Hit::C_Hit()
{
}

C_Hit::~C_Hit()
{
}

void C_Hit::Enemy_EnemyHit()
{
	for (int i = 0; i < SCENE.GetEnemynum(); i++)
	{
		for (int h = i+1; h < SCENE.GetEnemynum(); h++)
		{
			if (i==h)
			{
				continue;
			}
			C_Enemy* enemy1 = SCENE.GetEnemy(i);
			C_Enemy* enemy2 = SCENE.GetEnemy(h);
			Math::Vector2 enemy1move = enemy1->GetMove();
			Math::Vector2 enemy2move = enemy2->GetMove();
			Math::Vector2 enemy1pos = enemy1->GetPos();
			Math::Vector2 enemy2pos = enemy2->GetPos();
			Math::Vector2 enemy1fpos = enemy1->GetPos() + enemy1move;
			Math::Vector2 enemy2fpos = enemy2->GetPos() + enemy2move;

			//const float nextenemy1Top = enemy1fpos.y + 32;
			//const float nextenemy1Bottom = enemy1fpos.y - 32;
			//const float nextenemy1Left = enemy1fpos.x - 32;
			//const float nextenemy1Right = enemy1fpos.x + 32;

			//const float nextenemy2Top = enemy2fpos.y + 32;
			//const float nextenemy2Bottom = enemy2fpos.y - 32;
			//const float nextenemy2Left = enemy2fpos.x - 32;
			//const float nextenemy2Right = enemy2fpos.x + 32;

			//const float enemy2Top = enemy2pos.y + 32;
			//const float enemy2Bottom = enemy2pos.y - 32;
			//const float enemy2Left = enemy2pos.x - 32;
			//const float enemy2Right = enemy2pos.x + 32;

			//const float enemy1Top = enemy1pos.y + 32;
			//const float enemy1Bottom = enemy1pos.y - 32;
			//const float enemy1Left = enemy1pos.x - 32;
			//const float enemy1Right = enemy1pos.x + 32;



			float dx = enemy1pos.x - enemy2pos.x;
			float dy = enemy1pos.y - enemy2pos.y;
			float dist = sqrtf(dx * dx + dy * dy);

			float minDist = 64.0f;//最低距離

			if (dist < minDist && dist > 0.0f)
			{
				float push = (minDist - dist) * 0.5f;//押し出す距離(最低距離-直接距離) / 2(両方に押し出すため)

				dx /= dist;//x距離 / 直接距離
				dy /= dist;//y距離/直接距離

				enemy1->SetPos(enemy1pos + Math::Vector2(dx * push, dy * push));
				enemy2->SetPos(enemy2pos - Math::Vector2(dx * push, dy * push));
			}




		}

	}

}

void C_Hit::Enemy_BulletHit()
{
	for (int i = 0; i < SCENE.GetPlayer()->GetBulletNum(); i++)
	{
		for (int h = 0; h <SCENE.GetEnemynum(); h++)
		{
			C_Enemy* enemy = SCENE.GetEnemy(h);
			C_Bullet* bullet = SCENE.GetPlayerBullet(i);
			Math::Vector2 enemyPos = enemy->GetPos();
			Math::Vector2 bulletPos = bullet->GetPos();
		

			float dx = enemyPos.x - bulletPos.x;
			float dy = enemyPos.y - bulletPos.y;
			float dist = sqrtf(dx * dx + dy * dy);

			float minDist = 32.0f;//最低距離

			if (dist < minDist && dist > 0.0f)
			{
				float push = (minDist - dist);


				dx /= dist;//x距離/直接距離(現在の角度に変換)
				dy /= dist;//y距離/直接距離(現在の角度に変換)
				enemy->SetPos(enemyPos + Math::Vector2(dx * push, dy * push));
				enemy->Damage(10);
				bullet->Setshot(false);
			}



		}

	}

}

void C_Hit::Enemy_PlayerHit()
{

	if (SCENE.GetPlayer()->GetAlive())
	{

		PlayerInvincibleTime--;
		for (int i = 0; i < SCENE.GetEnemynum(); i++)
		{
		




				C_Enemy* enemy = SCENE.GetEnemy(i);
				C_Player* player = SCENE.GetPlayer();
				Math::Vector2 enemyPos = enemy->GetPos();
				Math::Vector2 playerPos = player->GetPos();
				if (!enemy->GetAlive())
				{
					continue;
				}

				float dx = enemyPos.x - playerPos.x;
				float dy = enemyPos.y - playerPos.y;
				float dist = sqrtf(dx * dx + dy * dy);

				float minDist = 64.0f;//最低距離

				if (dist < minDist && dist > 0.0f)
				{
					float push = (minDist - dist);


					dx /= dist;//x距離/直接距離(現在の角度に変換)
					dy /= dist;//y距離/直接距離(現在の角度に変換)
					enemy->SetPos(enemyPos + Math::Vector2(dx * push, dy * push));
					if (PlayerInvincibleTime <= 0)
					{
						PlayerInvincibleTime = 0;
					PlayerInvincibleTime = PlayerInvincibleMaxTime;
					player->Damage(10);
					//enemy->SetMove({ 0,0 });
				}

			}




		}
	}

}

