#pragma once
#include "CGameObject.h"

class CTexture;
class CRockmanObj;

class CHPbar :
    public CGameObject
{
public:

    int                   m_Maxhp;
    float                   m_prevHp;
    bool                  m_redHp;
    float                 m_HPoffset;
    float                 m_HPRedOffset;
    CRockmanObj*         m_target;

    CTexture* m_hpTexture;

    virtual void tick() override;
    virtual void render(HDC _dc) override;    

    CLONE(CHPbar);


public:
    CHPbar();
    ~CHPbar();
};

