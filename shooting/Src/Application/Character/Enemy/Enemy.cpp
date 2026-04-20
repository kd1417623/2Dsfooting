#include"Enemy.h"
#include"../../Scene.h"
C_Enemy::C_Enemy()
{
}

C_Enemy::~C_Enemy()
{
}

void C_Enemy::Update()
{
	if (PlayerAlive)
	{


		if (HP <= 0)
		{
			alive = false;
		}
		for (auto& b : bullet)
		{
			b.Update();

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
	if (!alive)
	{
		return;
	}
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.C_DrawTex(tex, Math::Rectangle{ 0,0,64,64 }, color);
	color = { 1,1,1,1 };
	for (auto& b : bullet)
	{
		b.Draw(true);
	}
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
		SCENE.getPlayerPos().y - pos.y,
		SCENE.getPlayerPos().x - pos.x
	);
	pictangle -= ToRadians(90);

	move = Math::Vector2(cosf(pictangle + ToRadians(90)) * speed, sinf(pictangle + ToRadians(90)) * speed);

	for (auto& b : bullet)
	{
	
			if (!b.Shot(Math::Vector2{ 0,640 }, bulletmove))
			{		

				bulletmove.x += 1;
			}
		
	
	}
	if (bulletmove.x>15)
	{
		bulletmove.x = -10;

	}
	
}