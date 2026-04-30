#include"../CharacterBase.h"
#include"EnemyTurret.h"
#include"../../Scene.h"
#include"../Player/Player.h"

#include"../../Scene/SceneBase.h"
EnemyTurret::EnemyTurret()
{
}

EnemyTurret::~EnemyTurret()
{
}

void EnemyTurret::Update() {
	bool	PlayerAlive = SCENE.GetNowScene()->GetPlayer()->GetAlive();
	if (!alive || !PlayerAlive)
	{
		if (PlayerAlive)
		{
			if (rand() % 5 > 3)
			{



				Reborn();
				Death_CoolDown = false;
			}
		}
		return;
	}
	if (HP <= 0)
	{

		alive = false;
		if (!Death_CoolDown)
		{
			SCENE.GetNowScene()->GetPlayer()->SetKillCount(SCENE.GetNowScene()->GetPlayer()->GetKillCount() + 1);
			Death_CoolDown = true;

		}
	}
	if (alive)
	{


		{
			Math::Vector2 playerpos = SCENE.GetNowScene()->GetPlayer()->GetPos();
			Math::Vector2 m_scroll = SCENE.GetNowScene()->GetPlayer()->GetScroll();
			float angle = atan2f(playerpos.y - (pos.y), playerpos.x - (pos.x));
			angle -= ToRadians(90);
			mat = Math::Matrix::CreateRotationZ(angle) *
				Math::Matrix::CreateTranslation(pos.x - m_scroll.x, pos.y - m_scroll.y, 0);
			for (auto& b : bullet)
			{
				if (!b.Shot(pos, Math::Vector2(cosf(angle + ToRadians(90)) * 10, sinf(angle + ToRadians(90)) * 10)))
				{
					break;
				}
			}
			for (auto& b : bullet)
			{
				b.Update();
			}
			if (HP <= 0)
			{
				alive = false;
			}
		}
	}
}
void EnemyTurret::Draw()
{
	if (alive)
	{


		for (auto& i : bullet) {
			i.Draw(true);
		}
		SHADER.m_spriteShader.SetMatrix(mat);
		SHADER.m_spriteShader.DrawTex(tex, Math::Rectangle{ 0,0,48,48 }, 1.0f);
	}
}

void EnemyTurret::Init(float circlesize)
{
	for (auto& i : bullet) { i.Init(); }
	pos = Math::Vector2(rand() % 3200 - 1600, 640);
	move = { 0,0 };

}

void EnemyTurret::Reborn()
{
	HP = maxHP;
	//PlayerAlive = true;
	alive = true;
	pos = Math::Vector2(rand() % 3200 - 1600, 360) + SCENE.GetNowScene()->GetPlayer()->GetScroll();

}
