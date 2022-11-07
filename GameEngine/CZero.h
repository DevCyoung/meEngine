#pragma once
#include "CRockmanObj.h"
#include "CRaycast.h"
#include "CPlayerAnimEvent.h"

enum class ZEROSTATE
{

};

class CLineCollider;
class CRaycast;
class CLine;
class CPlayerController;
class CPlayerAnimEvent;

class CZero :
    public CRockmanObj
{
private:
	CPlayerController*  m_playerController;
	CPlayerAnimEvent*	m_animEvent;

	//CLine*			m_downRay;

	CLineCollider*		m_downLandCheck;
	CLineCollider*		m_curLand;
	Vector2				m_landDir;
	
	



	float	m_fVerticalRayDist;
	float	m_fHorizonRayDist;
	bool	m_bisLand;


public:
	//¼öÁ¤
	CLineCollider* m_dirMoveLine;
	CCollider* m_dirMoveBox;

public:
	virtual void tick() override;
	
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;
	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);

public:
	void CreatePlayerController();
	void CreateAnimEvent();


public:
	void init();
	void EventInit();
	void EventTick();

public:
	void PlayerControll();


public:
	virtual void DownHitEnter(CLineCollider* _pOhter)     override;
	virtual void DownHitStay(CLineCollider* _pOhter)	  override;
	virtual void DownHitExit(CLineCollider* _pOhter)	  override;
	virtual void UpHitEnter(CLineCollider* _pOhter)		  override;
	virtual void UpHitStay(CLineCollider* _pOhter)		  override;
	virtual void UpHitExit(CLineCollider* _pOhter)		  override;
	virtual void LeftHitEnter(CLineCollider* _pOhter)	  override;
	virtual void LeftHitStay(CLineCollider* _pOhter)	  override;
	virtual void LeftHitExit(CLineCollider* _pOhter)	  override;
	virtual void RightHitEnter(CLineCollider* _pOhter)	  override;
	virtual void RightHitStay(CLineCollider* _pOhter)	  override;
	virtual void RightHitExit(CLineCollider* _pOhter)	  override;

	//box
public:
	virtual void OnTriggerEnterLeft(CCollider* _pOther)		override;
	virtual void OnTriggerEnterRight(CCollider* _pOther)	override;
	virtual void OnTriggerEnterUp(CCollider* _pOther)		override;
	virtual void OnTriggerEnterDown(CCollider* _pOther)		override;

	virtual void OnTriggerExitLeft(CCollider* _pOther)		override;
	virtual void OnTriggerExitRight(CCollider* _pOther)		override;
	virtual void OnTriggerExitUp(CCollider* _pOther)		override;
	virtual void OnTriggerExitDown(CCollider* _pOther)		override;


	UINT	GetAttackState() { return m_animEvent->m_attackCount; }

public:
	CLONE(CZero);



public:
	CZero();
	CZero(const CZero& _other);
	~CZero();
};

