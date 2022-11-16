#include "pch.h"
#include "CCyberspaceLevel4.h"
#include "CMapManager.h"
#include "CKeyManager.h"

CCyberspaceLevel4::CCyberspaceLevel4()
{
	m_isReady = false;
}

CCyberspaceLevel4::~CCyberspaceLevel4()
{
}


void CCyberspaceLevel4::init()
{
	CRockmanLevel::init();
	m_nextLevel = LEVEL_TYPE::CYBERSPACEBOSS;
}

void CCyberspaceLevel4::tick()
{
	CRockmanLevel::tick();


}

void CCyberspaceLevel4::Enter()
{
	CRockmanLevel::Enter();
	init();
	LoadMap(L"cyber\\cyberspace_Level_4.map");
	GETINSTANCE(CMapManager)->MapCameraSet(0);


}

void CCyberspaceLevel4::Exit()
{
	CRockmanLevel::Exit();
}

