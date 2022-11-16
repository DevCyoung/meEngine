#include "pch.h"
#include "CCyberspaceLevel2.h"
#include "CMapManager.h"
#include "CKeyManager.h"

CCyberspaceLevel2::CCyberspaceLevel2()
{
	m_isReady = false;
}

CCyberspaceLevel2::~CCyberspaceLevel2()
{
}


void CCyberspaceLevel2::init()
{
	CRockmanLevel::init();
	m_nextLevel = LEVEL_TYPE::CYBERSPACE3;
}

void CCyberspaceLevel2::tick()
{
	CRockmanLevel::tick();

	//if (IS_INPUT_TAB(KEY::ENTER))
	//{
	//	//exit
	//	NextLevel(LEVEL_TYPE::CYBERSPACE3);		
	//}
}

void CCyberspaceLevel2::Enter()
{	
	
	CRockmanLevel::Enter();
	init();
	LoadMap(L"cyber\\cyberspace_Level_2.map");
	GETINSTANCE(CMapManager)->MapCameraSet(0);
	


}

void CCyberspaceLevel2::Exit()
{
	CRockmanLevel::Exit();
}

