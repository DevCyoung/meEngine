#pragma once
#include "CComponent.h"

class CAnimation;
class CTexture;
class CGameObject;


class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>       m_mapAnim;
    CAnimation*                     m_pCurAnim;
    bool                            m_bRepeat;
    bool                            m_bReverse;

public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;


public:
    void Play(const wstring& _strName, bool _bRepeat);
    void TrigerPlay(const wstring& _strName, bool _bRepeat);

    void        CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vector2 _vLeftTop, Vector2 _vSize, Vector2 _vOffset, int _iMaxFrmCount, float _fDuration);
    CAnimation* FindAnimation(const wstring& _strName);
    CAnimation* LoadAnimation(const wstring& _strRelativePath);
    CAnimation* GetCurAnimation() { return m_pCurAnim; }

    //my
public:
    void SetAnimFrameFunc(const wstring& _animName, int _iFrameNum, CGameObject* _obj, DELEGATE _delegate);
    void SetReverse(bool m_rev) { m_bReverse = m_rev; }
    bool GetReverse() { return m_bReverse; }


public:
    CLONE(CAnimator);

public:
    CAnimator(CGameObject* _pOwner);
    CAnimator(const CAnimator& _other);
    ~CAnimator();
};

