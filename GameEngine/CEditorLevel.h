#pragma once
#include "CLevel.h"
class CEditorLevel :
    public CLevel
{

public:
    // CLevel��(��) ���� ��ӵ�
    virtual void init() override;
    virtual void tick() override;
    //virtual void render(HDC _dc) override;
    virtual void Enter() override;
    virtual void Exit() override;



public:
    CEditorLevel();
    ~CEditorLevel();

};

