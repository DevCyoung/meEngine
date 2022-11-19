#include "pch.h"
#include "CRockmanManager.h"

#include "CTimeManager.h"
#include "CEffectManager.h"
#include "CResourceManager.h"
#include "CSound.h"
#include "CCamera.h"
#include "CZero.h"

#include "CLevelManager.h"


#include"CAnimator.h"
#include "CRockmanLevel.h"

CRockmanManager::CRockmanManager()
	:m_event(ROCKEVENT::NONE)
	, m_stateDelay(0.f)
	, m_tartget{}
	, m_offset{}
	, m_fadeColor(eFADECOLOR::BLIND)
	, m_whiteDelay(0.f)
	, m_zeroDelay(0.f)
	, m_dumyDleay(0.f)
	, m_isWhite(false)
	, m_nextLevel{}
	, m_backGroundsound(nullptr)
	, m_zeroLife(0)
	, m_zeroCurHP(0)
	, m_zeroMaxHp(0)
{
	m_offset.x = 10.f;
	m_offset.y = 10.f;


	GETINSTANCE(CResourceManager)->LoadSound(L"finishboomting", L"sound\\finishboomting.wav")->SetVolume(89.f);
	GETINSTANCE(CResourceManager)->LoadSound(L"finishwin", L"sound\\finishwin.wav")->SetVolume(89.f);
	
	m_backGroundsound = GETINSTANCE(CResourceManager)->LoadSound(L"cyberbackground1", L"sound\\cyberspacebackground.wav");
	m_backGroundsound->SetVolume(16.f);
	//m_backGroundsound->PlayToBGM(true);
	//m_backGroundsound->SetVolume(16.f);	
	//backGroundsound->Stop();

	m_zeroMaxHp = 10;
	m_zeroCurHP = 2;
	m_zeroLife = 2;
}

CRockmanManager::~CRockmanManager()
{

}

void CRockmanManager::tick()
{
	switch (m_event)
	{
	case ROCKEVENT::BOSSDIE:
	{
		m_stateDelay += DELTATIME;
		m_whiteDelay += DELTATIME;
		if (m_stateDelay > 0.09f)
		{
			Vector2 pos = m_tartget;

			Vector2 offset = {};


			if (m_offset.x > 350)
			{
				m_offset.x = 350;
			}
			if (m_offset.y > 350)
			{
				m_offset.y = 350;
			}
			

			offset.x = (int)(rand() % (int)m_offset.x);
			offset.y = (int)(rand() % (int)m_offset.y);

			if (rand() % 2 == 0)
			{
				offset.x *= -1;
			}
			if (rand() % 2 == 1)
			{
				offset.y *= -1;
			}
			m_offset.x += 30.f;
			m_offset.y += 30.f;


			pos += offset;
			
			GETINSTANCE(CEffectManager)->OnShootPlay(EFFECT_TYPE::BOOMRED, pos, false);
			m_stateDelay = 0.f;
		}

		if (m_whiteDelay >= 2.2f && m_isWhite == false)
		{
			m_isWhite = true;
			GETINSTANCE(CCamera)->FadeOut(2.3f);
		}

		if (m_whiteDelay >= 5.9f && m_isWhite == true)
		{
			m_event = ROCKEVENT::WIN;
			m_whiteDelay = 0.f;
			m_stateDelay = 0.f;
			GETINSTANCE(CCamera)->FadeIn(2.3f);
		}
	}
		break;
	case ROCKEVENT::WIN:
		m_stateDelay += DELTATIME;
		if (m_stateDelay >= 2.7f)
		{
			GETINSTANCE(CResourceManager)->FindSound(L"finishwin")->Play();
			m_event = ROCKEVENT::ZEROGOOD;
			m_stateDelay = 0.f;
		}
		break;
	case ROCKEVENT::ZEROGOOD:
		m_stateDelay += DELTATIME;
		if (m_stateDelay >= 7.0f)
		{
			//GETINSTANCE(CResourceManager)->FindSound(L"finishwin")->Play();

			CZero* zero = GETINSTANCE(CLevelManager)->GetPlayerObject();
			zero->GetAnimator()->Play(L"GOOD", false);
			m_event = ROCKEVENT::RETURNHONE;
			m_stateDelay = 0.f;
		}
		break;
	case ROCKEVENT::RETURNHONE:
		m_stateDelay += DELTATIME;
		if (m_stateDelay >= 1.1f)
		{			
			CZero* zero = GETINSTANCE(CLevelManager)->GetPlayerObject();			
			zero->SetState(PLAYER_STATE::RETURNREADY);
			CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
			CRockmanLevel* rmLevel = dynamic_cast<CRockmanLevel*>(lv);
			rmLevel->m_cam->m_isFollow = false;
			m_event = ROCKEVENT::ZERORETURN;			
			m_stateDelay = 0.f;			
		}		
		break;
	case ROCKEVENT::ZERORETURN:
		m_stateDelay += DELTATIME;
		if (m_stateDelay >= 0.65f)
		{
			GETINSTANCE(CCamera)->SetTextureType(eFADECOLOR::BLIND);
			CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
			CRockmanLevel* rmLevel = dynamic_cast<CRockmanLevel*>(lv);
			rmLevel->NextLevel();
			//GETINSTANCE(CCamera)->FadeOut(0.8f);
			m_event = ROCKEVENT::NONE;
			m_stateDelay = 0.f;
			m_whiteDelay = 0.f;

			m_offset.x = 10.f;
			m_offset.y = 10.f;

			m_isWhite = false;
		}
	case ROCKEVENT::FADEEXIT:
		break;

	case ROCKEVENT::ZERODIE:
		m_zeroDelay += DELTATIME;
		m_dumyDleay += DELTATIME;

		if (m_dumyDleay >= 2.f)
		{
			m_zeroDelay = 0.f;
			m_dumyDleay = 0.f;
			m_event = ROCKEVENT::TODUMMYLEVEL;
			//GETINSTANCE(CCamera)->FadeOut(1.f);
			GETINSTANCE(CCamera)->SetTextureType(eFADECOLOR::BLIND);
			CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
			CRockmanLevel* rmLevel = dynamic_cast<CRockmanLevel*>(lv);
			GETINSTANCE(CRockmanManager)->m_backGroundsound->Stop();
			GETINSTANCE(CRockmanManager)->m_backGroundsound->SetPosition(0.f);

			if (GETINSTANCE(CRockmanManager)->m_zeroLife < 0)
			{
				rmLevel->NextLevel(LEVEL_TYPE::TITLE);
			}
			else
			{
				rmLevel->NextLevel(rmLevel->m_curLevel);
			}
			
			return;
		}
		if (m_zeroDelay >= 0.09f)
		{
			CZero* zero = GETINSTANCE(CLevelManager)->GetPlayerObject();
			for (size_t i = 0; i < 3; i++)
			{
				GETINSTANCE(CEffectManager)->OnShootPlay(EFFECT_TYPE::DIEBALL, zero->GetPos(), false);
			}			
			m_zeroDelay = 0.f;
		}
		break;
	case ROCKEVENT::TODUMMYLEVEL:
		break;
	}
}

void CRockmanManager::BossDieBoom(Vector2 monsterPos)
{

}

void CRockmanManager::SetEvent(ROCKEVENT _event)
{
	m_event = _event;	
	m_stateDelay = 1.f;
	m_zeroDelay = 0.f;
	m_dumyDleay = 0.f;

	switch (m_event)
	{
	case ROCKEVENT::BOSSDIE:
		GETINSTANCE(CResourceManager)->FindSound(L"finishboomting")->Play();
		GETINSTANCE(CCamera)->SetTextureType(eFADECOLOR::WHITE);

		break;
	case ROCKEVENT::RETURNHONE:
		break;
	
	}
}
