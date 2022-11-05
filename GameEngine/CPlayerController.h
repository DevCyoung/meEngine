#pragma once
#include "CComponent.h"

class CZero;
class CAnimator;
//STARTVIM
//RETURVIM
enum class PLAYER_STATE
{
    IDLE                        =0x00000000,
    WALK                        =0x00000001,
    FALLING                     =0x00000002,
    DASH                        =0x00000004,
    JUMP                        =0x00000008,
    WALLSLIDE                   =0x00000010,
    LANDATTACK1                 =0x00000020,
    LANDATTACK2                 =0x00000040,
    LANDATTACK3                 =0x00000080,
    FALLINGATTACK               =0x00000100,
    WALLSLIDEATTACK             =0x00000200,
    LADDERATTACK                =0x00000400,
    LAND                        =0x00000800,
    HIT                         =0x00001000,
    TRJUMP                      =0x00020000,
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

    

    int         m_dir;
    Vector2     m_velocity;

    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

    void InputTick();
    void StateTick();

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
    CLONE(CPlayerController);

public:
    CPlayerController(CGameObject* obj); //기본생성자 안만듬
    CPlayerController(const CGameObject& _other);
    ~CPlayerController();
};

