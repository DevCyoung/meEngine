#include "pch.h"
#include "CLevelManager.h"
#include "CEventManager.h"
	
#include "CTitleLevel.h"
#include "CStartLevel.h"
#include "CEditorLevel.h"
#include "CCollisionLevel.h"

#include "CCyberspaceLevel.h"
#include "CCyberspaceLevel2.h"
#include "CCyberspaceLevel3.h"
#include "CCyberspaceLevel4.h"
#include "CCyberspaceLevelBoss.h"

#include "CZero.h"
#include "CRockmanLevel.h"

CLevelManager::CLevelManager()
	: m_pCurLevel(nullptr)
	, m_arrLevel{}
{
}

CLevelManager::~CLevelManager()
{
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		if (m_arrLevel[i] != nullptr)
		{
			delete m_arrLevel[i];
			m_arrLevel[i] = nullptr;
		}
	}
}

void CLevelManager::init()
{	
	// Level 생성
	
	m_arrLevel[(UINT)LEVEL_TYPE::START]	 = new CStartLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::COLLISION] = new CCollisionLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR]	= new CEditorLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::TITLE] = new CTitleLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::CYBERSPACE] = new CCyberspaceLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::CYBERSPACE2] = new CCyberspaceLevel2;
	m_arrLevel[(UINT)LEVEL_TYPE::CYBERSPACE3] = new CCyberspaceLevel3;
	m_arrLevel[(UINT)LEVEL_TYPE::CYBERSPACE4] = new CCyberspaceLevel4;
	m_arrLevel[(UINT)LEVEL_TYPE::CYBERSPACEBOSS] = new CCyberspaceLevelBoss;

	this->LoadLevelEvent(LEVEL_TYPE::TITLE);

}

void CLevelManager::tick()
{
	m_pCurLevel->tick();
	m_pCurLevel->final_tick();	
}

void CLevelManager::fixed_tick()
{
	m_pCurLevel->fixed_tick();
}

void CLevelManager::render(HDC m_hDC)
{
	m_pCurLevel->render(m_hDC);
}

void CLevelManager::LoadLevel(LEVEL_TYPE _eNextLevel)
{
	tEvent _evn = {};
	_evn.eType = EVENT_TYPE::LEVEL_CHANGE;
	_evn.wParam = (DWORD_PTR)_eNextLevel;
	GETINSTANCE(CEventManager)->AddEvent(_evn);
}

CZero* CLevelManager::GetPlayerObject()
{
	CRockmanLevel* _lv = dynamic_cast<CRockmanLevel*>(GETINSTANCE(CLevelManager)->GetCurLevel());
	if (nullptr == _lv)
		return nullptr;
	return _lv->m_zero;
}

void CLevelManager::LoadLevelEvent(LEVEL_TYPE type)
{
	// 현재 레벨과 변경하려는 레벨이 동일 한 경우
	assert(m_pCurLevel != m_arrLevel[(UINT)type]);

	// 현재 레벨을 벗어남

	if (nullptr != m_pCurLevel)
		m_pCurLevel->Exit();
	m_pCurLevel = m_arrLevel[(UINT)type];
	m_pCurLevel->Enter();	
}