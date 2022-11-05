#include "pch.h"
#include "CRaycast.h"
#include "CLineCollider.h"

CRaycast::CRaycast()
	:m_arrRay{}
	, m_hoffset(0.f)
	, m_voffset(0.f)
	, m_hdist(0.f)
	, m_vdist(0.f)
{

}

CRaycast::~CRaycast()
{

}

void CRaycast::TranslateSetPos(Vector2 pos)
{
	/*m_arrRay[(UINT)RAY_TYPE::LEFT_UP]->SetRaycast(pos, Vector2(-1.f, 0), Vector2(0.f, -vOffset.y), vhdist.x);
	m_arrRay[(UINT)RAY_TYPE::LEFT_DOWN]->SetRaycast(pos, Vector2(-1.f, 0), Vector2(0.f, +vOffset.y), vhdist.x);
	m_arrRay[(UINT)RAY_TYPE::RIGHT_UP]->SetRaycast(pos, Vector2(+1.f, 0), Vector2(0.f, -vOffset.y), vhdist.x);
	m_arrRay[(UINT)RAY_TYPE::RIGHT_DOWN]->SetRaycast(pos, Vector2(+1.f, 0), Vector2(0.f, +vOffset.y), vhdist.x);
	m_arrRay[(UINT)RAY_TYPE::UP_LEFT]->SetRaycast(pos, Vector2(0.f, -1.f), Vector2(-vOffset.x, 0.f), vhdist.y);
	m_arrRay[(UINT)RAY_TYPE::UP_RIGHT]->SetRaycast(pos, Vector2(0.f, -1.f), Vector2(+vOffset.x, 0.f), vhdist.y);

	m_arrRay[(UINT)RAY_TYPE::DOWN_LEFT]->SetRaycast(pos, Vector2(0.f, +1.f), Vector2(-vOffset.x, 0.f), vhdist.y);
	m_arrRay[(UINT)RAY_TYPE::DOWN_RIGHT]->SetRaycast(pos, Vector2(0.f, +1.f), Vector2(+vOffset.x, 0.f), vhdist.y);
	m_arrRay[(UINT)RAY_TYPE::DOWN]->SetRaycast(pos, Vector2(0.f, +1.f), Vector2(0.f, 0.f), vhdist.y);*/
}

CLineCollider* CRaycast::GetLineCol(RAY_TYPE rayType)
{
	return	m_arrRay[(UINT)rayType];
}

int CRaycast::GetCollideCnt(RAY_TYPE TYPE)
{
	return m_arrRay[(UINT)TYPE]->GetCollideCnt();
}



bool CRaycast::GetDownWallColState()
{
	bool result =
		m_arrRay[(UINT)RAY_TYPE::DOWN_LEFT ]->GetCollideCnt() ||
		m_arrRay[(UINT)RAY_TYPE::DOWN_RIGHT]->GetCollideCnt() ||
		m_arrRay[(UINT)RAY_TYPE::DOWN      ]->GetCollideCnt();
	return result;
}

bool CRaycast::GetLeftWallColState()
{
	bool result =
		m_arrRay[(UINT)RAY_TYPE::LEFT_UP]->GetCollideCnt() ||
		m_arrRay[(UINT)RAY_TYPE::LEFT_DOWN]->GetCollideCnt();
	return result;
}

bool CRaycast::GetRightWallColState()
{
	bool result =
		m_arrRay[(UINT)RAY_TYPE::RIGHT_UP]->GetCollideCnt() ||
		m_arrRay[(UINT)RAY_TYPE::RIGHT_DOWN]->GetCollideCnt();
	return result;
}

bool CRaycast::GetUpWallColState()
{
	bool result =
		m_arrRay[(UINT)RAY_TYPE::UP_LEFT]->GetCollideCnt() ||
		m_arrRay[(UINT)RAY_TYPE::UP_RIGHT]->GetCollideCnt();
	return result;
}
