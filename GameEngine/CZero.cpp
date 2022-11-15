#include "pch.h"
#include "CZero.h"
#include "CLineColManager.h"
#include "CLineCollider.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CCamera.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResourceManager.h"
#include "CRigidbody.h"
#include "CLine.h"

#include "CPlayerController.h"
#include "CPlayerAnimEvent.h"

#include "CCameraObj.h"


//text
#include "CHitBox.h"
#include "CResourceManager.h"
#include "CSound.h"
#include "CHitManager.h"

#include "CEffectManager.h"

#include "CHPbar.h"

CTexture* mm_pTexuture = nullptr;

CZero::CZero()
	: m_fVerticalRayDist(0.f)
	, m_fHorizonRayDist(0.f)
	, m_bisLand(false)
	, m_curLand(nullptr)
	, m_downLandCheck(nullptr)
	, m_dirMoveLine(nullptr)
	, m_dirMoveBox(nullptr)
	, m_animEvent(nullptr)
	, m_camera(nullptr)
	, m_isCheatMode(false)
{
	SetTag(LAYER::PLAYER);
	m_isGravity = true;

	CreateAnimator();
	GETINSTANCE(CEffectManager)->SetPlayerTarget(this);
	GETINSTANCE(CResourceManager)->LoadTexture(L"ZERO", L"texture\\charactor\\atlas_zero.bmp");
	GETINSTANCE(CResourceManager)->LoadTexture(L"BLACKZERO", L"texture\\charactor\\atlas_zero_black.bmp");

	CreateCollider();
	GetCollider()->SetScale(Vector2(80.f, 120.f));

	CreateLineCollider();
	GetLineCollider()->SetRaycast(Vector2(-1000.f, -1000.f), Vector2(0.f, 1.f), Vector2(0.f, 0.f), GetCollider()->GetScale().y / 2.f);
	GetLineCollider()->SetEnterEvent((DELEGATECOL)&CZero::DownHitEnter, this);
	GetLineCollider()->SetExitEvent((DELEGATECOL)&CZero::DownHitExit, this);	

	CreateAnimEvent();
	CreatePlayerController();

	CreateRigidbody();
	GetRigidbody()->SetGravityAccel(1950.f);
	GetRigidbody()->SetGravity(true);
	GetRigidbody()->SetFrictionScale(12.f);

	//camera
	//TINSTANCE(CCamera)->Settarget(this);
	//테스트

	

	CHitBox* hbox = new CHitBox();
	hbox->SetOwner(this);
	hbox->SetTartgetLayer(LAYER::MONSTER);
	
	CGameObject::Instantiate(hbox, Vector2(0.f, 0.f), LAYER::PLAYERATTACK);
	
	m_hp = 10;
	CHPbar* bar = new CHPbar();
	bar->m_Maxhp = m_hp;
	bar->m_target = this;
	bar->m_prevHp = m_hp;
	CGameObject::Instantiate(bar, bar->GetPos(), LAYER::EDITOR);

}

CZero::CZero(const CZero& _other)
	: CRockmanObj(_other)
	, m_fVerticalRayDist(0.f)
	, m_fHorizonRayDist(0.f)
	, m_downLandCheck(nullptr)
	, m_curLand(nullptr)
	, m_bisLand(false)
	, m_dirMoveLine(nullptr)
	, m_dirMoveBox(nullptr)
	, m_animEvent(nullptr)
	, m_isCheatMode(false)
{
	SetTag(LAYER::PLAYER);


	CreateLineCollider();
	GetLineCollider()->SetRaycast(Vector2(-1000.f, -1000.f), Vector2(0.f, 1.f), Vector2(0.f, 0.f), GetCollider()->GetScale().y / 2.f);
	GetLineCollider()->SetEnterEvent((DELEGATECOL)&CZero::DownHitEnter, this);
	GetLineCollider()->SetExitEvent((DELEGATECOL)&CZero::DownHitExit, this);

	CreatePlayerController();
	CreateAnimEvent();
	



}

CZero::~CZero()
{
	if (nullptr != m_playerController)
	{
		delete m_playerController;
	}

	if (nullptr != m_animEvent)
	{
		delete m_animEvent;
	}

	if (nullptr != m_camera)
	{
		m_camera->Destroy();
	}
}



CLineCollider* lineColqq;
void CZero::init()
{

}

void CZero::tick()
{
	

	if (nullptr != m_animEvent)
		m_animEvent->tick();


	if (nullptr != m_playerController)
		m_playerController->tick();


	CRockmanObj::tick();

	if (nullptr != m_playerController)
		m_playerController->flip_tick();


	//치트모드
	if (IS_INPUT_TAB(KEY::_9))
	{
		GETINSTANCE(CResourceManager)->LoadSound(L"changemode", L"sound\\changemode.wav")->SetPosition(0);
		GETINSTANCE(CResourceManager)->LoadSound(L"changemode", L"sound\\changemode.wav")->SetVolume(18.f);
		GETINSTANCE(CResourceManager)->LoadSound(L"changemode", L"sound\\changemode.wav")->Play();

		if (m_isCheatMode == false)
		{
			GetAnimator()->SetAllAtlas(GETINSTANCE(CResourceManager)->FindTexture(L"BLACKZERO"));
			m_isCheatMode = true;
		}
		else
		{
			GetAnimator()->SetAllAtlas(GETINSTANCE(CResourceManager)->FindTexture(L"ZERO"));
			m_isCheatMode = false;
		}				
	}
}



void CZero::render(HDC _dc)
{
	if (nullptr != m_playerController)
		m_playerController->render(_dc);
	if (nullptr != m_animEvent)
		m_animEvent->render(_dc);
	CRockmanObj::render(_dc);

}


void CZero::RetrunEvent()
{
	m_playerController->m_state = PLAYER_STATE::RETURNREADY;
}

void CZero::AttackEvent(tAnimFrm frm,  CCollider* _pOther)
{
	if (LAYER::MONSTER != _pOther->GetOwner()->GetLayer())
		return;
	CRockmanObj* rmObj = dynamic_cast<CRockmanObj*>(_pOther->GetOwner());
	assert(rmObj);

	bool flipX = rmObj->GetPos().x > GetPos().x;

	if (m_playerController->m_state == PLAYER_STATE::LANDATTACK1)
	{

	}
	else if (m_playerController->m_state == PLAYER_STATE::LANDATTACK2)
	{		
	}
	else if (rmObj->m_hp > 0)
	{
		GETINSTANCE(CHitManager)->AddAtackDelay(frm);
	}
}
