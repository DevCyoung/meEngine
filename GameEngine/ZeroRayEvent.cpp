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
void CZero::DownHitEnter(CLineCollider* _pOhter)
{
	this->GetRigidbody()->SetGravity(false);
	this->GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));
}

void CZero::DownHitStay(CLineCollider* _pOhter)
{
	
	/*Vector2 inter = _pOhter->GetIntersction();
	Vector2 pos = Vector2(GetPos().x, inter.y -  m_ray.GetVdist() + 1);
	SetPos(pos);*/

}

void CZero::DownHitExit(CLineCollider* _pOhter)
{
	this->GetRigidbody()->SetGravity(true);
}


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
	Vector2 inter = _pOhter->GetIntersction();
	Vector2 pos = Vector2(inter.x + m_fHorizonRayDist, inter.y);
	SetPos(pos);
}

void CZero::RightHitStay(CLineCollider* _pOhter)
{
}

void CZero::RightHitExit(CLineCollider* _pOhter)
{
}