#pragma once
#include "CLevel.h"
class CStartLevel :
    public CLevel
{
public:
    // CLevel��(��) ���� ��ӵ�
    virtual void init() override;
    virtual void tick() override;

    // CLevel��(��) ���� ��ӵ�
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CStartLevel();
    ~CStartLevel();
};

