#include"Enemy.h"
#include"../../Scene.h"
#include"../../Character/Player/Player.h"
#include"../Effect/Grass.h"
#include"../../Scene/SceneBase.h"
#include"../Skill/DamegeArea.h"
C_Enemy::C_Enemy()
{
	for (auto& g : grass)
	{
		g = new Grass();

	}
	d_a = new DamegeArea;
	Init(100);

}

C_Enemy::~C_Enemy()
{
	for (auto& g : grass)
	{
		delete g;
	}
}

void C_Enemy::Update()
{
	for (auto& g : grass)
	{
		g->Update(0);
	}
	if (PlayerAlive)
	{
		pos += move;

		if (HP <= 0&&alive)
		{
			d_a->Smit(pos, 1, 50);

			alive = false;
			for (auto& g : grass)
			{
				g->Emit(pos);
			}
			if (!Death_CoolDown)
			{
				SCENE.GetNowScene()->GetPlayer()->SetKillCount(SCENE.GetNowScene()->GetPlayer()->GetKillCount() + 1);

				SCENE.SetScore(SCENE.GetScore() + 100 * SCENE.GetComboCount());


				SCENE.ComboReset();
				Death_CoolDown = true;

			}
		}

	}

	mat = Math::Matrix::CreateScale(2.5f, 2.5f, 1.0f) * Math::Matrix::CreateRotationZ(pictangle) *
		Math::Matrix::CreateTranslation(pos.x - PlayerScroll.x, pos.y - PlayerScroll.y, 0);

	d_a->Update();

}

void C_Enemy::Draw()
{

	d_a->Draw();

	D3D.SetBlendState(BlendMode::Add);

	for (auto& g : grass)
	{
		g->Draw(Math::Color{ 0,0.5f,0.5f,1 });
	}
	D3D.SetBlendState(BlendMode::Alpha);

	if (!alive)
	{
		return;
	}
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.C_DrawTex(tex, Math::Rectangle{ 0,0,64,64 }, color);
	color = { 1,1,1,1 };
}

void C_Enemy::Init(float circlesize)
{
	radius = circlesize;

	pos = Math::Vector2(rand() % 3200 - 1600, 400);
	move = { 0,0 };
	movecount = { 0,0 };
	posMax = { radius,radius };
	angle = (float)(rand() % 360) * (3.141592f / 180.0f);
	center = { 0.0f, 0.0f };
	speed = rand() % 3 + 5;
	//speed = 5;

	Death_CoolDown = false;

}

void C_Enemy::Action()
{

	PlayerScroll = SCENE.GetNowScene()->GetPlayer()->GetScroll();
	PlayerAlive = SCENE.GetNowScene()->GetPlayer()->GetAlive();

	if (abs(Math::Vector2{ SCENE.GetNowScene()->GetPlayer()->GetPos() - pos }.x) > SCENE.GetWindowWIDTH()
		|| abs(Math::Vector2{ SCENE.GetNowScene()->GetPlayer()->GetPos() - pos }.y) > SCENE.GetWindowHEIGHT())
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

	if (alive)
	{
		Math::Vector2 PlayerPos = SCENE.GetNowScene()->GetPlayer()->GetPos();
		Math::Vector2 EnemyVec;
		EnemyVec = PlayerPos - pos;
		pictangle = atan2f(
			EnemyVec.y,
			EnemyVec.x
		);
		pictangle -= ToRadians(90);
		EnemyVec.Normalize();
		move = Math::Vector2(EnemyVec * speed);


	}

}

void C_Enemy::Reborn()
{
	if (SCENE.GetNowScene()->GetBossBattle())
	{
		return;
	}

	int WindowWIDTH = SCENE.GetWindowWIDTH();

	HP = maxHP;
	color = { 1,1,1,1 };
	//PlayerAlive = true;
	moveswitch = false;
	movecount = { 0,0 };
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

void C_Enemy::SetGrassTex(KdTexture* _tex)
{
	for (int i = 0; i < 20; i++)
	{
		grass[i]->settex(_tex);
	}
}
