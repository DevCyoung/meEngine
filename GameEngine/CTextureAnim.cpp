#include "pch.h"
#include "CTextureAnim.h"
#include "CTexture.h"
#include "CRenderHelper.h"
#include "CResourceManager.h"
#include "CCamera.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSound.h"

CTextureAnim::CTextureAnim()
	:m_Curtexture(nullptr)
	, m_state(eTextAnimState::START)
	, m_removeDuration(0.f)
	, m_warning(nullptr)
	, m_ready(nullptr)
	, m_frmDuration(0.f)
	, m_isStop(true)
	, m_curVolum(0.f)
{
	m_ready = GETINSTANCE(CResourceManager)->LoadTexture(L"READY", L"ui\\ready.bmp");
	m_warning = GETINSTANCE(CResourceManager)->LoadTexture(L"WARNING", L"ui\\warning.bmp");

	GETINSTANCE(CResourceManager)->LoadSound(L"ready", L"sound\\ready.wav") -> SetVolume(20.f);
	GETINSTANCE(CResourceManager)->LoadSound(L"warning", L"sound\\warning.wav")->SetVolume(20.f);

	m_Curtexture = m_ready;
	m_frmDuration = 0.0055;
	m_curVolum = 20.f;
	
}

CTextureAnim::~CTextureAnim()
{
}


void CTextureAnim::tick()
{
	if (m_state == eTextAnimState::START)
	{
		for (size_t i = 0; i < m_vecTexAnim.size(); i++)
		{
			m_vecTexAnim[i].fDuration += DELTATIME;
		}
	}
	//하나삭제
	if (m_state == eTextAnimState::REMOVE)
	{
		m_curVolum -= 10.f * DELTATIME;

		if (m_curVolum <= 0)
		{
			m_curVolum = 0.f;			
		}

		GETINSTANCE(CResourceManager)->FindSound(L"ready")->SetVolume(m_curVolum);
		GETINSTANCE(CResourceManager)->FindSound(L"warning")->SetVolume(m_curVolum);

		m_removeDuration += DELTATIME;
		if (m_vecTexAnim.size() == 0)
			return;
		m_vecTexAnim.erase(m_vecTexAnim.end() - 1);
	}
}

void CTextureAnim::render(HDC _dc)
{
	Vector2 pos = GetPos();
	pos = GETINSTANCE(CCamera)->GetLook();
	pos = GETINSTANCE(CCamera)->GetRenderPos(pos);
	for (size_t i = 0; i < m_vecTexAnim.size(); i++)
	{

		if (m_vecTexAnim[i].fDestDuration <= m_vecTexAnim[i].fDuration)
		{
			tAnimFrm frm = {};
			frm.vLeftTop = m_vecTexAnim[i].vLeftTop;
			frm.vSize = m_vecTexAnim[i].vSize;
			
			CRenderHelper::StretchRenderOnePer(_dc, m_Curtexture, m_vecTexAnim[i], pos);
			//CRenderHelper::StretchRenderReplaceColor(m_Curtexture->GetDC(), frm, pos, ,false, 0.5f, BACKGROUNDCOLOR, 0xff000000, true, 1.f);
		}
	}
}

#include <algorithm>
#include <random>
void CTextureAnim::AutoSplitRandom(UINT size)
{
	float dutarion = 0.f;

	UINT width = m_Curtexture->Width();
	UINT height = m_Curtexture->Height();
	tTexAnim texAnim = {};



	for (size_t y = 0; y < height / size; y++)
	{
		for (size_t x = 0; x < width / size; x++)
		{
			texAnim.vLeftTop.x = x * size;
			texAnim.vLeftTop.y = y * size;
			texAnim.vDestSize.x = size;
			texAnim.vDestSize.y = size;
			texAnim.vSize.x = size;
			texAnim.vSize.y = size;
			texAnim.fDestDuration = dutarion;
			dutarion += m_frmDuration;
			m_vecTexAnim.push_back(texAnim);


		}
		dutarion = 0.025f;
	}

	std::shuffle(std::begin(m_vecTexAnim), std::end(m_vecTexAnim), std::default_random_engine());
}

void CTextureAnim::Enter()
{
	m_state = eTextAnimState::START;
	m_vecTexAnim.clear();

	if (m_Curtexture == m_ready)
	{
		GETINSTANCE(CResourceManager)->FindSound(L"ready")->Play();
		AutoSplitRandom(15);
	}
	else if (m_Curtexture == m_warning)
	{
		CSound* warningSound = GETINSTANCE(CResourceManager)->FindSound(L"warning");
		warningSound->SetPosition(0.f);
		warningSound->SetVolume(20.f);
		warningSound->PlayToBGM(true);
		m_curVolum = 20.f;
		AutoSplitRandom(13);
	}
	
	
}

void CTextureAnim::Remove()
{
	m_removeDuration = 0.f;
	m_state = eTextAnimState::REMOVE;


	
	if (m_Curtexture == m_ready)
	{
		//GETINSTANCE(CResourceManager)->FindSound(L"ready")->Stop();
		
	}
	else if (m_Curtexture == m_warning)
	{
		//GETINSTANCE(CResourceManager)->FindSound(L"warning")->Stop();
	}
}

