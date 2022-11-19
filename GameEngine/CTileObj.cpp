#include "pch.h"
#include "CTileObj.h"
#include "CResourceManager.h"
#include "CRenderHelper.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CTimeManager.h"
#include "CResourceManager.h"
#include "CSound.h"
#include "CLevelManager.h"
#include "CRockmanLevel.h"
#include "CKeyManager.h"

CTileObj::CTileObj()
	:m_backgorund(nullptr)
	, m_presStart(nullptr)
	, m_startDelay(0.f)
	, m_isShowStart(true)
	, m_state(TITLESTATE::NONE)
{
	m_backgorund = GETINSTANCE(CResourceManager)->LoadTexture(L"TITLEBACKGROUND", L"ui\\titlebackground.bmp");
	m_presStart = GETINSTANCE(CResourceManager)->LoadTexture(L"PRESSTART", L"ui\\presstart.bmp");
	Vector2 pos = GETINSTANCE(CEngine)->GetWndScreenSize();
	pos /= 2;
	SetPos(pos);
	GETINSTANCE(CCamera)->SetLook(pos);

	//selected.wav
	//sound
	GETINSTANCE(CResourceManager)->LoadSound(L"selected", L"sound\\selected.wav")->SetPosition(0);
	GETINSTANCE(CResourceManager)->LoadSound(L"selected", L"sound\\selected.wav")->SetVolume(18.f)
		;
	//GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->Play();
	
		
}

CTileObj::~CTileObj()
{
}



void CTileObj::tick()
{
	//CRockmanLevel::tick();
	//CGameObject::tick();
	m_startDelay += DELTATIME;

	if (m_startDelay >= 1.1f)
	{
		if (m_isShowStart == true)
		{
			m_isShowStart = false;
		}

		else
		{
			m_isShowStart = true;
		}
		m_startDelay = 0.f;
	}

	if (IS_INPUT_TAB(KEY::SPACE) || IS_INPUT_TAB(KEY::ENTER))
	{
		if (m_state == TITLESTATE::NONE)
		{
			GETINSTANCE(CResourceManager)->FindSound(L"selected")->Play();
			GETINSTANCE(CCamera)->SetTextureType(eFADECOLOR::BLIND);			
			
			CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
			CRockmanLevel* rmLevel = dynamic_cast<CRockmanLevel*>(lv);
			rmLevel->NextLevel();
		}
	}
}

void CTileObj::render(HDC _dc)
{	
	Vector2 pos = GetPos();
	pos.x -= 2.f;
	pos.y -= 2.f;
	CRenderHelper::StretchRenderTextrue(_dc, m_backgorund, pos);

	pos.y += 150.f;
	if (m_isShowStart)
	{
		CRenderHelper::StretchRenderTextrue(_dc, m_presStart, pos);
	}
	
}


