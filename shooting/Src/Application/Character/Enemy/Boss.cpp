#include "Boss.h"
#include "Src\Application\Scene.h"
#include"../../Scene/SceneBase.h"
#include"../Player/Player.h"
#include"../Effect/Glassval2.h"
#include"../Skill/Bullet.h"
C_BOSS::C_BOSS()
{
	HP = maxHP * 1000;

    for (auto& i : m_galass)
    {
        i = std::make_shared<Glassval2>();
	}
     for (auto& i : laserglass)
    {
        i = std::make_shared<Glassval2>();
	 }

	 for (auto& i : m_bullet)
     {
         i = std::make_shared<C_Bullet>();
     }
     Init(0);
     mat = Math::Matrix::CreateScale(WalpScale, 1.0f, 1.0f) * Math::Matrix::CreateRotationX(0.0f) * Math::Matrix::CreateTranslation(PosXCalc(pos).x, PosXCalc(pos).y, 0);

}

void C_BOSS::Init(float s)
{
    move = { 5, 0 };
    pos = { 0, 900 };
    atk2flg = false;

    atk2flg = atk2_charge = false;
    laserLength = 0.0f;
    LaserAlpha = 0.0f;

    for (int i = 0; i < bossglassnum; i++)
    {
        m_galass[i]->settex(bossgalasstex);
        laserglass[i]->settex(bossgalasstex);
    }
}

void C_BOSS::Update()
{
    if (HP<=0)
    {SCENE.SetClearFlag(true);
        return;
    }
    else
    {
		
	//	SCENE.ChengeScene(GameFase::result);
    }
    
	Math::Vector2 Scroll = SCENE.GetNowScene()->GetPlayer()->GetScroll();
    for (auto& i : m_galass)
    {
        i->Update();
    }
    for (auto& i : laserglass)
    {
        i->Update();
    }
    AtackDraw();

    UpdateMove();


    attackTimer--;

    if (!atk2flg&&!WalpAnimSwitch&&attackTimer<=0)
    {
     

            Atk2();
			attackTimer = attackInterval;

    }




    static int laser_animWait = 0; // フレームウェイトカウンタ

    if (atk2flg)
    {
        if (LaserVertical)
        {
            if (LaserStartPos.y< SCENE.GetWindowHEIGHT() / 2 + Scroll.y)
            {
            pos.y = (float)SCENE.GetWindowHEIGHT() / 2+Scroll.y;

            }
        }
        else
        {
            if (LaserStartPos.x < SCENE.GetWindowWIDTH() / 2 + Scroll.x)
            {

                pos.x = (float)SCENE.GetWindowWIDTH() / 2 + Scroll.x;
            }
                
        }
        laser_animWait+=3;
        if (laser_animWait >= laser_animationwait)
        {
            if (!WalpAnimSwitch)
            {
  laser_animation++;
            }
            if (laser_animation < 5)
            {
                laser_animationwait = 30;
                LaserAlpha = 0.2f;
            }
            else
            {
                laser_animationwait = 2;
                LaserAlpha = 1.0f;

                if (laser_animation == 17)
                {
                    for (auto& i : laserglass)
                    {
                        if (LaserVertical)
                        {
                            i->Emit(laserpos, LaserVertical);

                        }
                        else
                        {
                              i->Emit(laserpos,LaserVertical);

                        }
                    }
                }

            }
            if (laser_animation > 29)
            {
                laser_animation = 0;
                LaserVertical = !LaserVertical;

                atk2flg = false;
            }
            laser_animWait = 0;
        }
        if (laser_animation>=15&&laser_animation<=19)
        {
            LaserHitCheck();

        }
        //  }

        if (LaserVertical)
        {
            lasermat = 
              

                Math::Matrix::CreateScale(4.5f, 2.5f, 1.0f)*   Math::Matrix::CreateRotationZ(ToRadians(90)) *
                Math::Matrix::CreateTranslation(laserpos.x - SCENE.GetNowScene()->GetPlayer()->GetScroll().x, 0, 0);



        }
        else
        {
            lasermat =
            Math::Matrix::CreateScale(15.0f, 2.5f, 1.0f) * Math::Matrix::CreateRotationZ(ToRadians(0))*
            Math::Matrix::CreateTranslation(0, laserpos.y - SCENE.GetNowScene()->GetPlayer()->GetScroll().y, 0);

        }
    }


    mat =Math::Matrix::CreateScale(WalpScale,1.0f,1.0f)* Math::Matrix::CreateRotationZ(RotateAngle)*Math::Matrix::CreateTranslation(PosXCalc(pos).x, PosXCalc(pos).y, 0);
}

void C_BOSS::Draw()
{
    SHADER.m_spriteShader.SetMatrix(mat);
    SHADER.m_spriteShader.C_DrawTex(tex, { 0, 0, 176, 80 }, Color);
	Color = { 1,1,1,1 };
    AtackDraw();
    for (auto& i : m_galass)
    {
        i->Draw();
    }
    for (auto& i : laserglass)
    {
        i->Draw();
    }
}

void C_BOSS::AtackDraw()
{




    if (atk2flg)
    {
        SHADER.m_spriteShader.SetMatrix(lasermat);
        SHADER.m_spriteShader.DrawTex(laserTex, { 0,(int)laser_animation * 21,160,21 }, LaserAlpha);

    }
}


void C_BOSS::UpdateMove()
{
   
	float MoveSpeed = 5.0f;
    C_Player* player = SCENE.GetNowScene()-> GetPlayer();
    Math::Vector2 ppos = player->GetPos();


    Math::Vector2 EnemyVec;
    EnemyVec = ppos - pos;
	Math::Vector2 EnemyDist = EnemyVec;
  
    
   
    if (EnemyDist.Length() > 330)
    {
        EnemyVec.Normalize();
        move = EnemyVec * MoveSpeed;
    }
    else if (EnemyDist.Length() < 270)
    {
        EnemyVec.Normalize();
        move = EnemyVec * -MoveSpeed;
    }
    else
    {
        move = { 0,0 };
    }

    if (!atk2flg)
    {
pos += move;
    } 
    if (WalpAnimSwitch)
    {
        Walp(BossMoveTarget);

    }       

    
    

}


void C_BOSS::ImGUIUpdate()
{
	ImGui::Text("Boss HP: %f", HP);
}








Math::Vector2 C_BOSS::PosXCalc(Math::Vector2 pos)
{
    pos -= SCENE.GetNowScene()->GetPlayer()->GetScroll();
    return pos;

}


void C_BOSS::LaserHitCheck()
{
    Math::Vector2 playerPos = SCENE.GetNowScene()->GetPlayer()->GetPos();

    if (LaserVertical)
    {
        // 縦レーザー
        if (abs(playerPos.x - laserpos.x) < 90)
        {
            SCENE.GetNowScene()->GetPlayer()->Damage(10);
        }
    }
    else
    {
        // 横レーザー
        if (abs(playerPos.y - laserpos.y) < 90)
        {
            SCENE.GetNowScene()->GetPlayer()->Damage(10);
        }
    }
}
void C_BOSS::Walp(Math::Vector2 _pos)
{
    if (!WalpPop)
    {
        WalpScale -= 0.2;
        if (WalpScale<=0)
        {
			WalpScale = 0;
            WalpPop = true;
			pos = _pos;
        }
    }
    else
    {
        WalpScale += 0.2;
        if (WalpScale >= 1.0f)
        {
            WalpScale = 1.0f;

            WalpAnimSwitch = false;
            WalpPop = false;
         

            
		}
    }
}

void C_BOSS::Atk2()
{
    if (WalpAnimSwitch)
    {
        return;
    }
    C_Player* player = SCENE.GetNowScene()->GetPlayer();
    playerpos = player->GetPos();

    atk2flg = true;
    atk2_charge = true;
    atk2_timer = 0;

    laserLength = 0.0f;
    LaserAlpha = 0.0f;
    laser_animation = 0;
    
    WalpAnimSwitch = true;

     MoveTargetSet = true;

     
    if (LaserVertical)
    {
            laserpos.x = { player->GetPos().x+ rand() % 200 - 100 };
            laserpos.y = player->GetScroll().y;
		BossMoveTarget = { laserpos.x, player->GetScroll().y + 330 };
        RotateAngle = 0;
        LaserStartPos = BossMoveTarget;
     }
    else
	{
        RotateAngle = ToRadians(-90); 
		laserpos.x = player->GetScroll().x-150;
        laserpos.y = (player->GetPos().y)+rand() % 200 - 100;
       	BossMoveTarget = {player->GetScroll().x + 630, laserpos.y };
        LaserStartPos = BossMoveTarget;
    }


}




