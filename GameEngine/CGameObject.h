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
    Vector2	    m_preFramePos;
    LAYER		m_tag;
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
    virtual void fixed_tick();
    virtual void render(HDC _dc);

    
public:
    bool    m_isCollision;
    void    SetCollision(bool b) { m_isCollision = b; }
    bool    GetCollision() { return m_isCollision; }


public:
    void SetPos(Vector2 _vec2) { m_vPos = _vec2; }
    void SetScale(Vector2 _vec2) { m_vScale = _vec2; }
    void SetFlipX(bool _isFlipX) { m_isFlipX = _isFlipX; }
    void SetFilpY(bool _isFlipY) { m_isFlipY = _isFlipY; }
    void SetTag(LAYER layer) { m_tag = layer; }

    Vector2 GetPos()        { return m_vPos; } 
    Vector2 GetScale()      { return m_vScale; } 
    bool GetFilpX() const   { return m_isFlipX; }
    bool GetFilpY() const   { return m_isFlipY; }
    LAYER GetLayer() { return m_tag; }

    void SetPreFramePos(Vector2 pos) { m_preFramePos = pos; }
    Vector2 GetPreFramePos() { return m_preFramePos; }
public:
    //전역으로변경?
    static void    Instantiate(CGameObject* _pNewObj, Vector2 _vPos, LAYER _eLayer);

    //Physics calc
    virtual void OnTriggerEnter(CCollider* _pOther);
    virtual void OnTriggerStay(CCollider* _pOther);
    virtual void OnTriggerExit(CCollider* _pOther);


    virtual void OnTriggerEnterLeft(CCollider* _pOther);
    virtual void OnTriggerEnterRight(CCollider* _pOther);
    virtual void OnTriggerEnterUp(CCollider* _pOther);
    virtual void OnTriggerEnterDown(CCollider* _pOther);
    virtual void OnTriggerStayLeft(CCollider* _pOther);
    virtual void OnTriggerStayRight(CCollider* _pOther);
    virtual void OnTriggerStayUp(CCollider* _pOther);
    virtual void OnTriggerStayDown(CCollider* _pOther);
    virtual void OnTriggerExitLeft(CCollider* _pOther);
    virtual void OnTriggerExitRight(CCollider* _pOther);
    virtual void OnTriggerExitUp(CCollider* _pOther);
    virtual void OnTriggerExitDown(CCollider* _pOther);

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
