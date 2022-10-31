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
	m_ColDir |= (UINT)COL_STATE_DIR::LEFT;
}

void CZero::OnTriggerEnterRight(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::RIGHT;
}

void CZero::OnTriggerEnterUp(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::UP;
}

void CZero::OnTriggerEnterDown(CCollider* _pOther)
{
	m_ColDir |= (UINT)COL_STATE_DIR::DOWN;
	GetRigidbody()->SetGravity(false);
	GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));
}


void CZero::OnTriggerExitLeft(CCollider* _pOther)
{
	m_ColDir &= ~(UINT)COL_STATE_DIR::LEFT;
}

void CZero::OnTriggerExitRight(CCollider* _pOther)
{
	m_ColDir &= ~(UINT)COL_STATE_DIR::RIGHT;
}

void CZero::OnTriggerExitUp(CCollider* _pOther)
{
	m_ColDir &= ~(UINT)COL_STATE_DIR::UP;
}

void CZero::OnTriggerExitDown(CCollider* _pOther)
{
	m_ColDir &= ~(UINT)COL_STATE_DIR::DOWN;
	GetRigidbody()->SetGravity(true);
	GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));
}
