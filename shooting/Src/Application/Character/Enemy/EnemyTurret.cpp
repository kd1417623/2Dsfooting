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

void EnemyTurret::Update()

{Math::Vector2 playerpos = SCENE.GetPlayer()->GetPos();
	float angle = atan2f(playerpos.y - pos.y, playerpos.x - pos.x);
	angle -= ToRadians(90);
	mat = Math::Matrix::CreateRotationZ(angle) *
		Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
	for (auto& b : bullet)
	{
		b.Shot(pos, Math::Vector2(cosf(angle + ToRadians(90)) * 10, sinf(angle + ToRadians(90)) * 10));
		b.Update();
	}
}

void EnemyTurret::Draw()
{
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(tex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
}

void EnemyTurret::Init(float circlesize)
{
	pos = Math::Vector2(rand() % 3200 - 1600, circlesize);
	move = { 0,0 };

}
