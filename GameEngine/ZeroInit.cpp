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


void CZero::OnTriggerEnter(CCollider* _pOhter)
{
}

void CZero::OnTriggerStay(CCollider* _pOhter)
{
}

void CZero::OnTriggerExit(CCollider* _pOhter)
{
}



void CZero::DownHitEnter(CLineCollider* _pOhter)
{
	Vector2 inter = _pOhter->GetIntersction();
	//Vector2 pos = Vector2(GetPos().x, inter.y - m_rayDistance + 5);
	/*m_landDir = pos;
	m_landDir.Normalize();
	this->SetPos(pos);*/
	m_curLand = _pOhter;
	m_bisLand = true;
}

void CZero::DownHitStay(CLineCollider* _pOhter)
{
	Vector2 inter = _pOhter->GetIntersction();
	Vector2 pos = Vector2(GetPos().x, inter.y - m_rayDistance+ 1);
	SetPos(pos);
}

void CZero::DownHitExit(CLineCollider* _pOhter)
{
	m_bisLand = false;
}
