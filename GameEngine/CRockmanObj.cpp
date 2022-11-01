#include "pch.h"
#include "CRockmanObj.h"
#include "CLineColManager.h"
#include "CLineCollider.h"
#include "CLine.h"

CRockmanObj::CRockmanObj()
	:m_ColDir(0)
	, m_LineDir(0)
	, m_vellocity{}
	, m_downRay(nullptr)
{
	m_downRay = new CLine();
	m_downRay->CreateLineCollider(Vector2{}, Vector2{}, LINELAYER::DOWN);
	GETINSTANCE(CLineColManager)->LayerRegister(LINELAYER::DOWN, LINELAYER::DOWNWALL);
}

CRockmanObj::CRockmanObj(const CRockmanObj& _other)
	: CGameObject(_other)
	, m_ColDir(0)
	, m_LineDir(0)
	, m_vellocity{}
	, m_downRay(nullptr) //여기서문제생길수도있음
{
	if (_other.m_downRay != nullptr)
	{
		CreateLineCollider();
	}
}

CRockmanObj::~CRockmanObj()
{
	if (nullptr != m_downRay)
	{
		delete m_downRay;
	}
}
void CRockmanObj::CreateLineCollider()
{
	if (m_downRay != nullptr)
		return;
	m_downRay = new CLine();
	m_downRay->CreateLineCollider(Vector2{}, Vector2{}, LINELAYER::DOWN);
	GETINSTANCE(CLineColManager)->LayerRegister(LINELAYER::DOWN, LINELAYER::DOWNWALL);
}

void CRockmanObj::tick()
{
	if (nullptr != m_downRay)
	{
		m_downRay->GetLineCollider()->MoveRaycast(GetPos());
	}
	CGameObject::tick();
}

void CRockmanObj::fixed_tick()
{
	CGameObject::fixed_tick();
}

void CRockmanObj::render(HDC _dc)
{
	//충돌체등 그리기
	CGameObject::render(_dc);
}



void CRockmanObj::OnTriggerEnter(CCollider* _pOhter)
{
}

void CRockmanObj::OnTriggerStay(CCollider* _pOhter)
{
}

void CRockmanObj::OnTriggerExit(CCollider* _pOhter)
{
}



void CRockmanObj::OnTriggerEnterUp(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::UP;
}

void CRockmanObj::OnTriggerEnterDown(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::DOWN;

}
void CRockmanObj::OnTriggerEnterLeft(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::LEFT;
}

void CRockmanObj::OnTriggerEnterRight(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::RIGHT;
}





void CRockmanObj::OnTriggerStayUp(CCollider* _pOther)
{
	
}

void CRockmanObj::OnTriggerStayDown(CCollider* _pOther)
{
	
}

void CRockmanObj::OnTriggerStayLeft(CCollider* _pOther)
{
	
}

void CRockmanObj::OnTriggerStayRight(CCollider* _pOther)
{
	
}

void CRockmanObj::OnTriggerExitUp(CCollider* _pOther)
{
	m_ColDir &= ~(UINT)COL_STATE_DIR::UP;
}

void CRockmanObj::OnTriggerExitDown(CCollider* _pOther)
{
	m_ColDir &= ~(UINT)COL_STATE_DIR::DOWN;
}

void CRockmanObj::OnTriggerExitLeft(CCollider* _pOther)
{
	m_ColDir &= ~(UINT)COL_STATE_DIR::LEFT;
}

void CRockmanObj::OnTriggerExitRight(CCollider* _pOther)
{
	m_ColDir &= ~(UINT)COL_STATE_DIR::RIGHT;
}