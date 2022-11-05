#pragma once
#include "CComponent.h"

class CGameObject;

class CCollider :
    public CComponent
{
protected:
    Vector2                 m_vOffsetPos;
    Vector2                 m_vFinalPos;
    Vector2                 m_vScale;
    HPEN                    m_hPen;
    int                     m_iOverlapCount;

    map<UINT, COLLIDE_DIR>	m_mapColdir;

    UINT                    m_curWallDir[(UINT)COLLIDE_DIR::END];
        

public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

public:
    void SetOffsetPos(Vector2 _voffsetPos) { m_vOffsetPos = _voffsetPos; }
    Vector2 GetOffsetPos() { return m_vOffsetPos; }

    void SetScale(Vector2 _vScale) { m_vScale = _vScale; }
    Vector2 GetScale() const { return m_vScale; }

    Vector2 GetFinalPos() const { return m_vFinalPos; }

public:
    virtual void    OnTriggerEnter(CCollider* _pOhther);
    virtual void    OnTriggerStay(CCollider* _pOther);
    virtual void    OnTriggerExit(CCollider* _pOhther);

    UINT            GetWallDirState(COLLIDE_DIR dir) { return m_curWallDir[(UINT)dir]; }
    

public:
    int GetCollideCnt() { return m_iOverlapCount; }

public:
    CLONE(CCollider);

public:
    CCollider(CGameObject* obj); //기본생성자 안만듬
    CCollider(const CCollider& _other);
    ~CCollider();

};

