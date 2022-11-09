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
    eTextAnimState m_state;

    virtual void tick() override;
    virtual void render(HDC _dc) override;

    CTexture* m_texture;

    void AutoSplitRandom(UINT size);

public:
    void Enter();
    void Remove();

    CLONE(CTextureAnim);


public:
    CTextureAnim();
    ~CTextureAnim();

};

