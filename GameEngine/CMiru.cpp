#include "pch.h"
#include "CMiru.h"
#include "CAnimator.h"
#include "CCamera.h"

CMiru::CMiru()
{
	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\miru\\idle.anim");

	//GetAnimator()->LoadAnimation(L"animation\\zero\\thunder.anim");
	GetAnimator()->Play(L"IDLE", true);
	SetTag(LAYER::MONSTER);
}

CMiru::CMiru(const CMiru& _other)
	:CRockmanMonster(_other)
{
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
