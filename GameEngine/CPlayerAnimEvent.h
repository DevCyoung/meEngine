#pragma once
#include "CComponent.h"

class CAnimator;
class CZero;


class CPlayerAnimEvent :
    public CComponent
{
public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

private:
    CAnimator*  m_animztor;
    CZero*      m_zero;

public:
    UINT                m_attackCount;




public:
    CLONE(CPlayerAnimEvent);


private:
    void JumpReady();
    void WalkReady();
    void FallingReady();
    void Falling();

    void WalkFinish();
    void WallJumpReady();
    void WallSlideReady();
    void LandDashReady();
    void FireReady();
    void DashFinish();
    void ReturnReady();

    void Attack1();
    void Attack2();
    void Attack3();

    void Attack1Reday();
    void Attack2Reday();
    void Attack3Reday();

    void DamagedReady();

    void Idle();

    void Enter();

    void WallSlideEffect();
    void JumpReadyEffect();
    void LandDashReadyEffect();

    void GoodEffect();
    void GoodReturn();
public:
    CPlayerAnimEvent(CGameObject* obj); //기본생성자 안만듬
    CPlayerAnimEvent(const CGameObject& _other);
    ~CPlayerAnimEvent();
};

