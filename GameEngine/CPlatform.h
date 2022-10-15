#pragma once
#include "CGameObject.h"
class CPlatform :
    public CGameObject
{
public:
    virtual void OnTriggerEnter(CCollider* _pOther) override;
    virtual void OnTriggerStay(CCollider* _pOther) override;
    virtual void OnTriggerExit(CCollider* _pOther) override;

    CLONE(CPlatform);


public:
    CPlatform();
    ~CPlatform();
};