#include "pch.h"
#include "CCollider.h"
#include "CEngine.h"
#include "CComponent.h"
#include "CGameObject.h"
#include "CCamera.h"
#include "CRockmanObj.h"
#include "CLineCollider.h"
#include"CLineColManager.h"
#include "CCollisionManager.h"

CCollider::CCollider(CGameObject* obj)
	: CComponent(obj)
	, m_iOverlapCount(0)
	, m_hPen(GETINSTANCE(CEngine)->GetPen(PEN_TYPE::GREEN))
	, m_curWallDir{}
{
}

CCollider::CCollider(const CCollider& _other)
	: CComponent(nullptr)
	, m_vOffsetPos(_other.m_vOffsetPos)
	, m_vScale(_other.m_vScale)
	, m_iOverlapCount(0)
	, m_hPen(GETINSTANCE(CEngine)->GetPen(PEN_TYPE::GREEN))
	, m_curWallDir{}
{
}

CCollider::~CCollider()
{
}


void CCollider::tick()
{
	//중첩수가 음수인경우
	assert(!(m_iOverlapCount < 0));
}

void CCollider::final_tick()
{
	//충돌 체의 최종 위치값을 결정한다.
	m_vFinalPos = this->GetOwner()->GetPos() + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
{
	
	if (GETINSTANCE(CCollisionManager)->GetDrawCollide() == false)
		return;
	//충돌체를 그린다.
	HPEN hPen = nullptr;
	if (0 < m_iOverlapCount)
	{
		hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::RED);
	}
	else
	{
		hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::GREEN);
	}

	HBRUSH	hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HPEN	hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH	hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Vector2 vPos = GETINSTANCE(CCamera)->GetRenderPos(m_vFinalPos);

	//Vector2 vPos = GetOwner()->GetPos();

	Rectangle
	(
		_dc
		, (int)(vPos.x - m_vScale.x / 2)
		, (int)(vPos.y - m_vScale.y / 2)
		, (int)(vPos.x + m_vScale.x / 2)
		, (int)(vPos.y + m_vScale.y / 2)
	);

	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);
}

void CCollider::OnTriggerEnter(CCollider* _pOther)
{

	if (LAYER::WALL == _pOther->GetOwner()->GetLayer())
	{
		//충돌방향 셋팅
		//충돌 width와 height 구하기
		//나

		//WALL이라면

		Vector2 lT1 = GetFinalPos() - GetScale() / 2;
		Vector2 lT2 = _pOther->GetFinalPos() - _pOther->GetScale() / 2;

		Vector2 rb1 = GetFinalPos() + GetScale() / 2;
		Vector2 rb2 = _pOther->GetFinalPos() + _pOther->GetScale() / 2;

		LAYER tag1 = GetOwner()->GetLayer();
		LAYER tag2 = _pOther->GetOwner()->GetLayer();

		float left_up_x = max(lT1.x, lT2.x);
		float left_up_y = max(lT1.y, lT2.y);
		float right_down_x = min(rb1.x, rb2.x);
		float right_down_y = min(rb1.y, rb2.y);

		float width = right_down_x - left_up_x;
		float height = right_down_y - left_up_y;

		UINT id = _pOther->GetOwner()->GetID();
		map<UINT, COLLIDE_DIR>::iterator iter = m_mapColdir.find(id);
		if (iter == m_mapColdir.end())
		{
			m_mapColdir.insert(make_pair(id, COLLIDE_DIR::NONE));
			iter = m_mapColdir.find(id);
		}
		CRockmanObj* obj = dynamic_cast<CRockmanObj*>(this->GetOwner());
		CLineCollider* lineCol = nullptr;
		if (nullptr != obj)
		{
			lineCol = obj->m_curLineLand;
		}

		//천장이거나 바닥
		if (width >= height)
		{
			//내가더위에있다면 (y가더작음)
			if (GetFinalPos().y <= _pOther->GetFinalPos().y)
			{
				//이전 프레임 충돌 확인
				iter->second = COLLIDE_DIR::DOWN;
				++m_curWallDir[(UINT)COLLIDE_DIR::DOWN];
				this->GetOwner()->OnTriggerEnterDown(_pOther);
			}
			//천장
			else
			{
				iter->second = COLLIDE_DIR::UP;
				++m_curWallDir[(UINT)COLLIDE_DIR::UP];
				this->GetOwner()->OnTriggerEnterUp(_pOther);
			}
		}
		//왼쪽 혹은 오른쪽
		else
		{
			//왼쪽벽
			if (GetFinalPos().x <= _pOther->GetFinalPos().x)
			{
				if (lineCol != nullptr)
				{
					iter->second = COLLIDE_DIR::DOWN;
					++m_curWallDir[(UINT)COLLIDE_DIR::DOWN];
					this->GetOwner()->OnTriggerEnterDown(_pOther);
				}
				else
				{
					iter->second = COLLIDE_DIR::RIGHT;
					++m_curWallDir[(UINT)COLLIDE_DIR::RIGHT];
					this->GetOwner()->OnTriggerEnterRight(_pOther);
				}
			}
			//오른쪽벽
			else
			{
				if (lineCol != nullptr)
				{
					iter->second = COLLIDE_DIR::DOWN;
					++m_curWallDir[(UINT)COLLIDE_DIR::DOWN];
					this->GetOwner()->OnTriggerEnterDown(_pOther);
				}
				else
				{
					iter->second = COLLIDE_DIR::LEFT;
					++m_curWallDir[(UINT)COLLIDE_DIR::LEFT];
					this->GetOwner()->OnTriggerEnterLeft(_pOther);
				}
			}
		}
	}

	++m_iOverlapCount;
	this->GetOwner()->OnTriggerEnter(_pOther);
}

void CCollider::OnTriggerStay(CCollider* _pOhther)
{

	this->GetOwner()->OnTriggerStay(_pOhther);
}

void CCollider::OnTriggerExit(CCollider* _pOther)
{

	if (LAYER::WALL == _pOther->GetOwner()->GetLayer())
	{
		UINT id = _pOther->GetOwner()->GetID();
		map<UINT, COLLIDE_DIR>::iterator iter = m_mapColdir.find(id);
		if (iter == m_mapColdir.end())
		{
			assert(nullptr);
		}

		//충돌해제시 해당벽과 모든충돌을 해제시키면되는데?
		COLLIDE_DIR prevDir = iter->second;
		switch (prevDir)
		{
		case COLLIDE_DIR::LEFT:
			--m_curWallDir[(UINT)COLLIDE_DIR::LEFT];
			this->GetOwner()->OnTriggerExitLeft(_pOther);
			break;
		case COLLIDE_DIR::UP:
			--m_curWallDir[(UINT)COLLIDE_DIR::UP];
			this->GetOwner()->OnTriggerExitUp(_pOther);
			break;
		case COLLIDE_DIR::RIGHT:
			--m_curWallDir[(UINT)COLLIDE_DIR::RIGHT];
			this->GetOwner()->OnTriggerExitRight(_pOther);
			break;
		case COLLIDE_DIR::DOWN:
			--m_curWallDir[(UINT)COLLIDE_DIR::DOWN];
			this->GetOwner()->OnTriggerExitDown(_pOther);
			break;		
		}
		//find dir!
		iter->second = COLLIDE_DIR::NONE;
	}
	--m_iOverlapCount;
	this->GetOwner()->OnTriggerExit(_pOther);
}


