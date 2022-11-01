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
	, m_bIsRenderGizmo(false)
	, m_dir(WALLDIR::NONE)
	, m_isDead(false)
	, m_point{}
	, m_rayDir{}
	, m_offset{}
	, m_distance(0.f)
{

}

CLineCollider::CLineCollider(const CLineCollider& _other)
	: CCollider(_other)
	, m_vP1(_other.m_vP1)
	, m_vP2(_other.m_vP2)
	, m_EnterEvent(_other.m_EnterEvent)
	, m_StayEvent (_other.m_StayEvent)
	, m_ExitEvent (_other.m_ExitEvent)
	, m_bIsRenderGizmo(_other.m_bIsRenderGizmo)
	, m_dir(_other.m_dir)
	, m_layer(_other.m_layer)
	, m_isDead(false)
	, m_point{}
	, m_rayDir{}
	, m_offset{}
	, m_distance(0.f)
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
		switch (m_dir)
		{
		case WALLDIR::LEFT:
		{
			hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::BLACK);
		}
		break;
		case WALLDIR::UP:
		{
			hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::BLUE);
		}
		break;
		case WALLDIR::RIGHT:
		{
			hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::ORANGE);
		}
		break;
		case WALLDIR::DOWN:
		{
			hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::GREEN);
		}
		break;

		}

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


void CLineCollider::SetRaycast(Vector2 point, Vector2 dir, Vector2 offset, float distance)
{
	//시작점을 p1으로한다.
	

	m_point = point;
	m_rayDir = dir;
	m_offset = offset;
	m_distance = distance;

	m_rayDir.Normalize();

	m_vP1 = m_point + m_offset;
	m_vP2 = m_point + m_rayDir * m_distance + m_offset;
}

void CLineCollider::MoveRaycast(Vector2 point)
{
	m_vP1 = point + m_offset;
	m_vP2 = point + m_rayDir * m_distance + m_offset;
}
