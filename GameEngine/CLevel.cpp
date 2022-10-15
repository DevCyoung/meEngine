#include "pch.h"
#include "CLevel.h"
#include "CGameObject.h"
#include "CTile.h"


CLevel::CLevel()
{

}

CLevel::~CLevel()
{
	// ������Ʈ ����
	/*for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		for (size_t j = 0; j < m_arrLayer[i].size(); j++)
		{
			delete m_arrLayer[i][j];
		}
	}*/
	DeleteAllObject();
}

void CLevel::tick()
{
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		for (size_t j = 0; j < m_arrLayer[i].size(); j++)
		{
			m_arrLayer[i][j]->tick();
		}
	}
}

void CLevel::final_tick()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			m_arrLayer[i][j]->final_tick();
		}
	}
}

void CLevel::render(HDC _dc)
{
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		vector<CGameObject*>::iterator iter = m_arrLayer[i].begin();

		for (; iter != m_arrLayer[i].end(); )
		{
			if ((*iter)->IsDead())
			{
				iter = m_arrLayer[i].erase(iter);
			}
			else
			{
				(*iter)->render(_dc);
				++iter;
			}
		}
	}
}


void CLevel::DeleteAllObject()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			//�̺�Ʈ�Ŵ����� �ϵ��� ��Ŵ
			if (nullptr == m_arrLayer[i][j])
				continue;
			if (m_arrLayer[i][j]->IsDead())
				continue;
			delete m_arrLayer[i][j];
			m_arrLayer[i][j] = nullptr;
		}
		// �����Ҵ� ������Ų �ּҰ����� ���ͳ����� �������
		m_arrLayer[i].clear();
	}
}

void CLevel::DeleteAllObject(LAYER _eLayer)
{
	for (size_t i = 0; i < m_arrLayer[(UINT)_eLayer].size(); i++)
	{
		delete m_arrLayer[(UINT)_eLayer][i];
	}
	m_arrLayer[(UINT)_eLayer].clear();
}

//Ÿ�ϻ��θ���
void CLevel::CreateTile(UINT _X, UINT _Y)
{
	//���� Ÿ�� ����
	DeleteAllObject(LAYER::TILE);

	m_iTileXCount = _X;
	m_iTileYCount = _Y;

	for (UINT y = 0; y < m_iTileYCount; y++)
	{
		for (UINT x = 0; x < m_iTileXCount; x++)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vector2((float)TILE_SIZE * x, (float)TILE_SIZE * y));
			AddObject(pTile, LAYER::TILE);
		}
	}
}
