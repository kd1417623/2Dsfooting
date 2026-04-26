#pragma once
class DamegeArea
{
public:
	DamegeArea();
	~DamegeArea();

	void Init();
	void Update();
	void Draw();

	void Smit(Math::Vector2 pos,float life,float size);


private:
	float m_size;
	Math::Vector2 m_pos;

	float m_life;
	
	bool m_flg = false;

};

