#pragma once
#include "CRockmanLevel.h"
#include "CSound.h"

class CTexture;

class CTitleLevel :
    public CRockmanLevel
{
public:
    //
    //CTexture*
    //titlebackground.bmp
    // CLevel을(를) 통해 상속됨
    CSound* m_titleBackGround;

    virtual void init() override;
    virtual void tick() override;

    // CLevel을(를) 통해 상속됨
    virtual void Enter() override;
    virtual void Exit() override;
    
    
    
public:
    CTitleLevel();
    ~CTitleLevel();
};

