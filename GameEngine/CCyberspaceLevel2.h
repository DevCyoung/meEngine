#pragma once
#include "CRockmanLevel.h"
class CCyberspaceLevel2 :
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
    CCyberspaceLevel2();
    ~CCyberspaceLevel2();
};

