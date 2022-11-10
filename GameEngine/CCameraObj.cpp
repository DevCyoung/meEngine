#include "pch.h"
#include "CCameraObj.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CEngine.h"
CCameraObj::CCameraObj()
	: m_target(nullptr)
	, m_ColDir(0)
	, m_position{}
	
{
	CreateCollider();

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
	//leftcol

	//if (_pOhter->GetFinalPos().x < m_position.x)
	//{
	//	if ((m_ColDir & (UINT)COL_STATE_DIR::LEFT))
	//	{	
	//		Vector2 scale = GetCollider()->GetScale();
	//		Vector2 otherScale = _pOhter->GetScale();
	//	
	//		m_position.x = _pOhter->GetOwner()->GetPos().x + scale.x / 2 + otherScale.x / 2 - 1;
	//		return;
	//	}
	//}
	//if (_pOhter->GetFinalPos().x > m_position.x)
	//{
	//	if ((m_ColDir & (UINT)COL_STATE_DIR::RIGHT))
	//	{
	//		Vector2 scale = GetCollider()->GetScale();
	//		Vector2 otherScale = _pOhter->GetScale();
	//		m_position.x = _pOhter->GetOwner()->GetPos().x - scale.x / 2 - otherScale.x / 2 + 1;
	//		return;
	//	}
	//}

	//if (_pOhter->GetFinalPos().y < m_position.y)
	//{
	//	if ((m_ColDir & (UINT)COL_STATE_DIR::UP))
	//	{		
	//		Vector2 scale = GetCollider()->GetScale();
	//		Vector2 otherScale = _pOhter->GetScale();
	//	
	//		m_position.y = _pOhter->GetOwner()->GetPos().y + scale.y / 2 + otherScale.y / 2 + 1;
	//		return;
	//	}
	//}
	//if (_pOhter->GetFinalPos().y > m_position.y)
	//{
	//	if ((m_ColDir & (UINT)COL_STATE_DIR::DOWN))
	//	{
	//		Vector2 scale = GetCollider()->GetScale();
	//		Vector2 otherScale = _pOhter->GetScale();
	//		m_position.y = _pOhter->GetOwner()->GetPos().y - scale.y / 2 - otherScale.y / 2 - 1;
	//		return;

	//	}
	//}
	//SetPos(pos);

}

void CCameraObj::OnTriggerExit(CCollider* _pOhter)
{
}

void CCameraObj::OnTriggerEnterUp(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::UP;

	//Vector2 scale = GetCollider()->GetScale();
	//Vector2 otherScale = _pOther->GetScale();

	//Vector2 pos = GetPos();

	//pos.y = _pOther->GetOwner()->GetPos().y + scale.y / 2 + otherScale.y / 2 + 1;
	//SetPos(pos);
}

void CCameraObj::OnTriggerEnterDown(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::DOWN;

	//Vector2 scale = GetCollider()->GetScale();
	//Vector2 otherScale = _pOther->GetScale();

	//Vector2 pos = GetPos();
	//pos.y = _pOther->GetOwner()->GetPos().y - scale.y / 2 - otherScale.y / 2 - 1;
	//SetPos(pos);
}



	
void CCameraObj::OnTriggerEnterLeft(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::LEFT;

	//Vector2 scale = GetCollider()->GetScale();
	//Vector2 otherScale = _pOther->GetScale();

	//Vector2 pos = GetPos();
	//pos.x = _pOther->GetOwner()->GetPos().x + scale.x / 2 + otherScale.x / 2 - 1;
	//SetPos(pos);

}

void CCameraObj::OnTriggerEnterRight(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::RIGHT;

	//Vector2 scale = GetCollider()->GetScale();
	//Vector2 otherScale = _pOther->GetScale();

	//Vector2 pos = GetPos();
	//pos.x = _pOther->GetOwner()->GetPos().x - scale.x / 2 - otherScale.x / 2 + 1;
	//SetPos(pos);
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
