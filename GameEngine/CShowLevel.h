#pragma once
#include "CRockmanLevel.h"
class CShowLevel :
    public CRockmanLevel
{
public:
    // CLevel��(��) ���� ��ӵ�
    virtual void init() override;
    virtual void tick() override;

    // CLevel��(��) ���� ��ӵ�
    virtual void Enter() override;
    virtual void Exit() override;



public:
    CShowLevel();
    ~CShowLevel();
};

