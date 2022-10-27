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




void CZero::EventInit()
{
	/*m_fVerticalRayDist = 70.f;
	m_fHorizonRayDist = 35.f;
	GETINSTANCE(CLineColManager)->CreateRaycast(m_ray, Vector2(m_fHorizonRayDist, m_fVerticalRayDist), Vector2(m_fHorizonRayDist, m_fVerticalRayDist));*/

	/*m_downRay   = GETINSTANCE(CLineColManager)->CreateLine(Vector2(0.f, 0.f), Vector2(0.f,  m_fVerticalRayDist), LINELAYER::PLAYER);
	m_upRay		= GETINSTANCE(CLineColManager)->CreateLine(Vector2(0.f, 0.f), Vector2(0.f, -m_fVerticalRayDist), LINELAYER::PLAYER);


	m_leftRay   = GETINSTANCE(CLineColManager)->CreateLine(Vector2(0.f, 0.f), Vector2(-m_fHorizonRayDist, 0.f ), LINELAYER::PLAYER);
	m_rightRay  = GETINSTANCE(CLineColManager)->CreateLine(Vector2(0.f, 0.f), Vector2(m_fHorizonRayDist, 0.f ), LINELAYER::PLAYER);




	m_downLandCheck = GETINSTANCE(CLineColManager)->CreateLine(Vector2(0.f, 0.f), Vector2(0.f, m_fVerticalRayDist), LINELAYER::PLAYER);


	m_downRay->SetStayEvent((DELEGATECOL)&CZero::DownHitStay, this);
	m_downRay->SetEnterEvent((DELEGATECOL)&CZero::DownHitEnter, this);

	m_leftRay->SetStayEvent((DELEGATECOL)&CZero::LeftHitStay, this);
	m_leftRay->SetEnterEvent((DELEGATECOL)& CZero::LeftHitEnter, this);*/

	/*m_ray.GetLineCol(RAY_TYPE::DOWN_RIGHT)->SetStayEvent((DELEGATECOL)&CZero::DownHitStay, this);
	m_ray.GetLineCol(RAY_TYPE::DOWN_LEFT)->SetStayEvent((DELEGATECOL)&CZero::DownHitStay, this);*/

	GETINSTANCE(CLineColManager)->AddFixedTick((DELEGATE)&CZero::fixed_tick, this);

	m_ray.GetLineCol(RAY_TYPE::DOWN)->SetEnterEvent((DELEGATECOL)&CZero::DownHitEnter, this);
	m_ray.GetLineCol(RAY_TYPE::DOWN_LEFT)->SetEnterEvent((DELEGATECOL)&CZero::DownHitEnter, this);
	m_ray.GetLineCol(RAY_TYPE::DOWN_RIGHT)->SetEnterEvent((DELEGATECOL)&CZero::DownHitEnter, this);


	m_ray.GetLineCol(RAY_TYPE::DOWN)->SetExitEvent((DELEGATECOL)&CZero::DownHitExit, this);
	m_ray.GetLineCol(RAY_TYPE::DOWN_LEFT)->SetExitEvent((DELEGATECOL)&CZero::DownHitExit, this);
	m_ray.GetLineCol(RAY_TYPE::DOWN_RIGHT)->SetExitEvent((DELEGATECOL)&CZero::DownHitExit, this);


	//m_ray.GetLineCol(RAY_TYPE::DOWN_LEFT)->SetStayEvent((DELEGATECOL)&CZero::DownHitStay, this);

}

void CZero::EventTick()
{
	Vector2 pos = this->GetPos();/*
	m_downRay->TranslateSetPos(pos);
	m_leftRay->TranslateSetPos(pos);
	m_upRay->TranslateSetPos(pos);
	m_rightRay->TranslateSetPos(pos);*/
	m_ray.TranslateSetPos(pos);

	

}


