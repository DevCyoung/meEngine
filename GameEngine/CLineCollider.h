#pragma once
#include "CCollider.h"

class CLineColManager;


class CLineCollider :
    public CCollider
{

private:
    Vector2         m_vP1;
    Vector2         m_vP2;
    Vector2         m_intersection;

    tColliEvent     EnterEvent;
    tColliEvent     StayEvent;
    tColliEvent     ExitEvent;

    LAYER           layer;

    bool            bIsRenderPoint;

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

    void    SetOnTriggerEnterEvent(tColliEvent _colEvent) { EnterEvent = _colEvent;}    
    void    SetOnTriggerStayEvent(tColliEvent _colEvent) { StayEvent = _colEvent;}
    void    SetOnTriggerExitEvent(tColliEvent _colEvent) { ExitEvent = _colEvent;}

    void    SetEnterEvent(DELEGATECOL func, CEntity* instance) { EnterEvent.func = func, EnterEvent.instance = instance; }
    void    SetStayEvent(DELEGATECOL func, CEntity* instance) { StayEvent.func = func, StayEvent.instance = instance; }
    void    SetExitEvent(DELEGATECOL func, CEntity* instance) { ExitEvent.func = func, ExitEvent.instance = instance; }

    
    void SetP1(Vector2 _vP1) { m_vP1 = _vP1; }
    void SetP2(Vector2 _vP2) { m_vP2 = _vP2; }
    void SetP1P2(Vector2 _vP1, Vector2 _vP2) { SetP1(_vP1); SetP2(_vP2); }
    void SetRenderPoint(bool _bRender) { bIsRenderPoint = _bRender; }


    Vector2 GetP1() const { return m_vP1; }
    Vector2 GetP2() const   { return m_vP2; }
    Vector2 GetIntersction() const { return m_intersection; }

    float GetP1Length(Vector2 pos) { return (pos - m_vP1).Length(); }
    float GetP2Length(Vector2 pos) { return (pos - m_vP2).Length(); }



public :
    CLONE(CLineCollider);


public:
    CLineCollider(CGameObject* obj); //기본생성자 안만듬
    CLineCollider(const CLineCollider& _other);
    ~CLineCollider();

    friend CLineColManager;
};

