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
{
	SetTag(LAYER::PLAYER);
	m_isGravity = true;

	CreateAnimator();

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
	GETINSTANCE(CCamera)->Settarget(this);
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