#include "pch.h"
#include "CCyberspaceLevelBoss.h"
#include "CMapManager.h"
#include "CCyberKujacer.h"
#include "CKeyManager.h"
#include "CZero.h"

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
	if (IS_INPUT_TAB(KEY::ENTER))
	{
		CCyberKujacer* kujan = new CCyberKujacer();
		CGameObject::Instantiate(kujan, m_zero->GetPos(), LAYER::MONSTER);
	}

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

