#include "pch.h"
#include "CCyberspaceLevelBoss.h"
#include "CMapManager.h"
#include "CCyberKujacer.h"
#include "CKeyManager.h"
#include "CZero.h"

#include "CTextureAnim.h"

#include "CMonsterHpbar.h"

#include "CCyberKujacer.h"

CCyberspaceLevelBoss::CCyberspaceLevelBoss()
{
	m_isDestReady = false;
	m_isReady = m_isDestReady;	
}

CCyberspaceLevelBoss::~CCyberspaceLevelBoss()
{
}


void CCyberspaceLevelBoss::init()
{
	CRockmanLevel::init();
	
	m_nextLevel = LEVEL_TYPE::TITLE;
	m_curLevel = LEVEL_TYPE::CYBERSPACEBOSS;
}

void CCyberspaceLevelBoss::tick()
{
	CRockmanLevel::tick();

	//if (IS_INPUT_TAB(KEY::ENTER))
	//{
	//	NextLevel();
	//}
}

void CCyberspaceLevelBoss::Enter()
{
	CRockmanLevel::Enter();
	init();
	LoadMap(L"cyber\\cyberspace_Level_5.map");
	GETINSTANCE(CMapManager)->MapCameraSet(0);
}

void CCyberspaceLevelBoss::Exit()
{
	CRockmanLevel::Exit();
}

