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


			
private:

	Math::Matrix mat;
	KdTexture* backtex;
	Math::Vector2 PlayerScroll;
};

