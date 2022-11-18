#pragma once
#include "CGameObject.h"

class CCyberKujacer;
class CTexture;

class CMonsterHpbar :
    public CGameObject
{
public:

    int                   m_Maxhp;
    float                 m_prevHp;
    bool                  m_redHp;
    float                 m_HPoffset;
    float                 m_HPRedOffset;
    float                 m_distance;
    CCyberKujacer*          m_target;
    CTexture*             m_hpTexture;

    virtual void tick() override;
    virtual void render(HDC _dc) override;

    CLONE(CMonsterHpbar);


public:
    CMonsterHpbar();
    ~CMonsterHpbar();
};

