#include "pch.h"
#include "CLineColManager.h"
#include "CLevel.h"
#include "CLevelManager.h"
#include "CGameObject.h"
#include "CLineCollider.h"
#include "CRaycast.h"

CLineColManager::CLineColManager()
	:m_matrix{}
	,m_veclineCol{}
	,m_isDraw(false)
	, m_curMap(nullptr)
{
}

CLineColManager::~CLineColManager()
{
	DeletCollider();
}

void CLineColManager::tick()
{
	for (UINT iRow = 0; iRow < (UINT)LINELAYER::END; iRow++)
	{
		for (UINT iCol = iRow; iCol < (UINT)LINELAYER::END; iCol++)
		{
			if (!(m_matrix[iRow] & (1 << iCol)))
				continue;

			//iRow 레이어와 iCol레이어는 서로충돌 검사를 진행한다.
			CollisionBtwLayer(LINELAYER(iRow), LINELAYER(iCol));
		}
	}

	fixed_tick();
}

void CLineColManager::fixed_tick()
{
	for (size_t i = 0; i < m_vecFixedEvent.size(); i++)
	{
		(m_vecFixedEvent[i].instance->*m_vecFixedEvent[i].func)();
	}
}

void CLineColManager::render(HDC _dc)
{
	if (m_isDraw == true)
	{
		for (size_t i = 0; i < (UINT)LINELAYER::END; i++)
		{
			for (size_t j = 0; j < m_veclineCol[i].size(); j++)
			{
				m_veclineCol[i][j]->render(_dc);
			}
		}
	}
}
void CLineColManager::LayerRegister(LINELAYER _left, LINELAYER _right)
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
void CLineColManager::AddFixedTick(DELEGATE func, CEntity* instance)
{
	m_vecFixedEvent.push_back(tFixedEvent{ func, instance });
}
CLineCollider* CLineColManager::CreateLine(Vector2 p1, Vector2 p2, LINELAYER _layer)
{
	CLineCollider* collider = new CLineCollider(nullptr);
	m_veclineCol[(UINT)_layer].push_back(collider);
	collider->SetP1(p1);
	collider->SetP2(p2);
	collider->m_layer = _layer;
	return collider;
}

CLineCollider* CLineColManager::CreateRay(Vector2 point, Vector2 dir, Vector2 offset, float distance, LINELAYER _layer)
{
	CLineCollider* collider = new CLineCollider(nullptr);
	m_veclineCol[(UINT)_layer].push_back(collider);
	collider->SetRaycast(point, dir, offset,distance);
	return collider;
}

void CLineColManager::CreateRaycast(CRaycast& ray, Vector2 vOffset, Vector2 vhdist)
{
	ray.m_arrRay[(UINT)RAY_TYPE::LEFT_UP]		 = CreateRay(Vector2(0.0f, 0.f), Vector2(-1.f, 0), Vector2(0.f, -vOffset.y),  vhdist.x, LINELAYER::LEFT);
	ray.m_arrRay[(UINT)RAY_TYPE::LEFT_DOWN]		 = CreateRay(Vector2(0.0f, 0.f), Vector2(-1.f, 0), Vector2(0.f, +vOffset.y),  vhdist.x, LINELAYER::LEFT);

	ray.m_arrRay[(UINT)RAY_TYPE::RIGHT_UP]		 = CreateRay(Vector2(0.0f, 0.f), Vector2(+1.f, 0), Vector2(0.f, -vOffset.y),  vhdist.x, LINELAYER::RIGHT);
	ray.m_arrRay[(UINT)RAY_TYPE::RIGHT_DOWN]	 = CreateRay(Vector2(0.0f, 0.f), Vector2(+1.f, 0), Vector2(0.f, +vOffset.y),  vhdist.x, LINELAYER::RIGHT);

	ray.m_arrRay[(UINT)RAY_TYPE::UP_LEFT]		 = CreateRay(Vector2(0.0f, 0.f), Vector2(0.f, -1.f), Vector2(-vOffset.x, 0.f), vhdist.y, LINELAYER::UP);
	ray.m_arrRay[(UINT)RAY_TYPE::UP_RIGHT]		 = CreateRay(Vector2(0.0f, 0.f), Vector2(0.f, -1.f), Vector2(+vOffset.x, 0.f), vhdist.y, LINELAYER::UP);

	ray.m_arrRay[(UINT)RAY_TYPE::DOWN_LEFT]		 = CreateRay(Vector2(0.0f, 0.f), Vector2(0.f, +1.f), Vector2(-vOffset.x, 0.f), vhdist.y, LINELAYER::DOWN);
	ray.m_arrRay[(UINT)RAY_TYPE::DOWN_RIGHT]	 = CreateRay(Vector2(0.0f, 0.f), Vector2(0.f, +1.f), Vector2(+vOffset.x, 0.f), vhdist.y, LINELAYER::DOWN);

	ray.m_arrRay[(UINT)RAY_TYPE::DOWN]			 = CreateRay(Vector2(0.0f, 0.f), Vector2(0.f, +1.f), Vector2(0.f, 0.f), vhdist.y,		 LINELAYER::DOWN);



	ray.vOffset = vOffset;
	ray.vhdist = vhdist;

	LayerRegister(LINELAYER::LEFT,   LINELAYER::LEFTWALL);
	LayerRegister(LINELAYER::UP,     LINELAYER::UPWALL);
	LayerRegister(LINELAYER::RIGHT,  LINELAYER::RIGHTWALL);
	LayerRegister(LINELAYER::DOWN,   LINELAYER::DOWNWALL);


}



void CLineColManager::CollisionBtwLayer(LINELAYER _left, LINELAYER _right)
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

			bool bDead = vecLeft[i]->IsDead() || vecRight[j]->IsDead();
			//bool bDead = false;

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
	for (size_t i = 0; i < (UINT)LINELAYER::END; i++)
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
	for (size_t i = 0; i < (UINT)LINELAYER::END; i++)
	{
		count += m_veclineCol[i].size();
	}

	fwrite(&count, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < (UINT)LINELAYER::END; i++)
	{
		if ((LINELAYER)i == LINELAYER::MOUSE)
			continue;

		for (size_t j = 0; j < m_veclineCol[i].size(); j++)
		{
			CLineCollider lineCol = *m_veclineCol[i][j];
			fwrite(&lineCol.m_vP1   ,sizeof(Vector2) ,1 , _pFile);
			fwrite(&lineCol.m_vP2   ,sizeof(Vector2) ,1 , _pFile);
			fwrite(&lineCol.m_dir   ,sizeof(WALLDIR) ,1 , _pFile);
			fwrite(&lineCol.m_layer ,sizeof(LINELAYER)   ,1 , _pFile);
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
		Vector2		vP1;
		Vector2		vP2;
		WALLDIR		dir;
		LINELAYER	layer;
		fread(&vP1,		sizeof(Vector2), 1, _pFile);
		fread(&vP2,		sizeof(Vector2), 1, _pFile);
		fread(&dir,		sizeof(WALLDIR)  , 1, _pFile);
		fread(&layer,   sizeof(LINELAYER), 1, _pFile);
		GETINSTANCE(CLineColManager)->CreateLine(vP1, vP2, layer)->m_dir = dir;
	}
}