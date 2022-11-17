#include "pch.h"
#include "CCameraObj.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CEngine.h"
#include "CZero.h"
#include "CTimeManager.h"

CCameraObj::CCameraObj()
	: m_target(nullptr)
	, m_ColDir(0)
	, m_position{}
	, m_isFollow(true)
	, m_delay(1.f)
	, m_diff{}
{
	CreateCollider();
	SetTag(LAYER::CAMERA);
	GetCollider()->SetScale(GETINSTANCE(CEngine)->GetWndScreenSize());
}

CCameraObj::CCameraObj(const CCameraObj& _other)
	: m_target(nullptr)
	, m_ColDir(0)
	, m_position{}
	, m_isFollow(true)
	, m_delay(1.f)
	, m_diff{}
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

	if (m_target->GetState() == PLAYER_STATE::RETURN || m_target->GetState() == PLAYER_STATE::ENTER || m_target->GetState() == PLAYER_STATE::RETURNREADY)
	{
		return;
	}

	if (m_isFollow == false)
	{
		return;
	}

	Vector2 pos = m_target->GetPos();
	SetPos(pos);
	m_diff = m_target->GetPos() - GetPos();
	m_position = GetPos();	

}

void CCameraObj::fixed_tick()
{
	if (nullptr == m_target)
	{
		return;
	}

	if (m_target->GetState() == PLAYER_STATE::RETURN || m_target->GetState() == PLAYER_STATE::ENTER || m_target->GetState() == PLAYER_STATE::RETURNREADY)
	{
		return;
	}

	if (m_isFollow == false)
	{
		//m_position.x += 100.f * DELTATIME;
		//return;
	}
	GETINSTANCE(CCamera)->SetLook(m_position);

	//if (m_delay >= 0.9f)
	//{
	//	GETINSTANCE(CCamera)->SetLook(m_position);
	//}
	//else
	//{
	//	Vector2 pos = m_target->GetPos() + m_diff * DELTATIME;
	//	GETINSTANCE(CCamera)->SetLook(pos);
	//}

	
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
