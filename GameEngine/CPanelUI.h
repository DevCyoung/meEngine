#pragma once
#include "CUI.h"
class CPanelUI :
    public CUI
{
    //�е����������ش�. ����μ����Ұ�

private:
    Vector2 m_vLeftRightPadding;
    Vector2 m_vTopBottomPadding;
    Vector2 m_vInnerPadding;


    Vector2 m_vPressedPos;


public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void MouseLbtnDown() override;



public:
    CLONE(CPanelUI);



public:
    CPanelUI();
    ~CPanelUI();
};

