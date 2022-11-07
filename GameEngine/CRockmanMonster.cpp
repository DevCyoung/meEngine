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


void CRockmanMonster::Save(FILE* pFile)
{
	MONSTER_STATE monState	 = m_monsterState;
	fwrite(&monState , sizeof(MONSTER_STATE), 1, pFile);

	Vector2 Pos = GetPos();
	fwrite(&Pos, sizeof(Vector2), 1, pFile);

}
void CRockmanMonster::Load(FILE* pFile)
{
	MONSTER_STATE monState;
	fread(&monState, sizeof(MONSTER_STATE), 1, pFile);

	Vector2 pos;
	fread(&pos, sizeof(Vector2), 1, pFile);

	m_monsterState = monState;
	SetPos(pos);
}