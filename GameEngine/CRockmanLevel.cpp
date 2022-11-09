#include "pch.h"
#include "CRockmanLevel.h"
#include "CEditorLevel.h"
#include "CResourceManager.h"
#include "CLevelManager.h"

#include "CCamera.h"
#include "CCollisionManager.h"
#include "CZero.h"

#include "CResourceManager.h"
#include "CSound.h"
#include "CMapManager.h"
#include "CAnimator.h"
#include "CTextureAnim.h"
#include "CTimeManager.h"

CRockmanLevel::CRockmanLevel()
	: m_editor(nullptr)
	, m_zero(nullptr)
	, m_textureAnim(nullptr)
	, m_delay(0.f)
	, m_levelState(eLEVELSTATE::NONE)
	, m_isReady(true)
	, m_exitDelay(0.f)
	, m_nextLevel{}
{
	m_levelState = eLEVELSTATE::FADEENTER;
}

CRockmanLevel::~CRockmanLevel()
{
}


void CRockmanLevel::init()
{	
	//m_editor = (CEditorLevel*)GETINSTANCE(CLevelManager)->GetEditorLevel();

	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::MONSTER, LAYER::WALL);
	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::PLAYER, LAYER::WALL);

	m_textureAnim = new CTextureAnim();
	Vector2 pos = GETINSTANCE(CCamera)->GetLook();
	CGameObject::Instantiate(m_textureAnim, pos, LAYER::DEFAUT);
}

void CRockmanLevel::tick()
{
	CLevel::tick();

	LevelDealy();
}

void CRockmanLevel::Enter()
{
	//CLevel::Enter(); = 0
	init();
	GETINSTANCE(CCamera)->FadeIn(0.5f);
}

void CRockmanLevel::Exit()
{
	//CLevel::Exit(); = 0

	//GETINSTANCE(CCamera)->FadeOut(1.0f);
}

void CRockmanLevel::LoadMap(const wstring& str)
{
	((CEditorLevel*)GETINSTANCE(CLevelManager)->GetEditorLevel())->Load(str.c_str());
}

void CRockmanLevel::ZeroEnter(UINT idx)
{	
	m_zero = new CZero();
	CGameObject::Instantiate(m_zero, Vector2(-1000.f, -1000.f), LAYER::PLAYER);
	Vector2 pos = GETINSTANCE(CMapManager)->GetPlayerPos(idx);
	pos.y -= 500.f;
	m_zero->SetPos(pos);
	m_zero->GetAnimator()->Play(L"VIMBLINK", true);
	m_zero->SetState(PLAYER_STATE::ENTER);
}

void CRockmanLevel::ZeroRetrun()
{
	m_zero->SetState(PLAYER_STATE::RETURN);
	m_zero->GetAnimator()->Play(L"RETURN", true);
}

void CRockmanLevel::LevelDealy()
{
	m_delay += DELTATIME;
	
	if (m_delay >= 5.f && m_levelState == eLEVELSTATE::ZEROENTER)
	{
		GETINSTANCE(CResourceManager)->LoadSound(L"startvim", L"sound\\startvim.wav")->SetPosition(0);
		GETINSTANCE(CResourceManager)->LoadSound(L"startvim", L"sound\\startvim.wav")->SetVolume(18.f);
		GETINSTANCE(CResourceManager)->LoadSound(L"startvim", L"sound\\startvim.wav")->Play();
		ZeroEnter(0);		
		m_levelState = eLEVELSTATE::NONE;
		
	}
	else if (m_delay >= 3.f && m_levelState == eLEVELSTATE::FADEENTER)
	{
		if (m_isReady == false)
		{
			m_levelState = eLEVELSTATE::ZEROENTER;
		}
		else
		{
			m_levelState = eLEVELSTATE::READY;
		}
		m_textureAnim->Enter();
	}

	if (m_isReady)
	{
		if (m_delay >= 4.f && m_levelState == eLEVELSTATE::READY)
		{

			m_levelState = eLEVELSTATE::ZEROENTER;
			m_textureAnim->Remove();
		}
	}

	if(m_levelState == eLEVELSTATE::FADEEXIT)
	{
		m_exitDelay += DELTATIME;
		
		if (m_exitDelay >= 2.f)
		{
			GETINSTANCE(CLevelManager)->LoadLevel(m_nextLevel);
		}
	}
}

void CRockmanLevel::NextAread(UINT idx)
{
	m_isReady = true;
}

void CRockmanLevel::NextLevel(LEVEL_TYPE layer)
{	
	m_levelState = eLEVELSTATE::FADEEXIT;
	m_nextLevel = layer;
	GETINSTANCE(CCamera)->FadeOut(1.0f);
}
