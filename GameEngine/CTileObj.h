#pragma once
#include "CGameObject.h"

class CTexture;

enum class TITLESTATE
{
    NONE,
    STARTENTER,
    FADEEXIT,
    NEXTLEVEL,
};

class CTileObj :
    public CGameObject
{

public:

    CTexture* m_backgorund;
    CTexture* m_presStart;
    TITLESTATE  m_state;
    float       m_startDelay;
    bool        m_isShowStart;

    virtual void tick() override;
    virtual void render(HDC _dc) override;

    CLONE(CTileObj);

public:
    CTileObj();
    ~CTileObj();
};

