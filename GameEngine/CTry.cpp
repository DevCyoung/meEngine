#include "pch.h"
#include "CTry.h"
#include "CCollider.h"
#include "CAnimator.h"


CTry::CTry()
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(100.f, 100.f));

	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\try\\idle.anim");
	GetAnimator()->Play(L"IDLE", true);

	m_sponType = MONSETER_TYPE::TRY;
}

CTry::CTry(const CTry& _other)
	: CRockmanMonster(_other)
{

}

CTry::~CTry()
{

}

void CTry::tick()
{
	CRockmanMonster::tick();
}

void CTry::fixed_tick()
{
	CRockmanMonster::fixed_tick();
}

void CTry::render(HDC _dc)
{
	CRockmanMonster::render(_dc);
}
