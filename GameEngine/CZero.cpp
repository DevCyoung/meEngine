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
	, m_bisLand(false)
	, m_curLand(nullptr)
	, m_downLandCheck(nullptr)
	, m_downRay(nullptr)
	, m_dirMove(nullptr)
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
	init();

	CreateCollider();
	GetCollider()->SetScale(Vector2(70.f, 100.f));

	m_downRay = new CLine();
	m_downRay->CreateLineCollider(Vector2{}, Vector2{}, LINELAYER::DOWN);
	m_downRay->SetEnterEvent((DELEGATECOL)&CZero::DownHitEnter, this);
	m_downRay->SetExitEvent((DELEGATECOL)&CZero ::DownHitExit, this);
	m_downRay->GetLineCollider()->SetRaycast(GetPos(), Vector2(0.f, -1.f), Vector2(0.f, 0.f), 35.f);

	GETINSTANCE(CLineColManager)->LayerRegister(LINELAYER::DOWN, LINELAYER::DOWNWALL);

	m_vellocity = Vector2(1.f, 1.f);
}

CZero::CZero(const CRockmanObj& _other)
	: m_ray{}
	, m_fVerticalRayDist(0.f)
	,m_fHorizonRayDist(0.f)
	,m_downLandCheck(nullptr)
	,m_curLand(nullptr)
	,m_bisLand(false)
	, m_downRay(nullptr)
	, m_dirMove(nullptr)
{

}

CZero::~CZero()
{
	if (nullptr != m_downRay)
		delete m_downRay;
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
	CRockmanObj::tick();

	//float fRayDist = 75.f;

	Vector2 pos = this->GetPos();
	m_downRay->GetLineCollider()->SetRaycast(GetPos(), Vector2(0.f, 1.f), Vector2(0.f, 0.f), 50.f);
	if (IS_INPUT_PRESSED(KEY::LEFT)  &&  (m_ColDir & (UINT)COL_STATE_DIR::LEFT) == 0)
	{
		this->SetFilpX(false);
		if (nullptr == m_dirMove)
		{
			return;
		}
		Vector2 pos = GetPos();
		pos.x += DELTATIME * -200.f;
		Vector2 p1 = m_dirMove->GetP1();
		Vector2 p2 = m_dirMove->GetP2();
		pos.y = ((p2.y - p1.y) / (p2.x - p1.x)) * (pos.x - p1.x) + p1.y - 40.f;
		SetPos(pos);
		/*Vector2 vellocity;
		vellocity = m_vellocity  * -200.f;
		pos.x -= 200 * DELTATIME;
		GetRigidbody()->AddForce(vellocity);*/
	}
	if (IS_INPUT_PRESSED(KEY::RIGHT) && (m_ColDir & (UINT)COL_STATE_DIR::RIGHT) == 0)
	{
		this->SetFilpX(true);
		if (nullptr == m_dirMove)
		{
			return;
		}
		Vector2 pos = GetPos();
		pos.x += DELTATIME * 200.f;
		Vector2 p1 = m_dirMove->GetP1();
		Vector2 p2 = m_dirMove->GetP2();
		pos.y = ((p2.y - p1.y) / (p2.x - p1.x)) * (pos.x - p1.x) + p1.y - 40.f;
		SetPos(pos);
		/*Vector2 vellocity;
		vellocity = m_vellocity * +200.f;
		pos.x += 200 * DELTATIME;
		GetRigidbody()->AddForce(vellocity);*/
	}
	if (IS_INPUT_PRESSED(KEY::X) && (m_ColDir & (UINT)COL_STATE_DIR::LRD))
	{
		//m_vellocity.y -= 800.f;
		GetRigidbody()->SetVelocity(Vector2(0.f, -600.f));
		//GetRigidbody()->SetVelocity(m_vellocity);
	}

	//EventTick();
}



void CZero::render(HDC _dc)
{
	CRockmanObj::render(_dc);
}