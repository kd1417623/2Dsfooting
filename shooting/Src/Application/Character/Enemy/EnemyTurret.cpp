#include"../CharacterBase.h"
#include"EnemyTurret.h"
#include"../../Scene.h"
#include"../Player/Player.h"
#include"../Effect/Grass.h"
#include"../../Scene/SceneBase.h"
EnemyTurret::EnemyTurret()
{
	for (auto& g : grass) {

		g = std::make_shared<Grass>();
		g->Init();
	}
}

EnemyTurret::~EnemyTurret()
{
}

void EnemyTurret::Update() {
	for (auto& g : grass)
	{
		g->Update(0.5f);
	}
	bool	PlayerAlive = SCENE.GetNowScene()->GetPlayer()->GetAlive();
	if (Math::Vector2{ SCENE.GetNowScene()->GetPlayer()->GetPos()- pos  }.x > SCENE.GetWindowWIDTH()*2
		|| Math::Vector2{ SCENE.GetNowScene()->GetPlayer()->GetPos()- pos  }.y > SCENE.GetWindowHEIGHT()*2)
	{
		Reborn();

	}
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
			SCENE.ComboReset();
			for (auto& g : grass)
			{
				g->Emit(pos);
			}
			SCENE.SetScore(SCENE.GetScore() + (100*SCENE.GetComboCount()));
			Death_CoolDown = true;

		}
	}
	if (alive)
	{


		{
			Math::Vector2 playerpos = SCENE.GetNowScene()->GetPlayer()->GetPos();
			Math::Vector2 m_scroll = SCENE.GetNowScene()->GetPlayer()->GetScroll();
			AimVec = { playerpos - pos };
			float angle = atan2f(playerpos.y - (pos.y), playerpos.x - (pos.x));
			angle -= ToRadians(90);
			mat = Math::Matrix::CreateRotationZ(angle) *
				Math::Matrix::CreateTranslation(pos.x - m_scroll.x, pos.y - m_scroll.y, 0);
			for (auto& b : bullet)
			{
				Math::Vector2 ShotMove = AimVec;
				ShotMove.Normalize();
				if (!b.Shot(pos, ShotMove * 10))
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

	for (auto& g : grass)
	{
		g->Draw(Math::Color{ 0,0.5f,0.5f,1 });
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

	int WindowWIDTH = SCENE.GetWindowWIDTH();
	Math::Vector2 PlayerScroll = SCENE.GetNowScene()->GetPlayer()->GetScroll();
	HP = maxHP;
	alive = true;
	if (rand() % 100 > 50)
	{
		pos = Math::Vector2(rand() % WindowWIDTH - (WindowWIDTH / 2), 400) + PlayerScroll;

	}
	else
	{
		pos = Math::Vector2(rand() % WindowWIDTH - (WindowWIDTH / 2), -400) + PlayerScroll;
	}
}

void EnemyTurret::GrassSetTex(KdTexture* _tex)
{
	for (auto& g : grass) { g->settex(_tex); }
}
