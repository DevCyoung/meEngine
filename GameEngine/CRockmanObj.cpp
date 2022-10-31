#include "pch.h"
#include "CRockmanObj.h"

CRockmanObj::CRockmanObj()
	:m_ColDir(0)
	, m_LineDir(0)
	, m_vellocity{}
{
	
}

CRockmanObj::CRockmanObj(const CRockmanObj& _other)
	:m_ColDir(0)
	,m_LineDir(0)
	, m_vellocity{}
{
}

CRockmanObj::~CRockmanObj()
{
}


void CRockmanObj::tick()
{
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