#pragma once
#include "CComponent.h"

class CRigidbody :
    public CComponent
{
private:
    Vector2    m_vForce;           // ��
    Vector2    m_vVelocity;        // �ӵ� ( vector )
    float   m_fMass;            // ����

    float   m_fFriction;        // ������
    float   m_fFrictionScale;   // �������

    float   m_fVelocityLimit;   // ���� �ӵ�
    float   m_fGravityVLimit;   // �߷¿� ���� ���� �ӵ�


    float   m_fGravityAccel;    // �߷� ���ӵ� ����
    bool    m_bGravityUse;      // �߷� ��뿩��
    bool    m_bGround;          // �� üũ


public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

public:
    void AddForce(Vector2 _vForce) { m_vForce += _vForce; }
    void SetVelocityLimit(float _fLimit) { m_fVelocityLimit = _fLimit; }
    void SetGravityVelocityLimit(float _fLimit) { m_fGravityVLimit = _fLimit; }
    float GetGravityScale() { return m_fGravityAccel; }

    void SetVelocity(Vector2 _vVelocity) { m_vVelocity = _vVelocity; }
    Vector2 GetVelocity() { return m_vVelocity; }

    void AddVelocity(Vector2 _vAddV) { m_vVelocity += _vAddV; }

    void SetFriction(float _f) { m_fFriction = _f; }
    void SetFrictionScale(float _f) { m_fFrictionScale = _f; }
    void SetGravity(bool _bSet) { m_bGravityUse = _bSet; }
    void SetGravityAccel(float _fAccel) { m_fGravityAccel = _fAccel; }
    void SetGround(bool _bGround);


public:
    CLONE(CRigidbody);

public:
    CRigidbody(CGameObject* _pOwner);
    CRigidbody(const CRigidbody& _other);
    ~CRigidbody();
    //virtual ~CRigidbody();
};

