#pragma once
#include "CEntity.h"

class CAnimator;
class CTexture;

class CAnimation :
    public CEntity
{
private:
    CAnimator*          m_pAnimator;
    vector<tAnimFrm>    m_vecFrm;  

    CTexture*           m_pAtlas;
    int                 m_iCurFrm;
    float               m_fAccTime;
    bool                m_bFinish;

private:
    void init(const wstring& _strName, CTexture* _pAtlas, Vector2 _vLeftTop, Vector2 _vSize, Vector2 _vOffset, int _iMaxFrmCount, float _fDuration);


public:
    void tick();
    void render(HDC _dc);

public:
    bool IsFinish() { return m_bFinish; }
    void Reset()
    {
        m_bFinish = false;
        m_iCurFrm = 0;
        m_fAccTime = 0.f;
    }

    void Save(const wstring& _strRelativePath);
    void Load(const wstring& _strRelativePath);

    tColInfo GetColinfo(int idx) { return m_vecFrm[idx].colInfo; }

public:
    CLONE(CAnimation);

    //내가만든코드
    void SetFrameFunc(int _iFrameNum, CEntity* _obj, DELEGATE _delegate)
    {
        assert(_iFrameNum < m_vecFrm.size());
        m_vecFrm[_iFrameNum].action.func = _delegate;
        m_vecFrm[_iFrameNum].action.instance = _obj;
    }

public:
    CAnimation(CAnimator* _pAnimator);
    ~CAnimation();

    friend class CAnimator;
};

