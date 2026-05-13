#pragma once
#include"../CharacterBase.h"
class C_Bullet;
class Glassval2;
class C_BOSS : public C_Character

{
public:
    C_BOSS();
    ~C_BOSS() {}
    static const int bossglassnum = 100;

    std::shared_ptr<Glassval2> m_galass[bossglassnum * 2];
    std::shared_ptr<Glassval2> laserglass[bossglassnum];

	static const int BulletNum = 30;
	std::shared_ptr<C_Bullet> m_bullet[BulletNum];

    void DynamicDraw();

    void Init(float)override ;
    void Update() override;
    void Draw() override;
    void AtackDraw();
    void getplayerpos(Math::Vector2 pos) { playerpos = pos; };
    void setlasertex(KdTexture* texture) { laserTex = texture; };

    void UpdateMove();
    //void DrawCrop();
    void setgallastex(KdTexture* galasstex) { bossgalasstex = galasstex; }
    void ImGUIUpdate();


    Math::Vector2 PosXCalc(Math::Vector2 pos);

	bool GetLaserDir() { return LaserVertical; }
	float GetLaserThickness() { return deg/2; }

	void LaserHitCheck();

	void Damage(float _damage) override {
		Color = { 1,0,0,1 };
        HP -= _damage; if (HP < 0) { HP = 0; } }

    void Walp(Math::Vector2 pos);
private:
    void Atk2();

    int atk2_timer = 0;


    bool LaserVertical=false;
    float deg = 30;

    Math::Vector2 playerpos;


    Math::Matrix mat;

    KdTexture* laserTex;

    // 攻撃状態
    bool atk2flg = false;

    // 攻撃制御
    const int attackInterval = 120;
    int attackTimer = attackInterval;

    Math::Matrix lasermat;

    bool atk2_charge;     // チャージ中フラグ
    float laserLength;    // レーザー伸び具合(0.0～1.0)

    float laser_animation = 0.0f;

    Math::Vector2 laserpos;

    int laser_animationwait = 8;
    float LaserAlpha = 0.2f;

    KdTexture* bossgalasstex;


    Math::Vector2 MoveVec;


    float WalpScale = 1.0f;
	bool WalpAnimSwitch = false;

	bool WalpPop = false;

	Math::Vector2 BossMoveTarget;

    bool MoveTargetSet = false;

	bool WalpEv = false;

	float RotateAngle = 0.0f;

	Math::Vector2 LaserStartPos;

	Math::Color Color = { 1,1,1,1 };

};
