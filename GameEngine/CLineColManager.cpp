#include "pch.h"
#include "CLineColManager.h"
#include "CLevel.h"
#include "CLevelManager.h"
#include "CGameObject.h"
#include "CLineCollider.h"

CLineColManager::CLineColManager()
	:m_matrix{}
	,m_veclineCol{}
{
}

CLineColManager::~CLineColManager()
{
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		for (size_t j = 0; j < m_veclineCol[i].size(); j++)
		{
			delete m_veclineCol[i][j];
		}		
	}
}

void CLineColManager::tick()
{
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
void CLineColManager::render(HDC _dc)
{
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		for (size_t j = 0; j < m_veclineCol[i].size(); j++)
		{
			m_veclineCol[i][j]->render(_dc);
		}
	}
}
void CLineColManager::LayerRegister(LAYER _left, LAYER _right)
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


BOOL CLineColManager::CollisionBtwCollider(const CLineCollider* _pleft, const CLineCollider* _pright)
{
	/*Vector2 vLeftPos = _pleft->GetFinalPos();
	Vector2 vLeftScale = _pleft->GetScale();

	Vector2 vRightPos = _pright->GetFinalPos();
	Vector2 vRightScale = _pright->GetScale();*/
	float x1 = _pleft->GetP1().x;
	float y1 = _pleft->GetP1().y;
	float x2 = _pleft->GetP2().x;
	float y2 = _pleft->GetP2().y;

	float x3 = _pright->GetP1().x;
	float y3 = _pright->GetP1().y;
	float x4 = _pright->GetP2().x;
	float y4 = _pright->GetP2().y;

	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) 
	{
		return TRUE;
	}
	return FALSE;

	/*float intersectionX = x1 + (uA * (x2 - x1));
	float intersectionY = y1 + (uA * (y2 - y1));*/
}
CLineCollider* CLineColManager::CreateLine(Vector2 p1, Vector2 p2, LAYER _layer)
{
	CLineCollider* collider = new CLineCollider(nullptr);
	m_veclineCol[(UINT)_layer].push_back(collider);
	collider->SetP1(p1);
	collider->SetP2(p2);
	return collider;
}
void CLineColManager::CollisionBtwLayer(LAYER _left, LAYER _right)
{
	//CLevel* pCurLevel = (CLevel*)GETINSTANCE(CLevelManager)->GetCurLevel();

	//콘스트 레퍼런스이기때문에 const가 붙은 멤버함수만 사용할수있다.
	const vector<CLineCollider*>& vecLeft = m_veclineCol[(UINT)_left];
	const vector<CLineCollider*>& vecRight = m_veclineCol[(UINT)_right];

	for (size_t i = 0; i < vecLeft.size(); i++)
	{		
		//동일한 레이어일때 예외처리
		size_t j = 0;
		if (_left == _right)
		{
			j = i;
		}

		for (; j < vecRight.size(); j++)
		{			
			if (vecLeft[i] == vecRight[j])
			{
				continue;
			}

			//두 충돌체의 아이디를 조합.
			CLineColliderID ID = {};
			ID.LeftID = vecLeft[i]->GetID();
			ID.RightID = vecRight[j]->GetID();

			//이전 프레임 충돌 확인
			map<UINT_PTR, BOOL>::iterator iter = m_mapPrevInfo.find(ID.id);

			if (iter == m_mapPrevInfo.end())
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}

			//bool bDead = vecLeft[i]->IsDead() || vecRight[j]->IsDead();
			bool bDead = false;

			//지금 겹쳐있다.
			if (CollisionBtwCollider(vecLeft[i], vecRight[j]) == TRUE)
			{

				//이전에도 겹쳐있었다.
				if (iter->second)
				{
					if (bDead)
					{
						vecLeft[i]->OnTriggerExit(vecRight[j]);
						vecRight[j]->OnTriggerExit(vecLeft[i]);
					}
					else
					{
						vecLeft[i]->OnTriggerStay(vecRight[j]);
						vecRight[j]->OnTriggerStay(vecLeft[i]);
					}

				}
				else // 이전에 충돌한적이업다.
				{
					if (!bDead)
					{
						vecLeft[i]->OnTriggerEnter(vecRight[j]);
						vecRight[j]->OnTriggerEnter(vecLeft[i]);
						iter->second = true;//이거확인 2022 10 02 05:24
					}

				}
			}
			else //지금 떨어져있다.
			{
				//이전에는 겹쳐있었다. 아무튼 EndOverlap
				if (iter->second)
				{

					vecLeft[i]->OnTriggerExit(vecRight[j]);
					vecRight[j]->OnTriggerExit(vecLeft[i]);
					iter->second = false;
				}
			}
		}
	}
}

