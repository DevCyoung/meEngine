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

#include "CCameraObj.h"
#include "CGameObject.h"

#include "CEffectManager.h"

#include "CKeyManager.h"

#include "CRockmanManager.h"
CRockmanLevel::CRockmanLevel()
	: m_editor(nullptr)
	, m_zero(nullptr)
	, m_textureReadyAnim(nullptr)
	, m_cam(nullptr)
	, m_delay(0.f)
	, m_levelState(eLEVELSTATE::NONE)
	, m_isReady(true)
	, m_isDestReady(true)
	, m_exitDelay(0.f)
	, m_nextLevel{}
	, m_curLevel{}
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
	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::PLAYER, LAYER::MONSTER);
	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::PLAYER, LAYER::MONSTERATTACK);
	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::PLAYER, LAYER::EVENT);
	

	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::MONSTER, LAYER::PLAYERATTACK);
	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::CAMERA, LAYER::CAMERAWALL);

	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::WALL, LAYER::MONSTERATTACK);


	m_textureReadyAnim = new CTextureAnim();
	Vector2 pos = GETINSTANCE(CCamera)->GetLook();
	CGameObject::Instantiate(m_textureReadyAnim, pos, LAYER::DEFAUT);


	GETINSTANCE(CResourceManager)->LoadSound(L"startvim", L"sound\\startvim.wav");
	GETINSTANCE(CResourceManager)->LoadSound(L"startvim", L"sound\\startvim.wav")->SetVolume(18.f);

	//efect


}

void CRockmanLevel::tick()
{
	CLevel::tick();

	if (IS_INPUT_PRESSED(KEY::LSHIFT))
	{
		if (IS_INPUT_TAB(KEY::_1))
		{
			NextLevel(LEVEL_TYPE::CYBERSPACE);
		}
		else if (IS_INPUT_TAB(KEY::_2))
		{
			NextLevel(LEVEL_TYPE::CYBERSPACE2);
		}
		else if (IS_INPUT_TAB(KEY::_3))
		{
			NextLevel(LEVEL_TYPE::CYBERSPACE3);
		}
		else if (IS_INPUT_TAB(KEY::_4))
		{
			NextLevel(LEVEL_TYPE::CYBERSPACE4);
		}
		else if (IS_INPUT_TAB(KEY::_5))
		{
			NextLevel(LEVEL_TYPE::CYBERSPACEBOSS);
		}
		else if (IS_INPUT_TAB(KEY::_6))
		{
			NextLevel(LEVEL_TYPE::TITLE);
		}
	}

	LevelDealy();
}

void CRockmanLevel::Enter()
{
	//CLevel::Enter(); = 0
	init();
	GETINSTANCE(CEffectManager)->LoadAllEffect();
	GETINSTANCE(CCamera)->FadeIn(1.0f);	
	m_delay = 0.f;

	if (m_isReady == true)
	{		
		GETINSTANCE(CRockmanManager)->m_backGroundsound->PlayToBGM(true);
	}
}

void CRockmanLevel::Exit()
{
	DeleteAllObject();
	m_levelState = eLEVELSTATE::FADEENTER;
	m_zero = nullptr;
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

	m_cam = new CCameraObj();
	m_cam->SetTarget(m_zero);
	CGameObject::Instantiate(m_cam, m_cam->GetPos(), LAYER::CAMERA);

	Vector2 camPos = GETINSTANCE(CCamera)->GetLook();

	m_cam->SetPos(camPos);
	m_cam->m_position = camPos;

	m_zero->m_camera = m_cam;
}

void CRockmanLevel::ZeroRetrun()
{
	m_zero->SetState(PLAYER_STATE::RETURN);
	m_zero->GetAnimator()->Play(L"RETURN", true);
}

void CRockmanLevel::LevelDealy()
{
	m_delay += DELTATIME;


	
	if (m_delay >= 4.f && m_levelState == eLEVELSTATE::ZEROENTER)
	{		
		GETINSTANCE(CResourceManager)->FindSound(L"startvim")->Play();
		ZeroEnter(0);		
		m_levelState = eLEVELSTATE::NONE;
		
	}
	else if (m_delay >= 2.f && m_levelState == eLEVELSTATE::FADEENTER)
	{
		if (m_isReady == false)
		{
			m_levelState = eLEVELSTATE::ZEROENTER;
			m_delay += 2.f;

		}
		else
		{
			m_levelState = eLEVELSTATE::READY;
			m_textureReadyAnim->Enter();
		}
		
	}

	if (m_isReady)
	{
		if (m_delay >= 3.f && m_levelState == eLEVELSTATE::READY)	
		{

			m_levelState = eLEVELSTATE::ZEROENTER;
			m_textureReadyAnim->Remove();
			m_isReady = m_isDestReady;
		}
	}

	if (m_levelState == eLEVELSTATE::FADEFIX)
		return;

	if(m_levelState == eLEVELSTATE::FADEEXIT)
	{
		m_exitDelay += DELTATIME;
		
		if (m_exitDelay >= 1.0f)
		{			
			GETINSTANCE(CLevelManager)->LoadLevel(LEVEL_TYPE::DUMY);
			GETINSTANCE(CRockmanManager)->m_nextLevel = m_nextLevel;
			m_levelState = eLEVELSTATE::FADEFIX;
			m_exitDelay = 0.f;
		}
	}

	//if (m_levelState == eLEVELSTATE::DUMYLEVEL)
	//{
	//	m_exitDelay += DELTATIME;

	//	if (m_exitDelay >= 0.5f)
	//	{
	//		
	//		m_levelState = eLEVELSTATE::FADEFIX;
	//		m_exitDelay = 0.f;
	//	}
	//}
}

void CRockmanLevel::NextAread(UINT idx)
{
	m_isReady = true;
}

void CRockmanLevel::NextLevel(LEVEL_TYPE layer)
{	
	//if (layer == m_curLevel)
	//	return;

	m_levelState = eLEVELSTATE::FADEEXIT;
	m_nextLevel = layer;
	m_exitDelay = 0.f;
	GETINSTANCE(CCamera)->FadeOut(1.f);
}

void CRockmanLevel::NextLevel()
{
	m_levelState = eLEVELSTATE::FADEEXIT;
	m_exitDelay = 0.f;
	GETINSTANCE(CCamera)->FadeOut(1.f);
}
