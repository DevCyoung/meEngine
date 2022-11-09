#include "pch.h"
#include "CNextArea.h"
#include "CCollider.h"
#include "CCamera.h"
#include "CCollisionManager.h"

CNextArea::CNextArea()
{
	m_mode = COLIDE_EIDT_MODE::NEXTAREAEBOX;
}

CNextArea::~CNextArea()
{
}

void CNextArea::Save(FILE* pFile)
{
	Vector2 pos = GetPos();
	Vector2 scale = GetCollider()->GetScale();

	fwrite(&pos, sizeof(Vector2), 1, pFile);
	fwrite(&scale, sizeof(Vector2), 1, pFile);
}

void CNextArea::Load(FILE* pFile)
{
	Vector2 pos;
	Vector2 scale;

	fread(&pos, sizeof(Vector2), 1, pFile);
	fread(&scale, sizeof(Vector2), 1, pFile);

	GetCollider()->SetScale(scale);
	SetPos(pos);

}


void CNextArea::tick()
{
	CEventBox::tick();
}

void CNextArea::render(HDC _dc)
{
	CEventBox::render(_dc);

	if (GETINSTANCE(CCollisionManager)->GetDrawCollide())
	{
		Vector2 pos = GETINSTANCE(CCamera)->GetRenderPos(GetPos());
		TextOut(_dc, pos.x, pos.y, L"NEXTAREA", 8);
	}
	
}

void CNextArea::OnTriggerEnter(CCollider* _pOther)
{
	if (LAYER::PLAYER == _pOther->GetOwner()->GetLayer())
	{
		CEventBox::OnTriggerEnter(_pOther);
	}	
}
