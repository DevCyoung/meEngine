#pragma once
#include "CGameObject.h"

class CRockmanObj :
    public CGameObject
{
public:
    UINT			m_ColDir;
    UINT			m_LineDir;
    Vector2         m_vellocity;

	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;

	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);

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

	CLONE(CRockmanObj);

public:
	CRockmanObj();
	CRockmanObj(const CRockmanObj& _other);
	~CRockmanObj();

};

