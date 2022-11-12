#pragma once
#include "CComponent.h"

#define DASH_FRAME_SIZE 12

#define REDZEROCOLOR   0xffE90100
#define BLACKZEROCOLOR 0xff5000A0

#define BACKGROUNDCOLOR 0X00ff00ff    
class CZero;
class CAnimator;
//STARTVIM
//RETURVIM

struct tDashFrame
{
    tAnimFrm    frame;
    Vector2     pos;
    float       duration;
};

class CPlayerController :
    public CComponent
{
public:

    CZero*           m_zero;
    CAnimator*       m_animator;
    PLAYER_STATE     m_state;

    float       m_moveScale;
    float       m_fallingMoveScale;
    float       m_dashMoveScale;
    float       m_jumpScale;

    float       m_curdashScale;
    
    float       m_curFallingMove;


    //attackdelay

    float       m_attackDelay;
    float       m_fallingAttackDelay;
    float       m_specialDelay;
    float       m_jumpTrX;

    int         m_dir;
    Vector2     m_velocity;

    bool        m_isActable;


    vector<tDashFrame>  m_arrDashFrame;
    UINT                m_dashFrameIdx;
    float               m_dashFrameDelay;

    //Hit
    Vector2             m_hitDir;
    float               m_hitDelay;

    virtual void tick() override;
    void flip_tick();
    virtual void final_tick() override;
    
    virtual void render(HDC _dc) override;

    void InputTick();
    void StateTick();


    void DashFrame();
    float    m_attackDealy;

private:
    void Idle();
    void Walk();
    void LANDDASH();
    void Jump();
    void Falling();
    void LandAttack1();
    void LandAttack2();
    void LandAttack3();

    void FallingAttack();
    void WallSlide();
    void WallSlideAttack();

    void Move();

public:
    void SetState(PLAYER_STATE state) { m_state = state; }
    PLAYER_STATE GetState() { return m_state; }

public:
    CLONE(CPlayerController);

public:
    CPlayerController(CGameObject* obj); //기본생성자 안만듬
    CPlayerController(const CGameObject& _other);
    ~CPlayerController();
};

