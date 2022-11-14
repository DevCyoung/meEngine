#include "pch.h"
#include "CCong.h"
#include "CAnimator.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CLine.h"
#include "CTimeManager.h"
#include "CRigidbody.h"
#include "CAnimation.h"

#include "CCongBullet.h"

CCong::CCong()
	: m_time{}
	, m_state(CONG_STATE::NONE)
	, m_move{}
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(40.f, 70.f));
	
	CreateRockmanRrigidbody();


	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\cong\\idle.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\cong\\attack.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\cong\\falling.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\cong\\hide.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\cong\\jump.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\cong\\move.anim");

	GetAnimator()->FindAnimation(L"ATTACK")->SetFrameEvent(4, this, (DELEGATE)&CCong::BulletEvent);

	GetAnimator()->Play(L"MOVE", true);

	m_state = CONG_STATE::PATROL;	
	m_sponType = MONSETER_TYPE::CONG;
	m_move.x = 110.f;
	m_move.y = 500.f;

	//NONE상태였다가 카메라충돌시 움직임
	m_hp = 1;
}

CCong::CCong(const CCong& _other)
	: m_time{}
	, m_state(CONG_STATE::NONE)
	, m_move{}
{
}

CCong::~CCong()
{
}



void CCong::tick()
{
	CRockmanMonster::tick();

	Vector2 pos = GetPos();
	Vector2 velo = GetRigidbody()->GetVelocity();


	if (m_isStart == false)
	{
		return;
	}


	if (DownColState() == false && m_state != CONG_STATE::FALLING)
	{
		ToFalling();
	}

	switch (m_state)
	{
	case CONG_STATE::NONE:
		break;
	case CONG_STATE::IDLE:
		break;
	case CONG_STATE::PATROL:
	{
		m_time[(UINT)CONG_STATE::PATROL] += DELTATIME;

		if (m_time[(UINT)CONG_STATE::PATROL] >= 8.f)
		{
			velo.x = m_move.x * -1.f;
		}
		else
		{
			velo.x = m_move.x;
		}

		if (m_time[(UINT)CONG_STATE::PATROL] >= 16.f)
		{
			m_time[(UINT)CONG_STATE::PATROL] = 0.f;
		}

		int frmIdx = GetAnimator()->GetCurAnimation()->GetCurFrameIdx();
		if (frmIdx == 5 || frmIdx == 6 || frmIdx == 0 || frmIdx == 1)
		{
			velo.x = 0.f;
		}

		//if (m_vecLen.x <= 350.f && m_vecLen.x <= 300.f)
		//{
		//	ToAttack();
		//}
		if (m_vecLen.x <= 250.f)
		{
			if (rand() % 2 == 0)
			{
				ToHide();
			}
			else
			{
				ToAttack();
			}
			
		}


	}
		break;
	case CONG_STATE::FALLING:
	{
		if (DownColState() == true)
		{
			m_state = CONG_STATE::PATROL;
			GetAnimator()->Play(L"MOVE", true);
		}
	}
		break;
	case CONG_STATE::JUMP:
		break;
	case CONG_STATE::HIDE:
	{
		m_time[(UINT)CONG_STATE::HIDE] += DELTATIME;

		if (m_CurstartLen >= 450.f)
		{
			ToPatrol();
		}
		else if (m_time[(UINT)CONG_STATE::HIDE] >= 2.f)
		{
			ToAttack();
		}
		
	}
		break;
	case CONG_STATE::ATTACK:
	{
		m_time[(UINT)CONG_STATE::ATTACK] += DELTATIME;

		if (m_CurstartLen >= 500.f)
		{
			ToPatrol();
		}
		else if (m_time[(UINT)CONG_STATE::ATTACK] >= 2.f)
		{
			ToHide();
		}
	}
		break;	

	}

	if (LeftColState() == true && velo.x < 0)
	{
		velo.x *= -1;
		m_time[(UINT)CONG_STATE::PATROL] = 0.f;
	}


	if (RightColState() == true && velo.x > 0)
	{
		velo.x *= -1;
		m_time[(UINT)CONG_STATE::PATROL] = 8.f;
	}


	

	//AttackFlip
	if (m_state == CONG_STATE::ATTACK || m_state == CONG_STATE::HIDE)
	{
		if (m_vecDir.x < 0)
		{
			SetFlipX(false);
		}
		else
		{
			SetFlipX(true);
		}
	}


	GetRigidbody()->SetVelocity(velo);

}

void CCong::fixed_tick()
{

	CRockmanMonster::fixed_tick();
}

void CCong::render(HDC _dc)
{
	CRockmanMonster::render(_dc);
}
void CCong::OnTriggerEnter(CCollider* _pOhter)
{
	CRockmanMonster::OnTriggerEnter(_pOhter);
}

void CCong::OnTriggerStay(CCollider* _pOhter)
{
}

void CCong::OnTriggerExit(CCollider* _pOhter)
{
}


void CCong::ToHide()
{
	m_state = CONG_STATE::HIDE;
	m_time[(UINT)CONG_STATE::HIDE] = 0.f;
	GetAnimator()->TrigerPlay(L"HIDE", false);
	m_damagedState = DAMAGED_STATE::ULTIMAGE;	
}

void CCong::ToPatrol()
{
	m_state = CONG_STATE::PATROL;
	m_time[(UINT)CONG_STATE::PATROL] = 0.f;
	GetAnimator()->TrigerPlay(L"MOVE", true);
	m_damagedState = DAMAGED_STATE::IDLE;
	
}

void CCong::ToAttack()
{
	m_state = CONG_STATE::ATTACK;
	m_time[(UINT)CONG_STATE::ATTACK] = 0.f;
	GetAnimator()->TrigerPlay(L"ATTACK", true);	
	m_damagedState = DAMAGED_STATE::IDLE;
}

void CCong::ToFalling()
{
	m_state = CONG_STATE::FALLING;
	m_time[(UINT)CONG_STATE::FALLING] = 0.f;
	GetAnimator()->TrigerPlay(L"FALLING", true);
	m_damagedState = DAMAGED_STATE::IDLE;
}

void CCong::BulletEvent()
{
	CCongBullet* bullet = new CCongBullet();
	Vector2 pos = GetPos();
	Vector2 offset = {};
	
	offset.y = 17.f;
	//offset.x = m_vecDir.x * 3.f;
	if (m_vecDir.x < 0)
	{
		offset.x = -5.f;
	}
	else
	{
		offset.x = +5.f;
	}

	pos += offset;
	bullet->m_dir = m_vecDir;
	CGameObject::Instantiate(bullet, pos, LAYER::MONSTERATTACK);
}

