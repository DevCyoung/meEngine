#include "pch.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CTexture.h"
#include "CResourceManager.h"

CCamera::CCamera()
	: m_pBlindTex(nullptr)
	, m_pWhiteTex(nullptr)
	, m_pRedTex(nullptr)
	, m_pCurTex(nullptr)
	, m_fRatio(0.f)
	, m_fAccTime(0.f)
	, m_fMaxTime(0.f)
	, m_fRange(0.f)
	, m_fShakeSpeed(0.f)
	, m_bCamShake(false)
	, m_fShakeDir{}
	, m_cam(nullptr)
{
	POINT ptResolution = GETINSTANCE(CEngine)->GetWndScreenSize();

	

	m_pBlindTex = GETINSTANCE(CResourceManager)->CreateTexture(L"BlindTex", ptResolution.x, ptResolution.y);
	m_pRedTex = GETINSTANCE(CResourceManager)->CreateTexture(L"RedTex", ptResolution.x, ptResolution.y, RGB(255, 0, 0));
	m_pWhiteTex = GETINSTANCE(CResourceManager)->CreateTexture(L"whiteTex", ptResolution.x, ptResolution.y, RGB(255, 255, 255));
	m_pCurTex = m_pBlindTex;
}
CCamera::~CCamera()
{

}
void CCamera::Settarget(CZero* obj)
{
	m_cam->SetTarget(obj);
}

void CCamera::SetTextureType(eFADECOLOR color)
{
	switch (color)
	{
	case eFADECOLOR::BLIND:
		m_pCurTex = m_pBlindTex;
		break;
	case eFADECOLOR::WARNING:
		m_pCurTex = m_pRedTex;
		break;
	case eFADECOLOR::WHITE:
		m_pCurTex = m_pWhiteTex;
		break;
	}
}

void CCamera::tick()
{
	//CameraKeyMove();
	Vector2	WndScreenSize = GETINSTANCE(CEngine)->GetWndScreenSize();
	m_vDiff = m_vLook - (WndScreenSize / 2.f);


	// 카메라 렌더링 효과
	CameraEffect();

	// 카메라 흔들림 효과
	CameraShake();
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

Vector2 CCamera::GetRealMousePos()
{
	Vector2 vPos = GETINSTANCE(CKeyManager)->GetMousePos();
	return GetRealPos(vPos);
}
void CCamera::render(HDC _dc)
{
	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = 0;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255.f * m_fRatio);

	if (m_fRatio < 0.001f)
		return;

	AlphaBlend(_dc
		, 0, 0
		, m_pCurTex->Width()
		, m_pCurTex->Height()
		, m_pCurTex->GetDC()
		, 0, 0
		, m_pCurTex->Width()
		, m_pCurTex->Height()
		, tBlend);
}

void CCamera::FadeOut(float _fTerm)
{
	tCamEffect effect = {};
	effect.m_eCurEffect = CAMERA_EFFECT::FADE_OUT;
	effect.m_fAccTime = 0.f;
	effect.m_fMaxTime = _fTerm;
	effect.m_fdestRatioper = 1.f;

	m_CamEffectList.push_back(effect);
}

void CCamera::FadeOut(float _fTerm, float _destRatio)
{
	tCamEffect effect = {};
	effect.m_eCurEffect = CAMERA_EFFECT::FADE_OUT;
	effect.m_fAccTime = 0.f;
	effect.m_fMaxTime = _fTerm;
	effect.m_fdestRatioper = _destRatio;

	m_CamEffectList.push_back(effect);
}

void CCamera::FadeIn(float _fTerm)
{
	tCamEffect effect = {};
	effect.m_eCurEffect = CAMERA_EFFECT::FADE_IN;
	effect.m_fAccTime = 0.f;
	effect.m_fMaxTime = _fTerm;
	effect.m_fdestRatioper = 1.f;

	m_CamEffectList.push_back(effect);
}

void CCamera::FadeIn(float _fTerm, float _destRatio)
{
	tCamEffect effect = {};
	effect.m_eCurEffect = CAMERA_EFFECT::FADE_IN;
	effect.m_fAccTime = 0.f;
	effect.m_fMaxTime = _fTerm;
	effect.m_fdestRatioper = _destRatio;

	m_CamEffectList.push_back(effect);
}

void CCamera::CameraShake(float _fRange, float _fShakeSpeed, float _fTerm)
{
	m_fAccTime = 0.f;
	m_fMaxTime = _fTerm;
	m_fRange = _fRange;
	m_fShakeSpeed = _fShakeSpeed;
	m_fShakeDir = 1.f;
	m_bCamShake = true;
}




void CCamera::CameraEffect()
{
	if (m_CamEffectList.empty())
		return;

	tCamEffect& effect = m_CamEffectList.front();

	effect.m_fAccTime += DELTATIME;

	if (effect.m_fMaxTime <= effect.m_fAccTime)
	{
		m_CamEffectList.pop_front();
		return;
	}

	m_fRatio = effect.m_fAccTime / effect.m_fMaxTime;
	if (CAMERA_EFFECT::FADE_IN == effect.m_eCurEffect)
		m_fRatio = 1.f - m_fRatio;
	m_fRatio *= effect.m_fdestRatioper;
}

void CCamera::CameraShake()
{
	if (!m_bCamShake)
		return;

	m_fAccTime += DELTATIME;

	if (m_fMaxTime <= m_fAccTime)
	{
		m_bCamShake = false;
		m_vOffset = Vector2(0.f, 0.f);
	}

	m_vOffset.y += DELTATIME * m_fShakeSpeed * m_fShakeDir;

	if (m_fRange < fabsf(m_vOffset.y))
	{
		m_vOffset.y = m_fRange * m_fShakeDir;
		m_fShakeDir *= -1;
	}
}
