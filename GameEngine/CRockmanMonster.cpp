#include "pch.h"
#include "CRockmanMonster.h"
#include "CCollider.h"
#include "CTimeManager.h"


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

	//test
	if (m_damagedState == DAMAGED_STATE::DAMAGED)
	{
		m_damagedTime += DELTATIME;
		if (m_damagedTime >= 0.08f)
		{
			m_damagedTime = 0.f;
			m_damagedState = DAMAGED_STATE::IDLE;
		}
	}
	else if (m_damagedState == DAMAGED_STATE::ULTIMAGE)
	{
		//m_damagedState = DAMAGED_STATE::IDLE;
		m_damagedTime = 0.f;
	}
}

void CRockmanMonster::fixed_tick()
{
	CRockmanObj::fixed_tick();
}

void CRockmanMonster::render(HDC _dc)
{
	CRockmanObj::render(_dc);
}

void CRockmanMonster::OnTriggerEnter(CCollider* _pOhter)
{
	if (LAYER::PLAYERATTACK == _pOhter->GetOwner()->GetLayer())
	{
		m_damagedState = DAMAGED_STATE::DAMAGED;
		m_damagedTime = 0.f;
	}
}

void CRockmanMonster::OnTriggerStay(CCollider* _pOhter)
{
}

void CRockmanMonster::OnTriggerExit(CCollider* _pOhter)
{
	//if (LAYER::PLAYERATTACK == _pOhter->GetOwner()->GetLayer())
	//{
	//	m_damagedState = DAMAGED_STATE::IDLE;
	//	m_damagedTime = 0.f;
	//}
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