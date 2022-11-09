#include "pch.h"
#include "CCyberspaceLevel2.h"
#include "CMapManager.h"

CCyberspaceLevel2::CCyberspaceLevel2()
{
}

CCyberspaceLevel2::~CCyberspaceLevel2()
{
}


void CCyberspaceLevel2::init()
{
	CRockmanLevel::init();
}

void CCyberspaceLevel2::tick()
{
	CRockmanLevel::tick();

}

void CCyberspaceLevel2::Enter()
{	
	LoadMap(L"cyber\\addeventppap2.map");
	CRockmanLevel::Enter();
	init();
	GETINSTANCE(CMapManager)->MapCameraSet(0);
}

void CCyberspaceLevel2::Exit()
{
	CRockmanLevel::Exit();
}

