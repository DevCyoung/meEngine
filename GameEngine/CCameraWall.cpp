#include "pch.h"
#include "CCameraWall.h"

#include "CCamera.h"
#include "CCameraObj.h"
#include "CCollider.h"

CCameraWall::CCameraWall()
	:m_dir{ COLLIDE_DIR::NONE}
{
	m_dir = COLLIDE_DIR::LEFT;
}

CCameraWall::CCameraWall(const CWall& _other)
{

}

CCameraWall::~CCameraWall()
{

}

void CCameraWall::render(HDC _dc)
{
	CGameObject::render(_dc);
	Vector2 pos = GETINSTANCE(CCamera)->GetRenderPos(GetPos());
	
	TextOut(_dc, pos.x, pos.y,     L"CAMERAWALL", 10);
	pos.y += 30.f;

	switch (m_dir)
	{
	case COLLIDE_DIR::LEFT:
		TextOut(_dc, pos.x, pos.y, L"LEFT", 4);
		break;
	case COLLIDE_DIR::UP:
		TextOut(_dc, pos.x, pos.y, L"UP", 2);
		break;
	case COLLIDE_DIR::RIGHT:
		TextOut(_dc, pos.x, pos.y, L"RIGHT", 5);
		break;
	case COLLIDE_DIR::DOWN:
		TextOut(_dc, pos.x, pos.y, L"DOWN", 4);
		break;
	}
}


void CCameraWall::OnTriggerStay(CCollider* _pOther)
{
	Vector2 scale      =   GetCollider()->GetScale();
	Vector2 otherScale =   _pOther->GetScale();

	Vector2 pos =		GetPos();
	Vector2 camPos =	_pOther->GetFinalPos();

	if (_pOther->GetOwner()->GetLayer() == LAYER::CAMERA)
	{
		CCameraObj* camObj = dynamic_cast<CCameraObj*>(_pOther->GetOwner());
		camPos = camObj->m_position;
		switch (m_dir)
		{
		case COLLIDE_DIR::LEFT:
		{
			
			camPos.x = pos.x + scale.x / 2 + otherScale.x / 2 + 1;
		}
			break;
		case COLLIDE_DIR::UP:
		{
			camPos.y = pos.y + scale.y / 2 + otherScale.y / 2 - 1;
		}
			break;
		case COLLIDE_DIR::RIGHT:
		{
			camPos.x = pos.x - scale.x / 2 - otherScale.x / 2 - 1;
		}
			break;
		case COLLIDE_DIR::DOWN:
		{
			camPos.y = pos.y - scale.y / 2 - otherScale.y / 2 + 1;

		}
			break;
		}
		camObj->m_position = camPos;
		//_pOther->GetOwner()->SetPos(camPos);
	}

	
	
}

void CCameraWall::Save(FILE* pFile)
{
	COLLIDE_DIR dir = m_dir;
	fwrite(&dir, sizeof(COLLIDE_DIR), 1, pFile);
	CWall::Save(pFile);
}

void CCameraWall::Load(FILE* pFile)
{
	COLLIDE_DIR dir;
	fread(&dir, sizeof(COLLIDE_DIR), 1, pFile);
	m_dir = dir;
	CWall::Load(pFile);
}
