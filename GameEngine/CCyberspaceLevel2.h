#pragma once
#include "CRockmanLevel.h"
class CCyberspaceLevel2 :
    public CRockmanLevel
{
public:
    // CLevel을(를) 통해 상속됨
    virtual void init() override;
    virtual void tick() override;

    // CLevel을(를) 통해 상속됨
    virtual void Enter() override;
    virtual void Exit() override;



public:
    CCyberspaceLevel2();
    ~CCyberspaceLevel2();
};

