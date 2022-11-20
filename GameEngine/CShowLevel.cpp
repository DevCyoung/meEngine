#include "pch.h"
#include "CShowLevel.h"
#include "CMap.h"
#include "CMapManager.h"
#include "CCuner.h"
#include "CKeyManager.h"
#include "CZero.h"

CShowLevel::CShowLevel()
{
	m_isDestReady = true;
	m_isReady = m_isDestReady;
}

CShowLevel::~CShowLevel()
{
}


void CShowLevel::init()
{
	CRockmanLevel::init();
	m_nextLevel = LEVEL_TYPE::CYBERSPACE2;
	m_curLevel = LEVEL_TYPE::SHOW;
}

void CShowLevel::tick()
{
	CRockmanLevel::tick();

	if (IS_INPUT_TAB(KEY::SPACE))
	{
		Vector2 pos = m_zero->GetPos();
		CCuner* cuner = new CCuner();
		CGameObject::Instantiate(cuner, pos, LAYER::MONSTER);
	}

	//Å×½ºÆ®

	if (IS_INPUT_TAB(KEY::TAB))
	{
		//GETINSTANCE(CEffectManager)->OnShootPlay(EFFECT_TYPE::DIEBALL, GetPos(), false);
		//GetAnimator()->Play(L"GOOD", false);
		--m_zero->m_hp;
	}
}

void CShowLevel::Enter()
{
	CRockmanLevel::Enter();
	init();
	LoadMap(L"cyber\\show.map");
	GETINSTANCE(CMapManager)->MapCameraSet(0);
}

void CShowLevel::Exit()
{
	CRockmanLevel::Exit();
}

