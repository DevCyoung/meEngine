#pragma once
#include "CEntity.h"

class CCollider;
class CAnimator;
class CRigidbody;

class CGameObject :
    public CEntity
{
private:
    Vector2     m_vPos;
    Vector2     m_vScale;
    bool        m_isFlipX;
    bool        m_isFlipY;

private:
    CCollider* m_pCollider;
    CAnimator* m_pAnimator;
    CRigidbody* m_pRigidbody;

    bool        m_bDead;

protected:
    void CreateCollider();
    void CreateAnimator();
    void CreateRigidbody();

public:
    CCollider* GetCollider() { return m_pCollider; }
    CAnimator* GetAnimator() { return m_pAnimator; }
    CRigidbody* GetRigidbody() { return m_pRigidbody; }

public:
    virtual void tick();
    virtual void final_tick() final;
    virtual void render(HDC _dc);

public:
    void SetPos(Vector2 _vec2) { m_vPos = _vec2; }
    void SetScale(Vector2 _vec2) { m_vScale = _vec2; }
    void SetFilpX(bool _isFlipX) { m_isFlipX = _isFlipX; }
    void SetFilpY(bool _isFlipY) { m_isFlipY = _isFlipY; }

    Vector2 GetPos()        { return m_vPos; } 
    Vector2 GetScale()      { return m_vScale; } 
    bool GetFilpX() const   { return m_isFlipX; }
    bool GetFilpY() const   { return m_isFlipY; }


public:
    //전역으로변경
    void    Instantiate(CGameObject* _pNewObj, Vector2 _vPos, LAYER _eLayer);

    //Physics calc
    virtual void OnTriggerEnter(CCollider* _pOther);
    virtual void OnTriggerStay(CCollider* _pOther);
    virtual void OnTriggerExit(CCollider* _pOther);

    bool    IsDead() { return m_bDead; }
    void    Destroy();
    virtual CGameObject* Clone() = 0;

//test
public:
    void Func(CGameObject* _obj, void(CGameObject::* Function)(void));
    virtual void Func();

public:
    CGameObject();
   CGameObject(const CGameObject& _other);
    ~CGameObject();

    friend class CEventManager;
};
