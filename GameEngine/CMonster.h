#pragma once
#include "CGameObject.h"

class CCollider;

class CMonster :
    public CGameObject
{


    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void OnTriggerEnter(CCollider* _pOhter);
    virtual void OnTriggerStay(CCollider* _pOhter);
    virtual void OnTriggerExit(CCollider* _pOhter);

    CLONE(CMonster);


public:
    CMonster();
    ~CMonster();
};

