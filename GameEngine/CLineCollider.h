#pragma once
#include "CCollider.h"

class CLineColManager;


class CLineCollider :
    public CCollider
{

private:
    Vector2         m_vP1;
    Vector2         m_vP2;
    tColliEvent     OnTriggerEnterEvent;
    tColliEvent     OnTriggerStayEvent;
    tColliEvent     OnTriggerExitEvent;

public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

    void    OnTriggerEnter(CLineCollider* _pOhther) ;
    void    OnTriggerStay(CLineCollider* _pOther)   ;
    void    OnTriggerExit(CLineCollider* _pOhther)  ;

    void    SetOnTriggerEnterEvent(tColliEvent _colEvent) { OnTriggerEnterEvent = _colEvent;}
    void    SetOnTriggerStayEvent(tColliEvent _colEvent) { OnTriggerStayEvent = _colEvent;}
    void    SetOnTriggerExitEvent(tColliEvent _colEvent) { OnTriggerExitEvent = _colEvent;}

    
    void SetP1(Vector2 _vP1) { m_vP1 = _vP1; }
    void SetP2(Vector2 _vP2) { m_vP2 = _vP2; }
    //void SetP(Vector2 _vP1, Vector2 _vP2) { SetP1(_vP1); SetP2(_vP2); }

    Vector2 GetP1() const { return m_vP1; }
    Vector2 GetP2() const   { return m_vP2; }
    



public :
    CLONE(CLineCollider);


public:
    CLineCollider(CGameObject* obj); //�⺻������ �ȸ���
    CLineCollider(const CLineCollider& _other);
    ~CLineCollider();

    friend CLineColManager;
};

