#pragma once
#include "CGameObject.h"

class CZero;

class CCameraObj :
    public CGameObject
{

private:
	CZero*			m_target;
	UINT			m_ColDir;
public:
	float			m_delay;
	Vector2			m_diff;
public:
	Vector2			m_position;


public:
	bool			m_isFollow;

public:
	void	SetTarget(CZero* target) { m_target = target; }
	virtual void tick() override;
	virtual void fixed_tick() override;
	//virtual void fixed_tick() override;
	//virtual void render(HDC _dc) override;

	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);

	virtual void OnTriggerEnterLeft(CCollider* _pOther);
	virtual void OnTriggerEnterRight(CCollider* _pOther);
	virtual void OnTriggerEnterUp(CCollider* _pOther);
	virtual void OnTriggerEnterDown(CCollider* _pOther);
	
	virtual void OnTriggerExitLeft(CCollider* _pOther);
	virtual void OnTriggerExitRight(CCollider* _pOther);
	virtual void OnTriggerExitUp(CCollider* _pOther);
	virtual void OnTriggerExitDown(CCollider* _pOther);
public:
	CLONE(CCameraObj);


public:
	CCameraObj();
	CCameraObj(const CCameraObj& _other);
	~CCameraObj();

};

