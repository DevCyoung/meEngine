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


void CZero::OnTriggerEnter(CCollider* _pOther)
{
}

void CZero::OnTriggerStay(CCollider* _pOhter)
{
}

void CZero::OnTriggerExit(CCollider* _pOther)
{
}

void CZero::OnTriggerEnterLeft(CCollider* _pOther)
{
	CRockmanObj::OnTriggerEnterLeft(_pOther);
	Vector2 vPos = GetRigidbody()->GetVelocity();
	GetRigidbody()->SetVelocity(Vector2(0.f, vPos.y));
}

void CZero::OnTriggerEnterRight(CCollider* _pOther)
{
	CRockmanObj::OnTriggerEnterRight(_pOther);
	Vector2 vPos = GetRigidbody()->GetVelocity();
	GetRigidbody()->SetVelocity(Vector2(0.f, vPos.y));
}

void CZero::OnTriggerEnterUp(CCollider* _pOther)
{
	CRockmanObj::OnTriggerEnterUp(_pOther);
	GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));
}

void CZero::OnTriggerEnterDown(CCollider* _pOther)
{
	CRockmanObj::OnTriggerEnterDown(_pOther);
	GetRigidbody()->SetGravity(false);
	GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));
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
	CRockmanObj::OnTriggerExitDown(_pOther);
	GetRigidbody()->SetGravity(true);
	//GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));
}
