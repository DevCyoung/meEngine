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
    // CLevel��(��) ���� ��ӵ�
    CSound* m_titleBackGround;

    virtual void init() override;
    virtual void tick() override;

    // CLevel��(��) ���� ��ӵ�
    virtual void Enter() override;
    virtual void Exit() override;
    
    
    
public:
    CTitleLevel();
    ~CTitleLevel();
};

