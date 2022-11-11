#pragma once
#include "CGameObject.h"

class CTexture;
class CHPbar :
    public CGameObject
{

    CTexture* m_hpTexture;

    virtual void tick() override;
    virtual void render(HDC _dc) override;    

    CLONE(CHPbar);


public:
    CHPbar();
    ~CHPbar();
};

