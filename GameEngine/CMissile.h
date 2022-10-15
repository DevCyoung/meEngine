#pragma once
#include "CGameObject.h"
class CMissile :
    public CGameObject
{
private:
    float m_fSpeed;
    float m_angle;

public:
    void SetDirection(float _angle) { this->m_angle = _angle; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void OnTriggerEnter(CCollider* _pOhter);
    virtual void OnTriggerStay(CCollider* _pOhter);
    virtual void OnTriggerExit(CCollider* _pOhter);

    CLONE(CMissile);

public:
    CMissile();
    ~CMissile();
};

