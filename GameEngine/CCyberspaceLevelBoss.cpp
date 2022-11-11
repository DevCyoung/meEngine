#include "pch.h"
#include "CCyberspaceLevelBoss.h"
#include "CMapManager.h"

CCyberspaceLevelBoss::CCyberspaceLevelBoss()
{
	m_isReady = false;
}

CCyberspaceLevelBoss::~CCyberspaceLevelBoss()
{
}


void CCyberspaceLevelBoss::init()
{
	CRockmanLevel::init();
}

void CCyberspaceLevelBoss::tick()
{
	CRockmanLevel::tick();

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

