#include "pch.h"
#include "CLine.h"
#include "CLineCollider.h"
#include "CLineColManager.h"
#include "CCamera.h"
CLine::CLine()
	: m_isRenderPoint(false)
	, m_lineCollider(nullptr)
{
}

CLine::CLine(const CLine& _other)
	: m_isRenderPoint(false)
	, m_lineCollider(nullptr)
{

}

CLine::~CLine()
{
	if (nullptr != m_lineCollider)
	{
		/*GETINSTANCE(CLineColManager)->RemoveLine(m_lineCollider);
		m_lineCollider = nullptr;*/
	}
}

void CLine::tick()
{
	
	//m_lineCollider->TranslateSetPos(GetPos());
}

void CLine::fixed_tick()
{
	
}

void CLine::render(HDC _dc)
{
	Vector2 p1 = m_lineCollider->GetP1();
	Vector2 p2 = m_lineCollider->GetP2();
	p1 = GETINSTANCE(CCamera)->GetRenderPos(p1);
	p2 = GETINSTANCE(CCamera)->GetRenderPos(p2);

	int distance = 16;
	if (m_isRenderPoint)
	{
		Rectangle
		(
			_dc, (int)(p1.x - distance / 2)
			, (int)(p1.y - distance / 2)
			, (int)(p1.x + distance / 2)
			, (int)(p1.y + distance / 2)
		);

		Rectangle
		(
			_dc, (int)(p2.x - distance / 2)
			, (int)(p2.y - distance / 2)
			, (int)(p2.x + distance / 2)
			, (int)(p2.y + distance / 2)
		);
	}
}

void CLine::SetRaycast(Vector2 point, Vector2 dir, Vector2 offset, float distance)
{
	m_lineCollider->SetRaycast(point, dir, offset, distance);
}

void CLine::CreateLineCollider(Vector2 p1, Vector2 p2, LINELAYER layer)
{
	m_lineCollider = GETINSTANCE(CLineColManager)->CreateLine(p1, p2, layer);
}


void CLine::SetEnterEvent(DELEGATECOL func, CEntity* instance)
{
	m_lineCollider->SetEnterEvent(func, instance);
}

void CLine::SetStayEvent(DELEGATECOL func, CEntity* instance)
{
	m_lineCollider->SetStayEvent(func, instance);
}

void CLine::SetExitEvent(DELEGATECOL func, CEntity* instance)
{
	m_lineCollider->SetExitEvent(func, instance);
}
