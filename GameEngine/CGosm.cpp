#include "pch.h"
#include "CGosm.h"
#include "CAnimator.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CRigidbody.h"
#include "CLine.h"
#include "CTimeManager.h"

CGosm::CGosm()
	: m_time(0.f)
	, m_state{}
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(80.f, 100.f));

	CreateRockmanRrigidbody();	


	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\gosm\\attack.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\gosm\\attackready.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\gosm\\idle.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\gosm\\returnidle.anim");
	
	GetAnimator()->Play(L"IDLE", true);

	m_state = GOSM_STATE::IDLE;
	m_time = 0.f;

	m_sponType = MONSETER_TYPE::GOSM;
}

CGosm::CGosm(const CGosm& _other)
	:CRockmanMonster(_other)
{
	m_state = GOSM_STATE::IDLE;
	m_time = 0.f;

}

CGosm::~CGosm()
{
}


void CGosm::tick()
{


	Vector2 velo = GetRigidbody()->GetVelocity();
	velo.x = 0.f;
	m_time += DELTATIME;

	if (m_state == GOSM_STATE::IDLE)
	{
		//GetAnimator()->TrigerPlay(L"IDLE", true);
		if (m_time >= 1.5f)
		{
			SetFlipX(!GetFilpX());
			GetAnimator()->TrigerPlay(L"ATTACKREADY", false);
			m_state = GOSM_STATE::ATTACKREADY;
			m_time = 0.f;
		}
	}
	else if (m_state == GOSM_STATE::ATTACKREADY)
	{
		if (m_time >= 1.0f)
		{
			GetAnimator()->TrigerPlay(L"ATTACK", true);
			m_state = GOSM_STATE::ATTACK;
			m_time = 0.f;
		}
	}
	else if (m_state == GOSM_STATE::ATTACK)
	{
		if (m_time <= 1.0f)
			return;
		if (m_time <= 3.8f)
		{			
			if (GetFilpX() == false)
			{
				
				if (LeftColState() == false)
					velo.x = -500.f;
				else
				{
					velo.y = -300.f;
				}
				
			}				
			else
			{
				if (RightColState() == false)
					velo.x = +500.f;
				else
				{
					velo.y = -300.f;
				}
			}
				
			GetRigidbody()->SetVelocity(velo);
		}
		else if (m_time > 4.5f)
		{			
			GetAnimator()->TrigerPlay(L"RETURNIDLE", false);	
		}
		if (m_time > 5.0f)
		{
			GetAnimator()->TrigerPlay(L"IDLE", true);
			m_state = GOSM_STATE::IDLE;
			m_time = 0.f;
		}
		
	}

	

	GetRigidbody()->SetVelocity(velo);

	CRockmanMonster::tick();
}

void CGosm::fixed_tick()
{
	CRockmanMonster::fixed_tick();
}

void CGosm::render(HDC _dc)
{
	CRockmanMonster::render(_dc);
}

