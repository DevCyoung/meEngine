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
	DeletCollider();
}

void CLineColManager::tick()
{
	for (UINT iRow = 0; iRow < (UINT)LAYER::END; iRow++)
	{
		for (UINT iCol = iRow; iCol < (UINT)LAYER::END; iCol++)
		{
			if (!(m_matrix[iRow] & (1 << iCol)))
				continue;

			//iRow ���̾�� iCol���̾�� �����浹 �˻縦 �����Ѵ�.
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


BOOL CLineColManager::CollisionBtwCollider(CLineCollider* _pleft, CLineCollider* _pright)
{
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
		_pleft->m_intersection.x = x1 + (uA * (x2 - x1));
		_pleft->m_intersection.y = y1 + (uA * (y2 - y1));

		_pright->m_intersection.x = x3 + (uB * (x4 - x3));
		_pright->m_intersection.y = y3 + (uB * (y4 - y3));
		return TRUE;
	}
	return FALSE;

	
}
CLineCollider* CLineColManager::CreateLine(Vector2 p1, Vector2 p2, LAYER _layer)
{
	CLineCollider* collider = new CLineCollider(nullptr);
	m_veclineCol[(UINT)_layer].push_back(collider);
	collider->SetP1(p1);
	collider->SetP2(p2);
	collider->m_layer = _layer;
	return collider;
}

void CLineColManager::CollisionBtwLayer(LAYER _left, LAYER _right)
{
	//CLevel* pCurLevel = (CLevel*)GETINSTANCE(CLevelManager)->GetCurLevel();

	//�ܽ�Ʈ ���۷����̱⶧���� const�� ���� ����Լ��� ����Ҽ��ִ�.
	const vector<CLineCollider*>& vecLeft = m_veclineCol[(UINT)_left];
	const vector<CLineCollider*>& vecRight = m_veclineCol[(UINT)_right];

	for (size_t i = 0; i < vecLeft.size(); i++)
	{		
		//������ ���̾��϶� ����ó��
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

			//�� �浹ü�� ���̵� ����.
			CLineColliderID ID = {};
			ID.LeftID = vecLeft[i]->GetID();
			ID.RightID = vecRight[j]->GetID();

			//���� ������ �浹 Ȯ��
			map<UINT_PTR, BOOL>::iterator iter = m_mapPrevInfo.find(ID.id);

			if (iter == m_mapPrevInfo.end())
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}

			//bool bDead = vecLeft[i]->IsDead() || vecRight[j]->IsDead();
			bool bDead = false;

			//���� �����ִ�.
			if (CollisionBtwCollider(vecLeft[i], vecRight[j]) == TRUE)
			{

				//�������� �����־���.
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
				else // ������ �浹�����̾���.
				{
					if (!bDead)
					{
						vecLeft[i]->OnTriggerEnter(vecRight[j]);
						vecRight[j]->OnTriggerEnter(vecLeft[i]);
						iter->second = true;//�̰�Ȯ�� 2022 10 02 05:24
					}

				}
			}
			else //���� �������ִ�.
			{
				//�������� �����־���. �ƹ�ư EndOverlap
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




void CLineColManager::RemoveLine(CLineCollider* line)
{
	if (nullptr == line)
		return;

	for (size_t i = 0; i < m_veclineCol[(UINT)line->m_layer].size(); i++)
	{
		if (m_veclineCol[(UINT)line->m_layer][i] == line)
		{
			CLineCollider* lineCol = m_veclineCol[(UINT)line->m_layer][i];
			m_veclineCol[(UINT)line->m_layer].erase(m_veclineCol[(UINT)line->m_layer].begin() + i);
			delete lineCol;
			return;
		}
	}
}

void CLineColManager::DeletCollider()
{
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		for (size_t j = 0; j < m_veclineCol[i].size(); j++)
		{
			delete m_veclineCol[i][j];
		}
		m_veclineCol[i].clear();
	}
}

void CLineColManager::Save(FILE* _pFile)
{

	size_t count = 0;
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		count += m_veclineCol[i].size();
	}

	fwrite(&count, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		for (size_t j = 0; j < m_veclineCol[i].size(); j++)
		{
			CLineCollider lineCol = *m_veclineCol[i][j];
			fwrite(&lineCol.m_vP1   ,sizeof(Vector2) ,1 , _pFile);
			fwrite(&lineCol.m_vP2   ,sizeof(Vector2) ,1 , _pFile);
			fwrite(&lineCol.m_dir   ,sizeof(WALLDIR) ,1 , _pFile);
			fwrite(&lineCol.m_layer ,sizeof(LAYER)   ,1 , _pFile);

		}
	}
}

void CLineColManager::Load(FILE* _pFile)
{
	DeletCollider();
	size_t count = 0;
	fread(&count, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < count; i++)
	{
		Vector2 vP1;
		Vector2 vP2;
		WALLDIR	dir;
		LAYER	layer;
		fread(&vP1,		sizeof(Vector2), 1, _pFile);
		fread(&vP2,		sizeof(Vector2), 1, _pFile);
		fread(&dir,		sizeof(WALLDIR)  , 1, _pFile);
		fread(&layer,   sizeof(LAYER), 1, _pFile);
		GETINSTANCE(CLineColManager)->CreateLine(vP1, vP2, layer)->m_dir = dir;
	}
}
