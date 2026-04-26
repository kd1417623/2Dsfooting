#pragma once

class C_Background;
class C_Player;
class C_Enemy;
class C_Hit;
class C_Object;
class EnemyTurret;
class Scene
{
private:
	enum Gamescene
	{
		title,main, result,

	};
	static const int EnemyNum = 10;
	static const int TurretNum = 10;
	static const int WindowWIDTH = 1280;
	static const int WindowHEIGHT = 720;

	C_Player* player;

	std::shared_ptr<C_Enemy>enemy[EnemyNum];
	C_Hit *hit;
	EnemyTurret *m_turret[TurretNum];


	std::shared_ptr<C_Background>background=nullptr;
	std::shared_ptr<C_Object>backobj[2] = {nullptr,nullptr};

	Gamescene nowscene = title;
	// テクスチャ ・・・ 画像データ
	KdTexture charaTex;
	POINT mousePos;
	KdTexture playerTex;

	KdTexture bulletTex;
	KdTexture grassTex;

	KdTexture BackObjTex[2];
	KdTexture enemyTex;
	// 行列 ・・・ 座標などの情報
	Math::Matrix matrix;

	KdTexture TurretTex;



public:

	void Restart();
	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate(); 

	POINT getMousePos();


	C_Enemy* GetEnemy(int num) { return enemy[num].get(); }
	int GetEnemynum() { return EnemyNum; }

	C_Player* GetPlayer() { return player; }

	EnemyTurret* GetTurret(int num) { return m_turret[num]; }
	int GetTurretNum() { return TurretNum; }

	void AllEnemy_Kills();
private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
