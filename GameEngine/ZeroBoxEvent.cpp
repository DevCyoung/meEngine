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

#include "CRigidbody.h"
#include "CPlayerController.h"
#include "CPlayerAnimEvent.h"

void CZero::OnTriggerEnter(CCollider* _pOther)
{
	CRockmanObj::OnTriggerEnter(_pOther);


}

void CZero::OnTriggerStay(CCollider* _pOther)
{
	CRockmanObj::OnTriggerStay(_pOther);
}

void CZero::OnTriggerExit(CCollider* _pOther)
{
	CRockmanObj::OnTriggerExit(_pOther);
}



void CZero::OnTriggerEnterLeft(CCollider* _pOther)
{
	CRockmanObj::OnTriggerEnterLeft(_pOther);

	/*Vector2 vPos = GetRigidbody()->GetVelocity();
	GetRigidbody()->SetVelocity(Vector2(0.f, vPos.y));*/
}

void CZero::OnTriggerEnterRight(CCollider* _pOther)
{
	CRockmanObj::OnTriggerEnterRight(_pOther);

	/*Vector2 vPos = GetRigidbody()->GetVelocity();
	GetRigidbody()->SetVelocity(Vector2(0.f, vPos.y));*/
}

void CZero::OnTriggerEnterUp(CCollider* _pOther)

{
	CRockmanObj::OnTriggerEnterUp(_pOther);

	Vector2 scale = _pOther->GetScale();
	Vector2 meScale = GetCollider()->GetScale();

	float dis = scale.y / 2 + meScale.y / 2 - 20.f;

	
	//GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));
}

void CZero::OnTriggerEnterDown(CCollider* _pOther)
{

	CRockmanObj::OnTriggerEnterDown(_pOther);
	m_dirMoveBox = _pOther;

	/*GetRigidbody()->SetGravity(false);
	GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));*/
	
	/*Vector2 vPos = GetPos();
	float disY = _pOther->GetFinalPos().y - _pOther->GetScale().y / 2 - 49.f;
	vPos.y = disY;
	SetPos(vPos);*/
}


void CZero::OnTriggerExitLeft(CCollider* _pOther)
{
	CRockmanObj::OnTriggerExitLeft(_pOther);
}

void CZero::OnTriggerExitRight(CCollider* _pOther)
{
	CRockmanObj::OnTriggerExitRight(_pOther);
}

void CZero::OnTriggerExitUp(CCollider* _pOther)
{
	CRockmanObj::OnTriggerExitUp(_pOther);
}

void CZero::OnTriggerExitDown(CCollider* _pOther)
{
	//m_dirMoveBox = nullptr;
	CRockmanObj::OnTriggerExitDown(_pOther);
	//GetRigidbody()->SetGravity(true);
	//GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));
}

void CZero::CreatePlayerController()
{
	m_playerController = new CPlayerController(this);
}

void CZero::CreateAnimEvent()
{
	m_animEvent = new CPlayerAnimEvent(this);
}
