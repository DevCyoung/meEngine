#include "pch.h"
#include "CRockmanObj.h"

CRockmanObj::CRockmanObj()
{
	
}

CRockmanObj::CRockmanObj(const CRockmanObj& _other)
{
}

CRockmanObj::~CRockmanObj()
{
}


void CRockmanObj::tick()
{
	CGameObject::tick();
}

void CRockmanObj::fixed_tick()
{
	CGameObject::fixed_tick();
}

void CRockmanObj::render(HDC _dc)
{
	//�浹ü�� �׸���
	CGameObject::render(_dc);
}



void CRockmanObj::OnTriggerEnter(CCollider* _pOhter)
{
}

void CRockmanObj::OnTriggerStay(CCollider* _pOhter)
{
}

void CRockmanObj::OnTriggerExit(CCollider* _pOhter)
{
}