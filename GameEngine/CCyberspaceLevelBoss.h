#pragma once
#include "CRockmanLevel.h"
class CCyberspaceLevelBoss :
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
    CCyberspaceLevelBoss();
    ~CCyberspaceLevelBoss();
};

