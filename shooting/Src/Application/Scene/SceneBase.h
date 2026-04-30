#pragma once
class C_Background;
class C_Player;
class C_Enemy;
class C_Hit;
class C_Object;
class EnemyTurret;

class SceneBase
{
public:
	SceneBase() {
		AllNew();

		AllInit();
	};
	~SceneBase() {};

	virtual void Update() {};
	virtual void PreUpdate() {};
	virtual void Draw() {};
	virtual void Init() {};

	void AllNew();

	void Restart();
	C_Enemy* GetEnemy(int num) { return enemy[num].get(); }
	int GetEnemynum() { return EnemyNum; }

	C_Player* GetPlayer() { return player.get(); }

	EnemyTurret* GetTurret(int num) { return m_turret[num].get(); }
	int GetTurretNum() { return TurretNum; }

	void AllEnemy_Kills();


	C_Hit* GetHit() { return hit.get(); }

	void AllInit();
protected:

	static const int EnemyNum = 10;
	static const int TurretNum = 10;


	std::shared_ptr<C_Player> player;

	std::shared_ptr<C_Enemy>enemy[EnemyNum];
	std::shared_ptr<C_Hit> hit;
	std::shared_ptr<EnemyTurret> m_turret[TurretNum];


	std::shared_ptr<C_Background>background = nullptr;
	std::shared_ptr<C_Object>backobj[2] = { nullptr,nullptr };

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





};

