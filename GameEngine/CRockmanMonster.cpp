#include "pch.h"
#include "CRockmanMonster.h"


CRockmanMonster::CRockmanMonster()
{
	SetTag(LAYER::MONSTER);
}

CRockmanMonster::CRockmanMonster(const CRockmanMonster& _other)
	:CRockmanObj(_other)
{
}

CRockmanMonster::~CRockmanMonster()
{
}
void CRockmanMonster::tick()
{
	CRockmanObj::tick();
}

void CRockmanMonster::fixed_tick()
{
	CRockmanObj::fixed_tick();
}

void CRockmanMonster::render(HDC _dc)
{
	CRockmanObj::render(_dc);
}
