#pragma once
#include "CRockmanObj.h"

class CLineCollider;

enum class RAY_TYPE
{
	DOWN_LEFT,
	DOWN_RIGHT,
	UP_LEFT,
	UP_RIGHT,
	LEFT_UP,
	LEFT_DOWN,
	RIGHT_UP,
	RIGHT_DOWN,
	END
};

class CZero :
    public CRockmanObj
{
private:
	//CLineCollider*	m_mapLineCol[(UINT)RAY_TYPE::END];
	CLineCollider* m_downColLeft;
	CLineCollider* m_downColRight;
	CLineCollider* m_downLandCheck;

	CLineCollider* m_curLand;

	Vector2	m_landDir;
	float	m_rayDistance;
	bool	m_bisLand;

public:
	virtual void tick() override;
	virtual void render(HDC _dc) override;
	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);


public:
	void DownHitEnter(CLineCollider* _pOhter);
	void DownHitStay(CLineCollider* _pOhter);
	void DownHitExit(CLineCollider* _pOhter);



public:
	CLONE(CZero);



public:
	CZero();
	CZero(const CRockmanObj& _other);
	~CZero();
};

