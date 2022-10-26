#pragma once
#include "CRockmanObj.h"
#include "CRaycast.h"

class CLineCollider;
class CRaycast;




class CZero :
    public CRockmanObj
{
private:
	//CLineCollider*	m_mapLineCol[(UINT)RAY_TYPE::END];
	//CLineCollider* m_downRay;
	//CLineCollider* m_leftRay;
	//CLineCollider* m_rightRay;
	//CLineCollider* m_upRay;

	CRaycast m_ray;



	CLineCollider* m_downLandCheck;

	CLineCollider* m_curLand;

	Vector2	m_landDir;


	float	m_fVerticalRayDist;
	float	m_fHorizonRayDist;
	bool	m_bisLand;

public:
	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;
	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);


public:
	void init();
	void EventInit();
	void EventTick();


public:
	void DownHitEnter(CLineCollider* _pOhter);
	void DownHitStay(CLineCollider* _pOhter);
	void DownHitExit(CLineCollider* _pOhter);

	void UpHitEnter(CLineCollider* _pOhter);
	void UpHitStay(CLineCollider* _pOhter);
	void UpHitExit(CLineCollider* _pOhter);

	void LeftHitEnter(CLineCollider* _pOhter);
	void LeftHitStay(CLineCollider* _pOhter);
	void LeftHitExit(CLineCollider* _pOhter);

	void RightHitEnter(CLineCollider* _pOhter);
	void RightHitStay(CLineCollider* _pOhter);
	void RightHitExit(CLineCollider* _pOhter);


public:
public:
	CLONE(CZero);



public:
	CZero();
	CZero(const CRockmanObj& _other);
	~CZero();
};

