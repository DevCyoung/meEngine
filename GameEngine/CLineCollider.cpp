#include "pch.h"
#include "CLineCollider.h"
#include "CEngine.h"
#include "CCamera.h"
#include "CGameObject.h"

CLineCollider::CLineCollider(CGameObject* obj)
	: CCollider(obj)
	, m_vP1{}
	, m_vP2{}
	, m_EnterEvent{}
	, m_StayEvent{}
	, m_ExitEvent{}
	, m_intersection{}
	, m_layer{}
	, m_bIsRenderPoint(false)
	, m_dir(WALLDIR::NONE)
{

}

CLineCollider::CLineCollider(const CLineCollider& _other)
	: CCollider(_other)
	, m_vP1(_other.m_vP1)
	, m_vP2(_other.m_vP2)
	, m_EnterEvent(_other.m_EnterEvent)
	, m_StayEvent (_other.m_StayEvent)
	, m_ExitEvent (_other.m_ExitEvent)
	, m_bIsRenderPoint(_other.m_bIsRenderPoint)
	, m_dir(_other.m_dir)
	, m_layer(_other.m_layer)
{
}

CLineCollider::~CLineCollider()
{

}

void CLineCollider::tick()
{
	//중첩수가 음수인경우
	assert(!(m_iOverlapCount < 0));
}

void CLineCollider::final_tick()
{
	//충돌 체의 최종 위치값을 결정한다.
	m_vFinalPos = this->GetOwner()->GetPos() + m_vOffsetPos;
}

void CLineCollider::render(HDC _dc)
{
	//충돌체를 그린다.
	HPEN hPen = nullptr;
	if (0 < m_iOverlapCount)
	{
		hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::RED);
	}
	else
	{
		hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::GREEN);
	}

	HBRUSH	hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HPEN	hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH	hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Vector2 p1 = GETINSTANCE(CCamera)->GetRenderPos(m_vP1);
	Vector2 p2 = GETINSTANCE(CCamera)->GetRenderPos(m_vP2);

	MoveToEx(_dc, p1.x, p1.y, nullptr);
	LineTo(_dc, p2.x, p2.y);
	

	//Vector2 vPos = GetOwner()->GetPos();

	//Rectangle(_dc, (int)(vPos.x - m_vScale.x / 2)
	//	, (int)(vPos.y - m_vScale.y / 2)
	//	, (int)(vPos.x + m_vScale.x / 2)
	//	, (int)(vPos.y + m_vScale.y / 2));

	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);
	
	//hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::BLUE);
	
	int distance = 16;
	if (m_bIsRenderPoint)
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

void CLineCollider::TranslateMove(Vector2 add)
{
	m_vP1 += add;
	m_vP2 += add;
}

void CLineCollider::TranslateSetPos(Vector2 pos)
{
	//기준은 1p으로 한다.
	m_vP2.x += pos.x - m_vP1.x;
	m_vP2.y += pos.y - m_vP1.y;
	m_vP1 = pos;
}

void CLineCollider::OnTriggerEnter(CLineCollider* _pOhther)
{			
		++m_iOverlapCount;
	if (m_EnterEvent.instance && m_EnterEvent.func)
	{
		(m_EnterEvent.instance->*m_EnterEvent.func)(_pOhther);
	}
}

void CLineCollider::OnTriggerStay(CLineCollider* _pOhther)
{
	if (m_StayEvent.instance && m_StayEvent.func)
	{
		(m_StayEvent.instance->*m_StayEvent.func)(_pOhther);
	}
}

void CLineCollider::OnTriggerExit(CLineCollider* _pOhther)
{
		--m_iOverlapCount;
	if (m_ExitEvent.instance && m_ExitEvent.func)
	{
		(m_ExitEvent.instance->*m_ExitEvent.func)(_pOhther);
	}
}
