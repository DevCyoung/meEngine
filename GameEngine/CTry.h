#pragma once
#include "CRockmanMonster.h"

enum class TRYSTATE
{
	WAIT,
	ATTACK,
	END,
};

class CTry :
	public CRockmanMonster
{

	TRYSTATE	m_state;
	float		m_delay[(UINT)TRYSTATE::END];
	Vector2		m_attackDir;

	//To componet
	vector<tDashFrame>  m_arrDashFrame;
	UINT                m_dashFrameIdx;
	float               m_dashFrameDelay;



public:
	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;


	void DashFrame();

	CLONE(CTry);

public:
	CTry();
	CTry(const CTry& _other);
	~CTry();

};

