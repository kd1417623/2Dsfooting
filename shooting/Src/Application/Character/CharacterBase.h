#pragma once
class C_Character
{
public:
	C_Character();
	~C_Character();

	void SetTex(KdTexture* _tex) { tex = _tex; }

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Init(float	 circlesize) = 0;


	Math::Vector2 GetPos() { return pos; }
	Math::Vector2 GetMove() { return move; }

	void SetPos(Math::Vector2 spos) { pos = spos; };
	void  SetMove(Math::Vector2 smove) { move = smove; };

	void SetAlive(bool _alive) { alive = _alive; }

	void SetHP(float _HP) { HP = _HP; }
	virtual void Damage(float _damage) { }

	bool GetAlive() { return alive; }

	float GetHp() { return HP; }

	virtual void Death() {};

private:


protected:
	Math::Vector2 pos;
	Math::Vector2 move;
	Math::Matrix mat;
	KdTexture* tex;

	bool alive = true;

	float HP = 100;
	const float maxHP = 100;

};

