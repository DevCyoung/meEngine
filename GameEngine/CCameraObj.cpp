#include "pch.h"
#include "CCameraObj.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CEngine.h"
#include "CZero.h"

CCameraObj::CCameraObj()
	: m_target(nullptr)
	, m_ColDir(0)
	, m_position{}
	
{
	CreateCollider();
	SetTag(LAYER::CAMERA);
	GetCollider()->SetScale(GETINSTANCE(CEngine)->GetWndScreenSize());
}

CCameraObj::CCameraObj(const CCameraObj& _other)
	: m_target(nullptr)
	, m_ColDir(0)
	, m_position{}
{
}

CCameraObj::~CCameraObj()
{
}


void CCameraObj::tick()
{
	if (nullptr == m_target)
	{
		return;
	}

	Vector2 pos = m_target->GetPos();
	
	SetPos(pos);
	m_position = GetPos();
}

void CCameraObj::fixed_tick()
{
	if (nullptr == m_target)
	{
		return;
	}
	

	GETINSTANCE(CCamera)->SetLook(m_position);
}

void CCameraObj::OnTriggerEnter(CCollider* _pOhter)
{
}

void CCameraObj::OnTriggerStay(CCollider* _pOhter)
{	
}

void CCameraObj::OnTriggerExit(CCollider* _pOhter)
{
}

void CCameraObj::OnTriggerEnterUp(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::UP;
}

void CCameraObj::OnTriggerEnterDown(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::DOWN;
}



	
void CCameraObj::OnTriggerEnterLeft(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::LEFT;
}

void CCameraObj::OnTriggerEnterRight(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::RIGHT;

}


void CCameraObj::OnTriggerExitLeft(CCollider* _pOther)
{
	m_ColDir &= ~(UINT)COL_STATE_DIR::LEFT;
}

void CCameraObj::OnTriggerExitRight(CCollider* _pOther)
{
	m_ColDir &= ~(UINT)COL_STATE_DIR::RIGHT;
}

void CCameraObj::OnTriggerExitUp(CCollider* _pOther)
{
	m_ColDir &= ~(UINT)COL_STATE_DIR::UP;
}

void CCameraObj::OnTriggerExitDown(CCollider* _pOther)
{
	m_ColDir &= ~(UINT)COL_STATE_DIR::DOWN;
}
