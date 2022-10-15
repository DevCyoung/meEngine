#pragma once
#include "CComponent.h"

class CGameObject;

class CCollider :
    public CComponent
{
private:
    Vector2    m_vOffsetPos;
    Vector2    m_vFinalPos;
    Vector2    m_vScale;
    HPEN    m_hPen;
    int    m_iOverlapCount;

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    void SetOffsetPos(Vector2 _voffsetPos) { m_vOffsetPos = _voffsetPos; }
    Vector2 GetOffsetPos() { return m_vOffsetPos; }

    void SetScale(Vector2 _vScale) { m_vScale = _vScale; }
    Vector2 GetScale() const { return m_vScale; }

    Vector2 GetFinalPos() const { return m_vFinalPos; }

public:
    void    OnTriggerEnter(CCollider* _pOhther);
    void    OnTriggerStay(CCollider* _pOther);
    void    OnTriggerExit(CCollider* _pOhther);


public:
    CLONE(CCollider);

public:
    CCollider(CGameObject* obj); //기본생성자 안만듬
    CCollider(const CCollider& _other);
    ~CCollider();

};

