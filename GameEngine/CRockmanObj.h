#pragma once
#include "CGameObject.h"
#include "CLine.h"
class CRockmanObj :
    public CGameObject
{
protected:
    UINT			m_ColDir;
    UINT			m_LineDir;
	CLine*			m_downRay;
    Vector2         m_vellocity;

	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;

	//box 
	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);

	//box dir
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

	//ray dir
	virtual void DownHitEnter(CLineCollider* _pOhter)	{};
	virtual void DownHitStay(CLineCollider* _pOhter)	{};
	virtual void DownHitExit(CLineCollider* _pOhter)	{};
	virtual void UpHitEnter(CLineCollider* _pOhter)		{};
	virtual void UpHitStay(CLineCollider* _pOhter)		{};
	virtual void UpHitExit(CLineCollider* _pOhter)		{};
	virtual void LeftHitEnter(CLineCollider* _pOhter)	{};
	virtual void LeftHitStay(CLineCollider* _pOhter)	{};
	virtual void LeftHitExit(CLineCollider* _pOhter)	{};
	virtual void RightHitEnter(CLineCollider* _pOhter)	{};
	virtual void RightHitStay(CLineCollider* _pOhter)	{};
	virtual void RightHitExit(CLineCollider* _pOhter)	{};



	CLONE(CRockmanObj);

public:
	CRockmanObj();
	CRockmanObj(const CRockmanObj& _other);
	~CRockmanObj();

};

