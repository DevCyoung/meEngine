#include "pch.h"
#include "CMiru.h"
#include "CAnimator.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CLine.h"
CMiru::CMiru()
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(100.f, 100.f));

	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\miru\\idle.anim");
	GetAnimator()->Play(L"IDLE", true);


	CreateLineCollider();
	GetLineCollider()->SetRaycast(Vector2(-1000.f, -1000.f), Vector2(0.f, -1.f), Vector2(0.f, 0.f), 50.f);
	SetTag(LAYER::MONSTER);
}

CMiru::CMiru(const CMiru& _other)
	:CRockmanMonster(_other)
{
	CreateLineCollider();
	GetLineCollider()->SetRaycast(Vector2(-1000.f, -1000.f), Vector2(0.f, -1.f), Vector2(0.f, 0.f), -50.f);
	SetTag(LAYER::MONSTER);
}

CMiru::~CMiru()
{
}

void CMiru::tick()
{
	CRockmanMonster::tick();

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
