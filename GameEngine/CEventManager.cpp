#include "pch.h"
#include "CEventManager.h"
#include "CGameObject.h"
#include "CRockmanObj.h"
#include "CLevelManager.h"
#include "CLineCollider.h"

CEventManager::CEventManager()
{

}

CEventManager::~CEventManager()
{

}

void CEventManager::tick()
{
	//�������� ������Ʈ ����
	for (size_t i = 0; i < m_vecGarbage.size(); i++)
	{
		if (nullptr != m_vecGarbage[i])
		{
			delete m_vecGarbage[i];
			m_vecGarbage[i] = nullptr;
		}
	}
	m_vecGarbage.clear();

	//�ִϸ��̼� �̺�Ʈ ����
	for (size_t i = 0; i < m_vecAnimEvent.size(); i++)
	{
		tAnimEvent env = m_vecAnimEvent[i];

		if (env.instance && env.func)
		{
			(env.instance->*env.func)();
		}
	}

	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		switch (m_vecEvent[i].eType)
		{
			// wParam : Object Adress
			// lParam : Layer
		case EVENT_TYPE::CREATE_OBJECT:
		{
			CLevel* pCurLevel = GETINSTANCE(CLevelManager)->GetCurLevel();
			CGameObject* pNewObj = (CGameObject*)m_vecEvent[i].wParam;
			LAYER	eLayer = (LAYER)m_vecEvent[i].lParam;
			pCurLevel->AddObject(pNewObj, eLayer);
		}
		break;

		case EVENT_TYPE::DELETE_OBJECT:
		{
			//�������� ������Ʈ�� Dead ���·� �ΰ� Garbage�� �ִ´�.
			CGameObject* pObj = (CGameObject*)m_vecEvent[i].wParam;

			//����Ȯ���� ���� tick ���� ���ÿ� ������Ʈ�� ������û �� ��츦 ���
			if (false == pObj->m_bDead)
			{
				m_vecGarbage.push_back(pObj);
				pObj->m_bDead = true;
			}
		}
		break;
		case EVENT_TYPE::DELETE_LINECOL:
		{
			//�������� ������Ʈ�� Dead ���·� �ΰ� Garbage�� �ִ´�.
			CLineCollider* lineCol = (CLineCollider*)m_vecEvent[i].wParam;

			//����Ȯ���� ���� tick ���� ���ÿ� ������Ʈ�� ������û �� ��츦 ���
			/*if (false == lineCol->IsDead())
			{
				m_vecGarbage.push_back(pObj);
				pObj->m_bDead = true;
			}*/
		}
		case EVENT_TYPE::LEVEL_CHANGE:
		{
			LEVEL_TYPE eNextLevel = (LEVEL_TYPE)m_vecEvent[i].wParam;
			GETINSTANCE(CLevelManager)->LoadLevelEvent(eNextLevel);
		}
		break;
		}
	}

	

	m_vecAnimEvent.clear();
	m_vecEvent.clear();
}
