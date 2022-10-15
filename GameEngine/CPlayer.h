#pragma once
#include "CGameObject.h"

//as
#include "CResourceManager.h"
#include "CTexture.h"

class CCollider;


class CPlayer :
	public CGameObject
{

private:
	float m_fSpeed;




	bool isAtkkAvailable;
	bool canWalkReady;
	bool canWalk;
	int attackCount;
	//txtureÁö¿ö
	CTexture* m_pTexuture;


public:
	virtual void tick() override;
	virtual void render(HDC _dc) override;
	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);


public:
	void EventAttack1(void);
	void EventAttack2(void);
	void EventAttack3(void);
	void EventSCABBARD(void);
	void EventAtkkAvailable(void);
	void EventIdle(void);
	void EventWalkReady(void);
	void EventStartVim(void);
	void EventReturnHome(void);


	void EventJumpReady(void);
	void EventJump(void);
	void EVENtDownReady(void);
	void EventDown(void);
	void EventDownFinish(void);







public:
	CLONE(CPlayer);



public:
	CPlayer();
	~CPlayer();
};

