#pragma once
#include "CCollider.h"

class CLineCollider :
    public CCollider
{

private:
    Vector2 p1;
    Vector2 p2;

public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

    virtual void    OnTriggerEnter(CCollider* _pOhther) override;
    virtual void    OnTriggerStay(CCollider* _pOther)   override;
    virtual void    OnTriggerExit(CCollider* _pOhther)  override;

public :
    CLONE(CLineCollider);


public:
    CLineCollider(CGameObject* obj); //기본생성자 안만듬
    CLineCollider(const CLineCollider& _other);
    ~CLineCollider();

};

