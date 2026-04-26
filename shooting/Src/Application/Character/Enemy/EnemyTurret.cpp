#include"../CharacterBase.h"
#include"EnemyTurret.h"
#include"../../Scene.h"
#include"../Player/Player.h"
EnemyTurret::EnemyTurret()
{
}

EnemyTurret::~EnemyTurret()
{
}

void EnemyTurret::Update() {
	if (alive)
	{


		{
			Math::Vector2 playerpos = SCENE.GetPlayer()->GetPos();
			Math::Vector2 m_scroll = SCENE.GetPlayer()->GetScroll();
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
	pos = Math::Vector2(rand() % 3200 - 1600, circlesize);
	move = { 0,0 };

}
