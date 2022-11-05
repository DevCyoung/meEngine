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
	//��ø���� �����ΰ��
	assert(!(m_iOverlapCount < 0));
}

void CCollider::final_tick()
{
	//�浹 ü�� ���� ��ġ���� �����Ѵ�.
	m_vFinalPos = this->GetOwner()->GetPos() + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
{
	
	if (GETINSTANCE(CCollisionManager)->GetDrawCollide() == false)
		return;
	//�浹ü�� �׸���.
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
		//�浹���� ����
		//�浹 width�� height ���ϱ�
		//��

		//WALL�̶��

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

		//õ���̰ų� �ٴ�
		if (width >= height)
		{
			//�����������ִٸ� (y��������)
			if (GetFinalPos().y <= _pOther->GetFinalPos().y)
			{
				//���� ������ �浹 Ȯ��
				iter->second = COLLIDE_DIR::DOWN;
				++m_curWallDir[(UINT)COLLIDE_DIR::DOWN];
				this->GetOwner()->OnTriggerEnterDown(_pOther);
			}
			//õ��
			else
			{
				iter->second = COLLIDE_DIR::UP;
				++m_curWallDir[(UINT)COLLIDE_DIR::UP];
				this->GetOwner()->OnTriggerEnterUp(_pOther);
			}
		}
		//���� Ȥ�� ������
		else
		{
			//���ʺ�
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
			//�����ʺ�
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

		//�浹������ �ش纮�� ����浹�� ������Ű��Ǵµ�?
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


