#include"Enemy.h"
#include"../../Scene.h"
#include"../../Character/Player/Player.h"
#include"../Effect/Grass.h"
C_Enemy::C_Enemy()
{
	for (auto& g : grass)
	{
		g = new Grass();
		
	}
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


		if (HP <= 0)
		{
			alive = false;
			for (auto& g : grass)
			{
				g->Emit(pos);                                 
			}
			SCENE.GetPlayer()->SetKillCount(SCENE.GetPlayer()->GetKillCount() + 1);
		}

		center += move;
		// move = { 0,0 };
		//angle += movespeed;
		//pos.x = center.x + cosf(angle) * radius;
		//pos.y = center.y + sinf(angle) * radius;
		pos += move;
	}
	mat = Math::Matrix::CreateRotationZ(pictangle) *
		Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
}

void C_Enemy::Draw()
{
	D3D.SetBlendState(BlendMode::Add);

	for(auto &g:grass)
	{
		g->Draw(Math::Color{0,1,0,1});
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

	pos = Math::Vector2(rand()%3200-1600, radius);
	move = { 0,0 };
	movecount = { 0,0 };
	posMax = { radius,radius };
	angle = (float)(rand() % 360) * (3.141592f / 180.0f);
	center = { 0.0f, 0.0f };
	//movespeed = rand() %  5 + 1;
	movespeed = 5;
	speed = (float)(rand() % 19 + 1);
}

void C_Enemy::Action()
{
	PlayerAlive = SCENE.GetPlayer()->GetAlive();
	if (!alive||!PlayerAlive)
	{
		if (PlayerAlive)
		{
			if (rand()%5>3)
			{
				Reborn();
			}
		}
		return;
	}

	//if (moveswitch)
	//{
	//	if (radius<1)
	//	{
	//		moveswitch = false;
	//	}
	//	else
	//	{
	//		radius-=5;
	//	}
	//}
	//else
	//{
	//	if (radius>500)
	//	{
	//		moveswitch = true;
	//	}
	//	else
	//	{
	//		radius+=5;
	//	}
	//}
	pictangle = atan2f(
		SCENE.GetPlayer()->GetPos().y - pos.y,
		SCENE.GetPlayer()->GetPos().x - pos.x
	);
	pictangle -= ToRadians(90);

	move = Math::Vector2(cosf(pictangle + ToRadians(90)) * speed, sinf(pictangle + ToRadians(90)) * speed);


	
}

void C_Enemy::SetGrassTex(KdTexture* _tex)
{
	for (int i = 0; i < 20; i++)
	{
		grass[i]->settex(_tex);
	}
}
