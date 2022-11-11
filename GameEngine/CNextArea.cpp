#include "pch.h"
#include "CNextArea.h"
#include "CCollider.h"
#include "CCamera.h"
#include "CCollisionManager.h"
#include "CEventManager.h"
#include "CZero.h"
#include "CRigidbody.h"
#include "CTimeManager.h"
#include "CAnimator.h"

#include "CLevelManager.h"
#include "CLevel.h"
#include "CRockmanLevel.h"

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
	if (nullptr == m_zero)
		return;
	//Vector2  velo = m_zero->GetPos();

	//if (m_zero->GetState() == PLAYER_STATE::RETURN)
	//{		
	//	velo.y = -300.f;
	//	m_zero->GetRigidbody()->SetVelocity(velo);
	//}
	//else if (m_zero->DownColState() == true)
	//{			
	//	if (m_zero->GetState() == PLAYER_STATE::RETURNREADY)
	//	{
	//		m_zero->GetRigidbody()->SetGravity(false);
	//		m_zero->GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));
	//		m_zero->SetState(PLAYER_STATE::RETURN);
	//	}	
	//}
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
	if (_pOther->GetOwner()->GetLayer() != LAYER::PLAYER)
		return;
	CEventBox::OnTriggerEnter(_pOther);		
	if (m_bCollison == true)
		return;
	m_zero->SetState(PLAYER_STATE::RETURNREADY);

	CLevel* level = GETINSTANCE(CLevelManager)->GetCurLevel();
	CRockmanLevel* rmLevel = dynamic_cast<CRockmanLevel*>(level);
	assert(rmLevel);
	rmLevel->NextLevel();
	this->Destroy();
}
