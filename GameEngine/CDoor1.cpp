#include "pch.h"
#include "CDoor1.h"

#include "CCollider.h"
#include "CCamera.h"
#include "CCollisionManager.h"

CDoor1::CDoor1()
{
	m_mode = COLIDE_EIDT_MODE::BOSSDOOR2BOX;
}

CDoor1::~CDoor1()
{

}

void CDoor1::Save(FILE* pFile)
{
	Vector2 pos = GetPos();
	Vector2 scale = GetCollider()->GetScale();

	fwrite(&pos, sizeof(Vector2), 1, pFile);
	fwrite(&scale, sizeof(Vector2), 1, pFile);
}

void CDoor1::Load(FILE* pFile)
{
	Vector2 pos;
	Vector2 scale;

	fread(&pos, sizeof(Vector2), 1, pFile);
	fread(&scale, sizeof(Vector2), 1, pFile);

	GetCollider()->SetScale(scale);
	SetPos(pos);

}


void CDoor1::tick()
{
	CEventBox::tick();
}


void CDoor1::render(HDC _dc)
{
	CEventBox::render(_dc);

	if (GETINSTANCE(CCollisionManager)->GetDrawCollide())
	{
		Vector2 pos = GETINSTANCE(CCamera)->GetRenderPos(GetPos());
		TextOut(_dc, pos.x, pos.y, L"DOOR1", 5);
	}

}

void CDoor1::OnTriggerEnter(CCollider* _pOther)
{
	if (LAYER::PLAYER == _pOther->GetOwner()->GetLayer())
	{
		CEventBox::OnTriggerEnter(_pOther);
	}
}
