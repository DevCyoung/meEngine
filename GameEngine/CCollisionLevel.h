#pragma once
#include "CLevel.h"
class CLineCollider;
class CCollisionLevel :
    public CLevel
{
// CLevel��(��) ���� ��ӵ�
    virtual void init() override;
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    // CLevel��(��) ���� ��ӵ�
    virtual void Enter() override;
    virtual void Exit() override;

    void TestEventEnter(CLineCollider* _lineCol);
    void TestEventExit(CLineCollider* _lineCol);
    void TestEventOverlap(CLineCollider* _lineCol);

public:
    CCollisionLevel();
    ~CCollisionLevel();
};

