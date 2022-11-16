#pragma once
#include "CGameObject.h"

class CTexture;
class CZero;

class CHPbar :
    public CGameObject
{
public:

    int                   m_Maxhp;
    float                   m_prevHp;
    bool                  m_redHp;
    float                 m_HPoffset;
    float                 m_HPRedOffset;
    CZero*              m_target;

    CTexture* m_hpTexture;

    virtual void tick() override;
    virtual void render(HDC _dc) override;    

    CLONE(CHPbar);


public:
    CHPbar();
    ~CHPbar();
};

