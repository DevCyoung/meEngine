#include "pch.h"
#include "CMiru.h"
#include "CAnimator.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CLine.h"
#include "CTimeManager.h"
	
CMiru::CMiru()
	:m_leftSpeed(0.f)
	,m_rightSpeed(0.f)
	,m_defaultSpeed(200.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(100.f, 100.f));

	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\miru\\move.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\miru\\idle.anim");
	GetAnimator()->TrigerPlay(L"IDLE", true);

	

	//CreateRockmanRrigidbody();

	//CreateLineCollider();
	//GetLineCollider()->SetRaycast(Vector2(-1000.f, -1000.f), Vector2(0.f, -1.f), Vector2(0.f, 0.f), 50.f);
	//SetTag(LAYER::MONSTER);
	m_sponType = MONSETER_TYPE::MIRU;
	m_damagedState = DAMAGED_STATE::ULTIMAGE;

	m_rightSpeed = m_defaultSpeed;
	m_leftSpeed  = -m_defaultSpeed;
	m_startLen = 1000.f;

	
}

CMiru::CMiru(const CMiru& _other)
	:CRockmanMonster(_other)
	, m_leftSpeed(0.f)
	, m_rightSpeed(0.f)
	, m_defaultSpeed(200.f)
{
	/*CreateLineCollider();
	GetLineCollider()->SetRaycast(Vector2(-1000.f, -1000.f), Vector2(0.f, -1.f), Vector2(0.f, 0.f), -50.f);*/
	//SetTag(LAYER::MONSTER);
}

CMiru::~CMiru()
{
}

void CMiru::tick()
{
	CRockmanMonster::tick();
	Vector2 pos = GetPos();

	if (m_isStart == false)
	{
		return;
	}

	if (m_monsterState == MONSTER_STATE::TYPE1 || m_monsterState == MONSTER_STATE::TYPE2)
	{

		GetAnimator()->TrigerPlay(L"MOVE", true);
	}
	else
	{
		GetAnimator()->TrigerPlay(L"IDLE", true);
	}

	if (m_monsterState == MONSTER_STATE::TYPE1 )
	{
		pos.x += m_leftSpeed * DELTATIME;
	}
	if (m_monsterState == MONSTER_STATE::TYPE2)
	{
		pos.x += m_rightSpeed * DELTATIME;
	}
	
	SetPos(pos);
}

void CMiru::fixed_tick()
{
	CRockmanMonster::fixed_tick();
}

void CMiru::render(HDC _dc)
{
	CRockmanMonster::render(_dc);
}

void CMiru::OnTriggerEnter(CCollider* _pOhter)
{
	CRockmanMonster::OnTriggerEnter(_pOhter);

	if (m_monsterState == MONSTER_STATE::TYPE3)
	{
		return;
	}


	if (_pOhter->GetOwner()->GetLayer() == LAYER::PLAYERATTACK)
	{		

		if (m_vecDir.x > 0)
		{
			if (m_monsterState == MONSTER_STATE::TYPE1)
			{
				m_rightSpeed -= 70.f;
			}
			else
			{
				m_leftSpeed = -m_defaultSpeed;
			}

			m_monsterState = MONSTER_STATE::TYPE1;
		}
		else
		{
			if (m_monsterState == MONSTER_STATE::TYPE2)
			{
				m_rightSpeed += 70.f;
			}
			else
			{
				m_rightSpeed = m_defaultSpeed;
			}

			m_monsterState = MONSTER_STATE::TYPE2;
		}


	}
}

void CMiru::OnTriggerStay(CCollider* _pOhter)
{
}

void CMiru::OnTriggerExit(CCollider* _pOhter)
{
}
