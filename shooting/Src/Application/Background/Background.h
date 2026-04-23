#pragma once

class C_Background
{
public:
	C_Background();
	~C_Background();
	void Update();
	void Draw();
	void Init();

	void SetBackTex(KdTexture* tex) { backtex = tex; }
	void SetObjectTex(KdTexture* tex) { objecttex = tex; }
private:

	static const int objectnum = 10;
	Math::Matrix mat;
	KdTexture* backtex;
	KdTexture  *objecttex;
	Math::Matrix objmat[objectnum];
	Math::Vector2 objpos[objectnum];
	Math::Vector2 objmove[objectnum];
	Math::Vector2 PlayerScroll;
};

