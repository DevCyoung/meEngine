#include "pch.h"
#include "CCyberspaceLevel.h"
#include "CTextureAnim.h"
#include "CGameObject.h"
#include "CCamera.h"
#include "CEditorLevel.h"
#include "CLevelManager.h"
#include "CKeyManager.h"

#include "CZero.h"
#include "CMapManager.h"
#include "CAnimator.h"
#include "CTextureAnim.h"


CCyberspaceLevel::CCyberspaceLevel()
{
	
}

CCyberspaceLevel::~CCyberspaceLevel()
{
}

void CCyberspaceLevel::init()
{
	CRockmanLevel::init();	
}

void CCyberspaceLevel::tick()
{
	CRockmanLevel::tick();

	if (IS_INPUT_TAB(KEY::ENTER))
	{
		//exit
		NextLevel(LEVEL_TYPE::CYBERSPACE2);
		//GETINSTANCE(CLevelManager)->LoadLevel(LEVEL_TYPE::CYBERSPACE2);
	}
}

void CCyberspaceLevel::Enter()
{
	
	CRockmanLevel::Enter();	
	init();
	LoadMap(L"cyber\\test1.map");
	GETINSTANCE(CMapManager)->MapCameraSet(0);		
}

void CCyberspaceLevel::Exit()
{
	CRockmanLevel::Exit();
}

