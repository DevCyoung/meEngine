#include "pch.h"
#include "CTitleLevel.h"
#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CPlatform.h"
#include "CCollisionManager.h"
#include "CKeyManager.h"
#include "CCamera.h"
#include "CLevelManager.h"
#include "CPlatform.h"
#include "CTileObj.h"

CTitleLevel::CTitleLevel()
{

}

CTitleLevel::~CTitleLevel()
{

}

void CTitleLevel::init()
{
	m_nextLevel = LEVEL_TYPE::CYBERSPACE;
	m_curLevel = LEVEL_TYPE::TITLE;
	m_levelState = eLEVELSTATE::NONE;
}

void CTitleLevel::tick()
{
	CRockmanLevel::tick();

	if (IS_INPUT_PRESSED(KEY::LSHIFT))
	{
		if (IS_INPUT_TAB(KEY::_7))
		{
			GETINSTANCE(CLevelManager)->LoadLevel(LEVEL_TYPE::EDITOR);
		}
	}

	
}

void CTitleLevel::Enter()
{
	this->init();
	GETINSTANCE(CCamera)->FadeIn(1.0f);
	CTileObj* titleObj = new CTileObj();
	CGameObject::Instantiate(titleObj, titleObj->GetPos(), LAYER::DEFAUT
	);
}

void CTitleLevel::Exit()
{
	this->DeleteAllObject();
}