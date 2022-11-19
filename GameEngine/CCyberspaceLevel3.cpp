#include "pch.h"
#include "CCyberspaceLevel3.h"
#include "CMapManager.h"
#include "CKeyManager.h"

CCyberspaceLevel3::CCyberspaceLevel3()
{
	m_isDestReady = false;
	m_isReady = m_isDestReady;
}

CCyberspaceLevel3::~CCyberspaceLevel3()
{
}


void CCyberspaceLevel3::init()
{
	CRockmanLevel::init();
	m_nextLevel = LEVEL_TYPE::CYBERSPACE4;
	m_curLevel = LEVEL_TYPE::CYBERSPACE3;
}

void CCyberspaceLevel3::tick()
{
	CRockmanLevel::tick();

	//if (IS_INPUT_TAB(KEY::ENTER))
	//{
	//	//exit
	//	NextLevel(LEVEL_TYPE::CYBERSPACE4);
	//}
}

void CCyberspaceLevel3::Enter()
{

	CRockmanLevel::Enter();
	init();
	LoadMap(L"cyber\\cyberspace_Level_3.map");
	GETINSTANCE(CMapManager)->MapCameraSet(0);


}

void CCyberspaceLevel3::Exit()
{
	CRockmanLevel::Exit();
}

