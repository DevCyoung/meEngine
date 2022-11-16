#include "pch.h"
#include "CFlyCong.h"
#include "CAnimator.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CRigidbody.h"
#include "CLine.h"
#include "CTimeManager.h"
#include "CZero.h"
#include "CCyberCongBoost.h"
#include <cmath>

#include "CCyberCongBullet.h"




CFlyCong::CFlyCong()
	:m_boost(nullptr)
	, m_delay{}
	, m_booState{}
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(30.f, 30.f));

	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\flycong\\attackleft.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\flycong\\attackleftdown.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\flycong\\attackleftup.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\flycong\\attackup.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\flycong\\attackdown.anim");

	GetAnimator()->LoadAnimation(L"animation\\monster\\flycong\\idle.anim");

	GetAnimator()->Play(L"IDLE", false);

	m_sponType = MONSETER_TYPE::FLYCONG;

	/*m_boost = new CCyberCongBoost();
	m_boost->m_target = this;
	m_boost->m_isMove = false;
	CGameObject::Instantiate(m_boost, GetPos(), LAYER::DEFAUT);*/

	m_booState = BOOSTSTATE::PATROL;
	m_hp = 3;
}

CFlyCong::CFlyCong(const CFlyCong& _other)
	:m_boost(nullptr)
	, m_delay{}
	, m_booState{}
{
}

CFlyCong::~CFlyCong()
{
	if (nullptr != m_boost)
	{
		m_boost->Destroy();
	}
}


void CFlyCong::tick()
{
	CRockmanMonster::tick();

	if (m_isStart == false)
	{
		return;
	}


	Vector2 dir = m_zero->GetPos() - GetPos();
	dir.Normalize();

	Vector2 pos = GetPos() + dir * 300.f * DELTATIME;

	pos.x = GetPos().x + dir.x * 520.f * DELTATIME;
	pos.y = GetPos().y + dir.y * 400.f * DELTATIME;

	float len = (GetPos() - m_zero->GetPos()).Length();

	double x = dir.x;
	double y = dir.y;

	if (dir.x < 0)
	{
		x *= -1.f;
	}

	double angleInRadians = std::atan2(x, y);

	int angleInDegrees = (angleInRadians / 3.14f) * 180.0;




	Vector2 move_dir = Vector2(sinf(angleInDegrees), cosf(angleInDegrees));

	
	//강제상태변환

	if (m_vecLen.x > 400.f && m_booState != BOOSTSTATE::PATROL)
	{
		m_booState = BOOSTSTATE::PATROL;
		m_delay[(UINT)BOOSTSTATE::PATROL] = 0.f;
	}
	else if (m_vecLen.x < 150.f && m_booState != BOOSTSTATE::ATTACK && m_booState != BOOSTSTATE::ATTACKREADY)
	{
		m_booState = BOOSTSTATE::ATTACK;
		//m_delay[(UINT)BOOSTSTATE::ATTACK] = 0.f;
	}





	
	pos = GetPos();

	if (m_booState == BOOSTSTATE::ATTACK)
	{
		m_delay[(UINT)BOOSTSTATE::ATTACK] += DELTATIME;
		m_delay[(UINT)BOOSTSTATE::ATTACKREADY] += DELTATIME;

		//1사분면
		if (0 <= angleInDegrees && angleInDegrees <= 36)
		{

			GetAnimator()->TrigerPlay(L"ATTACKDOWN", true);
		}
		else if (36 <= angleInDegrees && angleInDegrees <= 72)
		{


			GetAnimator()->TrigerPlay(L"ATTACKLEFTDOWN", true);
		}
		else if (72 <= angleInDegrees && angleInDegrees <= 108)
		{

			GetAnimator()->TrigerPlay(L"ATTACKLEFT", true);
		}
		else if (108 <= angleInDegrees && angleInDegrees <= 144)
		{

			GetAnimator()->TrigerPlay(L"ATTACKLEFTUP", true);
		}
		else if (144 <= angleInDegrees && angleInDegrees <= 180)
		{

			GetAnimator()->TrigerPlay(L"ATTACKUP", true);
		}


		if (dir.x > 0)
		{
			SetFlipX(true);
		}
		else
		{
			SetFlipX(false);
		}


		if (m_delay[(UINT)BOOSTSTATE::ATTACK] >= 0.3f && m_delay[(UINT)BOOSTSTATE::ATTACKREADY] <= 1.f)
		{
			CCyberCongBullet* bullet = new CCyberCongBullet();
			bullet->m_targetdir = m_vecDir;
			CGameObject::Instantiate(bullet, GetPos(), LAYER::MONSTER);
			m_delay[(UINT)BOOSTSTATE::ATTACK] = 0.f;
		}

		if (m_delay[(UINT)BOOSTSTATE::ATTACKREADY] >= 3.f)
		{
			m_delay[(UINT)BOOSTSTATE::ATTACKREADY] = 0.f;			
			m_booState = BOOSTSTATE::PATROL;
			GetAnimator()->TrigerPlay(L"ATTACKLEFT", true);
		}
		

	
	}
	else if (m_booState == BOOSTSTATE::PATROL)
	{
		m_delay[(UINT)BOOSTSTATE::PATROL] += DELTATIME;

		if (m_delay[(UINT)BOOSTSTATE::PATROL] >= 4.f)
		{
			
			if (RightColState() == false)
			{
				pos.x += 80.f * DELTATIME;
			}

			
			SetFlipX(true);
		}
		else
		{
			if (LeftColState() == false)
			{
				pos.x -= 80.f * DELTATIME;
			}
			
			SetFlipX(false);
		}

		if (m_delay[(UINT)BOOSTSTATE::PATROL] >= 8.f)
		{
			m_booState = BOOSTSTATE::ATTACK;
			m_delay[(UINT)BOOSTSTATE::PATROL] = 0.f;
		}
	}
	
	SetPos(pos);
}
