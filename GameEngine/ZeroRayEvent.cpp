#include "pch.h"
#include "CZero.h"
#include "CLineColManager.h"
#include "CLineCollider.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CCamera.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResourceManager.h"
#include "CRaycast.h"


#include  "CRigidbody.h"


//최초 Down충돌이 일어난다면....
//무조건 Gravity를 0으로 해야한다.
void CZero::DownHitEnter(CLineCollider* _pOhter)
{
	CRockmanObj::DownHitEnter(_pOhter);
	m_isLineDownState = false;
	/*m_LineDir |= (UINT)COL_STATE_DIR::DOWN;
	m_dirMoveLine = _pOhter;
	if (m_ColDir & (UINT)COL_STATE_DIR::DOWN)
	{
		m_dirMoveLine = _pOhter;
	}
	else
	{
		Vector2 Pos = GetRigidbody()->GetVelocity();
		this->GetRigidbody()->SetGravity(false);
		this->GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));
	}*/
}

void CZero::DownHitStay(CLineCollider* _pOhter)
{
	/*Vector2 inter = _pOhter->GetIntersction();
	Vector2 pos = Vector2(GetPos().x, inter.y -  m_ray.GetVdist() + 1);
	SetPos(pos);*/
}

void CZero::DownHitExit(CLineCollider* _pOhter)
{
	CRockmanObj::DownHitExit(_pOhter);
	m_isLineDownState = true;
	//m_LineDir &= ~(UINT)COL_STATE_DIR::DOWN;
	//m_dirMoveLine = nullptr;
	//Vector2 Pos = GetRigidbody()->GetVelocity();
	//this->GetRigidbody()->SetGravity(true);
	////this->GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));
	//if (m_ColDir & (UINT)COL_STATE_DIR::DOWN)
	//{
	//	//m_vellocity = Vector2(1.f, 1.f);
	//	m_dirMoveLine = nullptr;
	//}
	//else
	//{
	//	/*Vector2 Pos = GetRigidbody()->GetVelocity();
	//	this->GetRigidbody()->SetGravity(false);
	//	this->GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));*/
	//}
}

//raynotuse
#pragma region rayevent

void CZero::UpHitEnter(CLineCollider* _pOhter)
{
}

void CZero::UpHitStay(CLineCollider* _pOhter)
{
}

void CZero::UpHitExit(CLineCollider* _pOhter)
{
}


void CZero::LeftHitEnter(CLineCollider* _pOhter)
{
	/*Vector2 inter = _pOhter->GetIntersction();
	Vector2 pos = Vector2(inter.x + m_fHorizonRayDist, inter.y);
	SetPos(pos);*/
}

void CZero::LeftHitStay(CLineCollider* _pOhter)
{

}

void CZero::LeftHitExit(CLineCollider* _pOhter)
{

}


void CZero::RightHitEnter(CLineCollider* _pOhter)
{
	//Vector2 inter = _pOhter->GetIntersction();
	//Vector2 pos = Vector2(inter.x + m_fHorizonRayDist, inter.y);
	//SetPos(pos);
}

void CZero::RightHitStay(CLineCollider* _pOhter)
{
}

void CZero::RightHitExit(CLineCollider* _pOhter)
{
}

#pragma endregion
