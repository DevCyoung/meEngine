#include "pch.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CKeyManager.h"
#include "CTimeManager.h"

CCamera::CCamera()
	: m_pBlindTex(nullptr)
	, m_fRatio(0.f)
	, m_fAccTime(0.f)
	, m_fMaxTime(0.f)
	, m_fRange(0.f)
	, m_fShakeSpeed(0.f)
	, m_bCamShake(false)
	, m_fShakeDir{}
{
	/*POINT ptResolution = GETINSTANCE(CEngine)->GetWndScreenSize();
	m_pBlindTex = CResMgr::GetInst()->CreateTexture(L"BlindTex", ptResolution.x, ptResolution.y);*/
}

CCamera::~CCamera()
{

}

void CCamera::tick()
{
	//CameraKeyMove();
	Vector2	WndScreenSize = GETINSTANCE(CEngine)->GetWndScreenSize();
	m_vDiff = m_vLook - (WndScreenSize / 2.f);
}


void CCamera::CameraKeyMove(float _fSpeed)
{
	if (IS_INPUT_PRESSED(KEY::W))
	{
		m_vLook.y -= _fSpeed * DELTATIME;
	}
	if (IS_INPUT_PRESSED(KEY::S))
	{
		m_vLook.y += _fSpeed * DELTATIME;
	}
	if (IS_INPUT_PRESSED(KEY::A))
	{
		m_vLook.x -= _fSpeed * DELTATIME;
	}
	if (IS_INPUT_PRESSED(KEY::D))
	{
		m_vLook.x += _fSpeed * DELTATIME;
	}
}

void CCamera::render(HDC _dc)
{
}

void CCamera::FadeOut(float _fTerm)
{
}

void CCamera::FadeIn(float _fTerm)
{
}

void CCamera::CameraShake(float _fRange, float _fSpeed, float _fTerm)
{
}


void CCamera::CameraEffect()
{
}

void CCamera::CameraShake()
{
}
