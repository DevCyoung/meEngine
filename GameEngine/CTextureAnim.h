#pragma once
#include "CGameObject.h"

enum class eTextAnimState
{
    NONE,
    START,
    REMOVE,
};

class CTexture;


class CTextureAnim :
    public CGameObject
{

    vector<tTexAnim> m_vecTexAnim;
    float            m_removeDuration;
    float            m_frmDuration;
    bool             m_isStop;
    float            m_curVolum;
    eTextAnimState   m_state;

    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CTexture* m_Curtexture;

    CTexture* m_warning;
    CTexture* m_ready;

    void AutoSplitRandom(UINT size);

    void SetReady() { m_Curtexture = m_ready;  }
    void SetWarning() { m_Curtexture = m_warning; }
    void SetfrmDuration(float duration) { m_frmDuration = duration; }

public:
    void Enter();
    void Remove();

    CLONE(CTextureAnim);


public:
    CTextureAnim();
    ~CTextureAnim();

};

