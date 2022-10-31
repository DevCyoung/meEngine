#pragma once
#include "CCollider.h"


class CLineColManager;
class CEditorLevel;
class CLineCollider :
    public CCollider
{

private:
    Vector2         m_vP1;
    Vector2         m_vP2;
    WALLDIR         m_dir;

    tColliEvent     m_EnterEvent;
    tColliEvent     m_StayEvent;
    tColliEvent     m_ExitEvent;
    Vector2         m_intersection;
    LINELAYER       m_layer;

  
    bool            m_bIsRenderGizmo;

    bool            m_isDead;

    

public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

public:
    void TranslateMove(Vector2 add);
    void TranslateSetPos(Vector2 pos);
    
    void    OnTriggerEnter(CLineCollider* _pOhther) ;
    void    OnTriggerStay(CLineCollider* _pOther)   ;
    void    OnTriggerExit(CLineCollider* _pOhther)  ;

    void    SetEnterEvent(DELEGATECOL func, CEntity* instance) { m_EnterEvent.func = func, m_EnterEvent.instance = instance; }
    void    SetStayEvent(DELEGATECOL func, CEntity* instance) { m_StayEvent.func = func, m_StayEvent.instance = instance; }
    void    SetExitEvent(DELEGATECOL func, CEntity* instance) { m_ExitEvent.func = func, m_ExitEvent.instance = instance; }

    void    SetRaycast(Vector2 point, Vector2 dir, Vector2 offset, float distance);
    void    SetMoveRaycast(Vector2 point);
    
    void SetP1(Vector2 _vP1) { m_vP1 = _vP1; }
    void SetP2(Vector2 _vP2) { m_vP2 = _vP2; }
    void SetP1P2(Vector2 _vP1, Vector2 _vP2) { SetP1(_vP1); SetP2(_vP2); }
    void SetIsRenderGizmo(bool _bRender) { m_bIsRenderGizmo = _bRender; }


    Vector2 GetP1() const { return m_vP1; }
    Vector2 GetP2() const   { return m_vP2; }
    Vector2 GetIntersction() const { return m_intersection; }
    bool GetIsRenderGizmo() const { return m_bIsRenderGizmo; }

    float GetP1Length(Vector2 pos) { return (pos - m_vP1).Length(); }
    float GetP2Length(Vector2 pos) { return (pos - m_vP2).Length(); }

    bool    IsDead() { return m_isDead; }

public :
    CLONE(CLineCollider);


public:
    CLineCollider(CGameObject* obj); //기본생성자 안만듬
    CLineCollider(const CLineCollider& _other);
    ~CLineCollider();

    friend CLineColManager;
    friend CEditorLevel;
};

