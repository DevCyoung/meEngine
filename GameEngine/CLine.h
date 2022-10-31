#pragma once
#include "CGameObject.h"

class CLineCollider;

class CLine :
    public CGameObject
{

public:
	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;

	CLineCollider* m_lineCollider;
	bool		   m_isRenderPoint;

public:
	CLineCollider*	GetLineCollider() { return m_lineCollider; }
	void			CreateLineCollider(Vector2 p1, Vector2 p2, LINELAYER layer);

	void    SetEnterEvent(DELEGATECOL func, CEntity* instance);
	void    SetStayEvent(DELEGATECOL func, CEntity* instance) ;
	void    SetExitEvent(DELEGATECOL func, CEntity* instance);
	//void ResizeCollider(Vector2 leftTop, Vector2 bottom);

public:
	CLONE(CLine);



public:
	CLine();
	CLine(const CLine& _other);
	~CLine();
};

