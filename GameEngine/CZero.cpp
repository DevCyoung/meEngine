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

CTexture* mm_pTexuture = nullptr;
CZero::CZero()
	: m_fVerticalRayDist(0.f)
	, m_fHorizonRayDist(0.f)
	, m_bisLand(false)
	, m_curLand(nullptr)
	, m_downLandCheck(nullptr)
	, m_dirMoveLine(nullptr)
	, m_dirMoveBox(nullptr)
{
	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\zero\\thunder.anim");
	GetAnimator()->LoadAnimation(L"animation\\zero\\IDLE.anim");
	GetAnimator()->LoadAnimation(L"animation\\zero\\attack.anim");

	GetAnimator()->Play(L"IDLE", true);
	CreateRigidbody();
	this->CreateRigidbody();
	this->GetRigidbody()->SetGravity(true);
	this->GetRigidbody()->SetGravityAccel(600.f);
	this->GetRigidbody()->SetVelocityLimit(600.f);
	this->GetRigidbody()->SetGravityVelocityLimit(600.f);

	CreateCollider();
	GetCollider()->SetScale(Vector2(70.f, 100.f));

	CreateLineCollider();
	GetLineCollider()->SetRaycast(GetPos(), Vector2(0.f, -1.f), Vector2(0.f, 0.f), 50.f);
	GetLineCollider()->SetEnterEvent((DELEGATECOL)&CZero::DownHitEnter, this);
	GetLineCollider()->SetExitEvent((DELEGATECOL)&CZero::DownHitExit, this);	
	SetTag(LAYER::PLAYER);
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
{
	CreateLineCollider();
	GetLineCollider()->SetRaycast(GetPos(), Vector2(0.f, -1.f), Vector2(0.f, 0.f), 50.f);
	GetLineCollider()->SetEnterEvent((DELEGATECOL)&CZero::DownHitEnter, this);
	GetLineCollider()->SetExitEvent((DELEGATECOL)&CZero::DownHitExit, this);
	SetTag(LAYER::PLAYER);
}

CZero::~CZero()
{

}



CLineCollider* lineColqq;
void CZero::init()
{
	//EventInit();
	Vector2 pos = GetPos();
	//lineColqq = GETINSTANCE(CLineColManager)->CreateRay(pos, Vector2(-1.f, 0.f), 40.f, LINELAYER::LEFTWALL);
	//GETINSTANCE(CLineColManager)->CreateRaycast(m_ray, Vector2(40.f, 60.f), Vector2(40.f, 60.f));
	//EventInit();
}

void CZero::tick()
{

	//float fRayDist = 75.f;
	CRockmanObj::tick();
	Vector2 pos = this->GetPos();

	//EventTick();
	m_vellocity.y = GetRigidbody()->GetVelocity().y;
	if (IS_INPUT_PRESSED(KEY::LEFT))
	{
		m_vellocity.x = -137.5f;
		SetFlipX(false);
	}
	if (IS_INPUT_RELEASE(KEY::LEFT))
	{
		m_vellocity.x = 0.f;
	}

	if (IS_INPUT_PRESSED(KEY::RIGHT))
	{
		m_vellocity.x = +137.5f;
		SetFlipX(true);
	}
	if (IS_INPUT_RELEASE(KEY::RIGHT))
	{
		m_vellocity.x = 0.f;
	}

	if (IS_INPUT_PRESSED(KEY::C))
	{
		m_vellocity.x *= 1.5f;
	}
	if (IS_INPUT_RELEASE(KEY::C))
	{
		m_vellocity.x = 0.f;
	}
	
	if (IS_INPUT_PRESSED(KEY::X))
	{
		//m_vellocity.y = -200.f;
		GetRigidbody()->AddForce(Vector2(0.f, -1600.f));
	}
	else
	{
		if (nullptr != m_dirMoveLine)
		{
			Vector2 p1 = m_dirMoveLine->GetP1();
			Vector2 p2 = m_dirMoveLine->GetP2();
			pos.y = ((p2.y - p1.y) / (p2.x - p1.x)) * (pos.x - p1.x) + p1.y - 49.f;
			SetPos(pos);
		}
		else if (nullptr != m_dirMoveBox)
		{
			float distance = m_dirMoveBox->GetFinalPos().y - m_dirMoveBox->GetScale().y / 2 - 49.f;
			pos.y = distance;
			SetPos(pos);
		}
		//m_vellocity.y = +150.f;
	}

	//if ((m_ColDir & (UINT)COL_STATE_DIR::DOWN) == 0)
	//{
	//	GetRigidbody()->SetGravity(true);
	//	
	//}


	//m_vellocity.y = GetRigidbody()->GetVelocity().y;
	
	

	m_downRay->GetLineCollider()->SetRaycast(GetPos(), Vector2(0.f, 1.f), Vector2(0.f, 0.f), 50.f);
	GetRigidbody()->SetVelocity(m_vellocity);
	
}



void CZero::render(HDC _dc)
{
	CRockmanObj::render(_dc);
}