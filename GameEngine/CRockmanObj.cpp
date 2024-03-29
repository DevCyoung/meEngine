#include "pch.h"
#include "CRockmanObj.h"
#include "CLineColManager.h"
#include "CLineCollider.h"
#include "CLine.h"
#include "CTimeManager.h"
#include "CRigidbody.h"


bool CRockmanObj::RightColState()
{
	if (nullptr == GetCollider())
		return false;
	if (m_ColDir & (UINT)COL_STATE_DIR::RIGHT)
		return true;
	return false;
}

bool CRockmanObj::LeftColState()
{
	if (nullptr == GetCollider())
		return false;
	if (m_ColDir & (UINT)COL_STATE_DIR::LEFT)
		return true;
	return false;
}

bool CRockmanObj::DownColState()
{
	if (nullptr == GetCollider())
		return false;
	if ((m_ColDir & (UINT)COL_STATE_DIR::DOWN) || (m_LineDir & (UINT)COL_STATE_DIR::DOWN))
		return true;
	return false;
}

bool CRockmanObj::UpColState()
{
	if (nullptr == GetCollider())
		return false;
	if (m_ColDir & (UINT)COL_STATE_DIR::UP)
		return true;
	return false;
}


CRockmanObj::CRockmanObj()
	:m_ColDir(0)
	, m_sponType(MONSETER_TYPE::NONE)
	, m_LineDir(0)
	, m_vellocity{}
	, m_downRay(nullptr)
	, m_curBoxWall(nullptr)
	, m_bColInterPolate(true)
	, m_isDownExitState(true)
	, m_isLineDownState(true)
	, m_isBoxCollideDownState(false)
	, m_isGravity(false)
	, m_gravityAceel(0.f)
	, m_curGravity(0.f)
	, m_damagedState(DAMAGED_STATE::NONE)
	, m_hp(0)

	
{
	m_gravityAceel = 1.95f;
}

CRockmanObj::CRockmanObj(const CRockmanObj& _other)
	: CGameObject(_other)
	, m_sponType(MONSETER_TYPE::NONE)
	, m_ColDir(0)
	, m_LineDir(0)
	, m_vellocity{}
	, m_downRay(nullptr) //여기서문제생길수도있음
	, m_bColInterPolate(_other.m_bColInterPolate)
	, m_isDownExitState(true)
	, m_isLineDownState(true)
	, m_curBoxWall(nullptr)
	, m_isBoxCollideDownState(false)
	, m_isGravity(false)
	, m_gravityAceel(_other.m_gravityAceel)
	, m_curGravity(0.f)	
	, m_hp(0)


{
	if (_other.m_downRay != nullptr)
	{
		CreateLineCollider();
		float dist = 50.f;
		if (GetCollider() != nullptr)
		{
			dist = GetCollider()->GetScale().y;
		}

		GetLineCollider()->SetRaycast(GetPos(), Vector2(0.f, 1.f), Vector2(0.f, 0.f), _other.m_downRay->GetLineCollider()->m_distance);
	}
}

CRockmanObj::~CRockmanObj()
{
	if (nullptr != m_downRay)
	{
		delete m_downRay;
	}
}
void CRockmanObj::CreateRockmanRrigidbody()
{
	CreateRigidbody();
	GetRigidbody()->SetGravityAccel(1950.f);
	GetRigidbody()->SetGravity(true);
	GetRigidbody()->SetFrictionScale(12.f);

	CreateLineCollider();
	GetLineCollider()->SetEnterEvent((DELEGATECOL)&CRockmanObj::DownHitEnter, this);
	GetLineCollider()->SetExitEvent((DELEGATECOL)&CRockmanObj::DownHitExit, this);
	GetLineCollider()->SetRaycast(Vector2(-1000.f, -1000.f), Vector2(0.f, 1.f), Vector2(0.f, 0.f), GetCollider()->GetScale().y / 2.f);
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

	if (nullptr != GetRigidbody())
	{
		if (GetCollision() == true)
		{
			if (DownColState() == false)
			{
				GetRigidbody()->SetGravity(true);
			}
			else
			{
				GetRigidbody()->SetGravity(false);
			}
		}

	

		Vector2 velo = GetRigidbody()->GetVelocity();
		if (abs(velo.x) > 0.001f)
		{
			if (velo.x < 0.01f)
			{
				SetFlipX(false);
			}
			if (velo.x > 0.01f)
			{
				SetFlipX(true);
			}



		}
		float d = GetRigidbody()->GetGravityScale();
		if (GetRigidbody()->GetGravityScale() > 1.f)
		{
			SetFilpY(false);
		}
		else if (GetRigidbody()->GetGravityScale() < 1.f)
		{
			SetFilpY(true);
		}
	}

	if (nullptr != m_curLineLand)
	{
		Vector2 p1 = m_curLineLand->GetP1();
		Vector2 p2 = m_curLineLand->GetP2();
		Vector2 pos = GetPos();
		pos.y = ((p2.y - p1.y) / (p2.x - p1.x)) * (pos.x - p1.x) + p1.y - GetLineCollider()->GetLineCollider()->m_distance + 1;
		SetPos(pos);
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
	m_isBoxCollideDownState = true;
}

void CRockmanObj::OnTriggerStay(CCollider* _pOhter)
{
}

void CRockmanObj::OnTriggerExit(CCollider* _pOhter)
{
	m_isBoxCollideDownState = false;
}




void CRockmanObj::OnTriggerEnterUp(CCollider* _pOther)
{

	m_ColDir |= (UINT)COL_STATE_DIR::UP;
	if (GetCollision() == false)
		return;

	if (nullptr == GetRigidbody())
		return;

	Vector2 scale = GetCollider()->GetScale();
	Vector2 otherScale = _pOther->GetScale();

	Vector2 pos = GetPos();

	pos.y = _pOther->GetOwner()->GetPos().y + scale.y / 2 + otherScale.y / 2 + 12;
	SetPos(pos);

	Vector2 velo = GetRigidbody()->GetVelocity();
	velo.y = 0;
	GetRigidbody()->SetVelocity(velo);

}

void CRockmanObj::OnTriggerEnterDown(CCollider* _pOther)
{
	
	m_ColDir |= (UINT)COL_STATE_DIR::DOWN;
	if (GetCollision() == false)
		return;

	if (nullptr == GetRigidbody())
		return;

	m_isDownExitState = false;
	Vector2 scale = GetCollider()->GetScale();
	Vector2 otherScale = _pOther->GetScale();

	Vector2 pos = GetPos();
	pos.y = _pOther->GetOwner()->GetPos().y - scale.y / 2 - otherScale.y / 2 + 1;
	SetPos(pos);

	GetRigidbody()->SetGravity(false);
	Vector2 velo = GetRigidbody()->GetVelocity();
	velo.y = 0;
	GetRigidbody()->SetVelocity(velo);

}
void CRockmanObj::OnTriggerEnterLeft(CCollider* _pOther)
{

	m_ColDir |= (UINT)COL_STATE_DIR::LEFT;
	if (GetCollision() == false)
		return;
	if (nullptr == GetRigidbody())
		return;

	Vector2 scale = GetCollider()->GetScale();
	Vector2 otherScale = _pOther->GetScale();

	Vector2 pos = GetPos();
	pos.x = _pOther->GetOwner()->GetPos().x + scale.x / 2 + otherScale.x / 2 - 1;
	SetPos(pos);

	Vector2 velo = GetRigidbody()->GetVelocity();
	velo.x = 0;
	GetRigidbody()->SetVelocity(velo);
}

void CRockmanObj::OnTriggerEnterRight(CCollider* _pOther)
{
	
	m_ColDir |= (UINT)COL_STATE_DIR::RIGHT;
	if (GetCollision() == false)
		return;
	if (nullptr == GetRigidbody())
		return;

	Vector2 scale = GetCollider()->GetScale();
	Vector2 otherScale = _pOther->GetScale();

	Vector2 pos = GetPos();
	pos.x = _pOther->GetOwner()->GetPos().x - scale.x / 2 - otherScale.x / 2 + 1;
	SetPos(pos);

	Vector2 velo = GetRigidbody()->GetVelocity();
	velo.x = 0;
	GetRigidbody()->SetVelocity(velo);
}

void CRockmanObj::DownHitEnter(CLineCollider* _pOhter)
{

	m_LineDir |= (UINT)COL_STATE_DIR::DOWN;
	if (GetCollision() == false)
		return;
	m_curLineLand = _pOhter;

}
void CRockmanObj::DownHitExit(CLineCollider* _pOhter)
{
	m_LineDir &= ~(UINT)COL_STATE_DIR::DOWN;
	m_curLineLand = nullptr;
}


void CRockmanObj::OnTriggerExitUp(CCollider* _pOther)
{
	m_ColDir &= ~(UINT)COL_STATE_DIR::UP;

}

void CRockmanObj::OnTriggerExitDown(CCollider* _pOther)
{

	if (GetCollider()->GetWallDirState(COLLIDE_DIR::DOWN) > 0)
	{
		return;
	}

	m_ColDir &= ~(UINT)COL_STATE_DIR::DOWN;
	if (GetCollision() == false)
		return;
	//m_isDownExitState = true;
	if (nullptr == GetRigidbody())
		return;

	GetRigidbody()->SetGravity(true);
	Vector2 velo = GetRigidbody()->GetVelocity();
	velo.y = 0;
	GetRigidbody()->SetVelocity(velo);
}

void CRockmanObj::OnTriggerExitLeft(CCollider* _pOther)
{
	if (GetCollider()->GetWallDirState(COLLIDE_DIR::LEFT) > 0)
	{
		return;
	}

	m_ColDir &= ~(UINT)COL_STATE_DIR::LEFT;
	if (GetCollision() == false)
		return;
	if (nullptr == GetRigidbody())
		return;

	if (nullptr == GetRigidbody())
		return;
}

void CRockmanObj::OnTriggerExitRight(CCollider* _pOther)
{
	if (GetCollider()->GetWallDirState(COLLIDE_DIR::RIGHT) > 0)
	{
		return;
	}
	m_ColDir &= ~(UINT)COL_STATE_DIR::RIGHT;
	if (GetCollision() == false)
		return;
	if (nullptr == GetRigidbody())
		return;

	if (nullptr == GetRigidbody())
		return;

	
}






void CRockmanObj::DownHitStay(CLineCollider* _pOhter)
{

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