#pragma once
#include "CRockmanLevel.h"
class CCyberspaceLevel3 :
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
    CCyberspaceLevel3();
    ~CCyberspaceLevel3();
};

