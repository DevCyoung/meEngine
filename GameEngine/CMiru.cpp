#include "pch.h"
#include "CMiru.h"
#include "CAnimator.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CLine.h"
#include "CTimeManager.h"
	
CMiru::CMiru()
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(100.f, 100.f));

	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\miru\\move.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\miru\\idle.anim");
	GetAnimator()->Play(L"MOVE", true);

	CreateRockmanRrigidbody();

	//CreateLineCollider();
	//GetLineCollider()->SetRaycast(Vector2(-1000.f, -1000.f), Vector2(0.f, -1.f), Vector2(0.f, 0.f), 50.f);
	//SetTag(LAYER::MONSTER);
	m_sponType = MONSETER_TYPE::MIRU;
}

CMiru::CMiru(const CMiru& _other)
	:CRockmanMonster(_other)
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

	
	

	if (m_monsterState == MONSTER_STATE::TYPE1)
	{
		pos.x += 500.f * DELTATIME;
	}
	if (m_monsterState == MONSTER_STATE::TYPE2)
	{
		pos.x -= 500.f * DELTATIME;
	}
	if (m_monsterState == MONSTER_STATE::TYPE3)
	{
		pos.y += 500.f * DELTATIME;
	}
	if (m_monsterState == MONSTER_STATE::TYPE4)
	{
		pos.y -= 500.f * DELTATIME;
	}
	//SetPos(pos);
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
}

void CMiru::OnTriggerStay(CCollider* _pOhter)
{
}

void CMiru::OnTriggerExit(CCollider* _pOhter)
{
}
