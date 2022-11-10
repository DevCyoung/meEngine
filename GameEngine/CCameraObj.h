#pragma once
#include "CGameObject.h"
class CCameraObj :
    public CGameObject
{

private:
	CGameObject*    m_target;
	UINT			m_ColDir;
public:
	Vector2			m_position;
public:
	void	SetTarget(CGameObject* target) { m_target = target; }
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

