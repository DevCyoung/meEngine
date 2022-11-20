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

#include "CRockmanManager.h"

CTitleLevel::CTitleLevel()
	:m_titleBackGround(nullptr)
{
	m_titleBackGround = GETINSTANCE(CResourceManager)->LoadSound(L"titlebackground", L"sound\\titlebackground.wav");	
	m_titleBackGround->SetVolume(18.f);
	
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
		if (IS_INPUT_TAB(KEY::_8))
		{
			GETINSTANCE(CLevelManager)->LoadLevel(LEVEL_TYPE::SHOW);
		}
	}

	
}

void CTitleLevel::Enter()
{
	this->init();
	GETINSTANCE(CCamera)->FadeIn(1.0f);
	CTileObj* titleObj = new CTileObj();
	CGameObject::Instantiate(titleObj, titleObj->GetPos(), LAYER::DEFAUT);

	GETINSTANCE(CRockmanManager)->m_zeroCurHP  = 8;
	GETINSTANCE(CRockmanManager)->m_zeroMaxHp  = 8;
	GETINSTANCE(CRockmanManager)->m_zeroLife   = 2;

	m_titleBackGround->SetPosition(0.f);
	m_titleBackGround->PlayToBGM(true);
}

void CTitleLevel::Exit()
{	
	m_titleBackGround->Stop(true);
	this->DeleteAllObject();
}