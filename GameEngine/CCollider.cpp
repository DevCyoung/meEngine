#include "pch.h"
#include "CCollider.h"
#include "CEngine.h"
#include "CComponent.h"
#include "CGameObject.h"
#include "CCamera.h"


CCollider::CCollider(CGameObject* obj)
	: CComponent(obj)
	, m_iOverlapCount(0)
	, m_hPen(GETINSTANCE(CEngine)->GetPen(PEN_TYPE::GREEN))
{
}

CCollider::CCollider(const CCollider& _other)
	: CComponent(nullptr)
	, m_vOffsetPos(_other.m_vOffsetPos)
	, m_vScale(_other.m_vScale)
	, m_iOverlapCount(0)
{
}

CCollider::~CCollider()
{
}


void CCollider::tick()
{
	//중첩수가 음수인경우
	assert(!(m_iOverlapCount < 0));
}

void CCollider::final_tick()
{
	//충돌 체의 최종 위치값을 결정한다.
	m_vFinalPos = this->GetOwner()->GetPos() + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
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

void CCollider::OnTriggerEnter(CCollider* _pOhther)
{
	++m_iOverlapCount;
	this->GetOwner()->OnTriggerEnter(_pOhther);
}

void CCollider::OnTriggerStay(CCollider* _pOhther)
{
	this->GetOwner()->OnTriggerStay(_pOhther);
}

void CCollider::OnTriggerExit(CCollider* _pOhther)
{
	--m_iOverlapCount;
	this->GetOwner()->OnTriggerExit(_pOhther);
}

