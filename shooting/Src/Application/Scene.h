#pragma once
#include"Character/Player/Player.h"
#include"Character/Enemy/Enemy.h"
#include"Character/Hit/Hit.h"
class Scene
{
private:
	enum Gamescene
	{
		title,main, result,

	};
	static const int EnemyNum = 10;
	static const int WindowWIDTH = 1280;
	static const int WindowHEIGHT = 720;

	C_Player player;
	C_Enemy enemy[EnemyNum];
	C_Hit hit;


	int nowscene = title;
	// テクスチャ ・・・ 画像データ
	KdTexture charaTex;
	POINT mousePos;
	KdTexture playerTex;

	KdTexture bulletTex;


	KdTexture enemyTex;
	// 行列 ・・・ 座標などの情報
	Math::Matrix matrix;

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


	Math::Vector2 getPlayerPos() { return player.GetPos(); }
	C_Enemy* GetEnemy(int num) { return &enemy[num]; }
	int GetEnemynum() { return EnemyNum; }

	C_Player* GetPlayer() { return &player; }
	


	C_Bullet* GetPlayerBullet(int num) { return &player.m_bullet[num]; }
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
