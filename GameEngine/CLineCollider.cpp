#include "pch.h"
#include "CLineCollider.h"
#include "CEngine.h"
#include "CCamera.h"
#include "CGameObject.h"

CLineCollider::CLineCollider(CGameObject* obj)
	: CCollider(obj)
	, p1{}
	, p2{}
{
}

CLineCollider::CLineCollider(const CLineCollider& _other)
	: CCollider(_other)
	, p1(_other.p1)
	, p2(_other.p2)
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

	Vector2 vPos = GETINSTANCE(CCamera)->GetRenderPos(m_vFinalPos);

	//Vector2 vPos = GetOwner()->GetPos();

	Rectangle(_dc, (int)(vPos.x - m_vScale.x / 2)
		, (int)(vPos.y - m_vScale.y / 2)
		, (int)(vPos.x + m_vScale.x / 2)
		, (int)(vPos.y + m_vScale.y / 2));

	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);
}

void CLineCollider::OnTriggerEnter(CCollider* _pOhther)
{
}

void CLineCollider::OnTriggerStay(CCollider* _pOther)
{
}

void CLineCollider::OnTriggerExit(CCollider* _pOhther)
{
}
