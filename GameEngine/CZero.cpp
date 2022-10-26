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

CTexture* mm_pTexuture = nullptr;
CZero::CZero()
	: m_fVerticalRayDist(0.f)
	, m_bisLand(false)
	, m_curLand(nullptr)
	, m_downLandCheck(nullptr)
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
	this->GetRigidbody()->SetVelocityLimit(11800.f);
	this->GetRigidbody()->SetGravityVelocityLimit(600.f);
	init();
}

CZero::CZero(const CRockmanObj& _other)
	: m_ray{}
	, m_fVerticalRayDist(0.f)
	,m_fHorizonRayDist(0.f)
	,m_downLandCheck(nullptr)
	,m_curLand(nullptr)
	,m_bisLand(false)

{
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
	GETINSTANCE(CLineColManager)->CreateRaycast(m_ray, Vector2(40.f, 60.f), Vector2(40.f, 60.f));
	EventInit();
}

void CZero::tick()
{
	CRockmanObj::tick();

	float fRayDist = 75.f;

	Vector2 pos = this->GetPos();

	if (IS_INPUT_PRESSED(KEY::LEFT) && m_ray.GetCollideCnt(RAY_TYPE::LEFT_UP) == 0 && m_ray.GetCollideCnt(RAY_TYPE::LEFT_DOWN) == 0)
	{
		this->SetFilpX(false);
		pos.x -= 200 * DELTATIME;
	}
	if (IS_INPUT_PRESSED(KEY::RIGHT) && m_ray.GetCollideCnt(RAY_TYPE::RIGHT_UP) == 0 && m_ray.GetCollideCnt(RAY_TYPE::RIGHT_DOWN) == 0)
	{
		this->SetFilpX(true);
		pos.x += 200 * DELTATIME;
	}
	if (IS_INPUT_PRESSED(KEY::UP))
	{
		pos.y -= 200 * DELTATIME;
	}
	if (IS_INPUT_PRESSED(KEY::DOWN))
	{
		pos.y += 200 * DELTATIME;
	}

	if (IS_INPUT_TAB(KEY::LCTRL))
	{
		GetAnimator()->Play(L"THUNDER", false);
	}

	if (IS_INPUT_TAB(KEY::Z))
	{
		GetAnimator()->Play(L"ATTACK", false);
	}

	if (IS_INPUT_PRESSED(KEY::X))
	{
		pos.y -= 1000 * DELTATIME;
		//GetRigidbody()->SetVelocity(Vector2(0.f, -10000.f));
	}
	else
	{
	}
	if (IS_INPUT_PRESSED(KEY::C))
	{
		//GetRigidbody()->SetVelocity(Vector2(200.f, 0.f));
	}
	EventTick();
	

	this->SetPos(pos);

	m_ray.TranslateSetPos(GetPos());
}

void CZero::fixed_tick()
{
	Vector2 vPos = GetPos();
	vPos.x += 300.f * DELTATIME;
	SetPos(vPos);
}

void CZero::render(HDC _dc)
{
	CRockmanObj::render(_dc);
}