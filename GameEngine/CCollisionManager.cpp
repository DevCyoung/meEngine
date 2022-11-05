#include "pch.h"
#include "CCollisionManager.h"
#include "CLevel.h"
#include "CLevelManager.h"
#include "CGameObject.h"
#include "CCollider.h"

CCollisionManager::CCollisionManager()
	: m_matrix{}
	, m_isDraw(false)
{
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::tick()
{
	//CLevel* pCurLevel = (CLevel*)GETINSTANCE(CLevelManager)->GetCurLevel();

	for (UINT iRow = 0; iRow < (UINT)LAYER::END; iRow++)
	{
		for (UINT iCol = iRow; iCol < (UINT)LAYER::END; iCol++)
		{
			if (!(m_matrix[iRow] & (1 << iCol)))
				continue;

			//iRow 레이어와 iCol레이어는 서로충돌 검사를 진행한다.
			CollisionBtwLayer(LAYER(iRow), LAYER(iCol));
		}
	}
}

void CCollisionManager::LayerRegister(LAYER _left, LAYER _right)
{
	UINT iRaw = (UINT)_left;
	UINT iCol = (UINT)_right;

	if (iRaw > iCol)
	{
		UINT iTemp = iRaw;
		iRaw = iCol;
		iCol = iTemp;
	}
	this->m_matrix[iRaw] |= (1 << iCol);
}

BOOL CCollisionManager::CollisionBtwCollider(const CCollider* _pleft, const CCollider* _pright)
{
	Vector2 vLeftPos = _pleft->GetFinalPos();
	Vector2 vLeftScale = _pleft->GetScale();
	   
	Vector2 vRightPos = _pright->GetFinalPos();
	Vector2 vRightScale = _pright->GetScale();

	if (fabsf(vLeftPos.x - vRightPos.x) > (vLeftScale.x / 2.f + vRightScale.x / 2))
		return FALSE;
	if (fabsf(vLeftPos.y - vRightPos.y) > (vLeftScale.y / 2.f + vRightScale.y / 2))
		return FALSE;
	return TRUE;
}

void CCollisionManager::CollisionBtwLayer(LAYER _left, LAYER _right)
{
	CLevel* pCurLevel = (CLevel*)GETINSTANCE(CLevelManager)->GetCurLevel();

	//콘스트 레퍼런스이기때문에 const가 붙은 멤버함수만 사용할수있다.
	const vector<CGameObject*>& vecLeft = pCurLevel->GetLayer(_left);
	const vector<CGameObject*>& vecRight = pCurLevel->GetLayer(_right);

	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;
		}

		//동일한 레이어일때 예외처리
		size_t j = 0;
		if (_left == _right)
		{
			j = i;
		}

		for (; j < vecRight.size(); j++)
		{
			if (nullptr == vecRight[j]->GetCollider())
			{
				continue;
			}
			if (vecLeft[i] == vecRight[j])
			{
				continue;
			}

			//두 충돌체의 아이디를 조합.
			CollisionID ID = {};
			ID.LeftID = vecLeft[i]->GetCollider()->GetID();
			ID.RightID = vecRight[j]->GetCollider()->GetID();

			//이전 프레임 충돌 확인
			map<UINT_PTR, BOOL>::iterator iter = m_mapPrevInfo.find(ID.id);

			if (iter == m_mapPrevInfo.end())
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}

 			bool bDead = vecLeft[i]->IsDead() || vecRight[j]->IsDead();

			//지금 겹쳐있다.
			if (CollisionBtwCollider(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{

				//이전에도 겹쳐있었다.
				if (iter->second)
				{
					if (bDead)
					{
						vecLeft[i]->GetCollider()->OnTriggerExit(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnTriggerExit(vecLeft[i]->GetCollider());
					}
					else
					{
						vecLeft[i]->GetCollider()->OnTriggerStay(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnTriggerStay(vecLeft[i]->GetCollider());
					}

				}
				else // 이전에 충돌한적이업다.
				{
					if (!bDead)
					{
						vecLeft[i]->GetCollider()->OnTriggerEnter(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnTriggerEnter(vecLeft[i]->GetCollider());
						iter->second = true;//이거확인 2022 10 02 05:24
					}
					
				}
			}
			else //지금 떨어져있다.
			{
				//이전에는 겹쳐있었다. 아무튼 EndOverlap
				if (iter->second)
				{

					vecLeft[i]->GetCollider()->OnTriggerExit(vecRight[j]->GetCollider());
					vecRight[j]->GetCollider()->OnTriggerExit(vecLeft[i]->GetCollider());
					iter->second = false;
				}
			}
		}
	}
}
