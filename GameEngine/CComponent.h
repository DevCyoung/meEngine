#pragma once
#include "CEntity.h"

class CGameObject;

class CComponent :
    public CEntity
{
private:
    CGameObject*    m_pOwner;

public:
    //추상클래스
    virtual void tick() = 0;
    virtual void render(HDC _dc) = 0;
    virtual void final_tick() {};

public:
    CGameObject* GetOwner() { return m_pOwner; }
private:
    void SetOwner(CGameObject* _pOwner) { m_pOwner = _pOwner; }

    

public:
    CComponent(CGameObject* obj); //기본생성자 안만듬
    ~CComponent();

    friend class CGameObject;
    friend class CLine;
};

