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
	//삭제예정 오브젝트 삭제
	for (size_t i = 0; i < m_vecGarbage.size(); i++)
	{
		if (nullptr != m_vecGarbage[i])
		{
			delete m_vecGarbage[i];
			m_vecGarbage[i] = nullptr;
		}
	}
	m_vecGarbage.clear();

	//애니메이션 이벤트 실행
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
			//삭제예정 오브젝트를 Dead 상태로 두고 Garbage에 넣는다.
			CGameObject* pObj = (CGameObject*)m_vecEvent[i].wParam;

			//낮은확률로 같은 tick 에서 동시에 오브젝트를 삭제요청 한 경우를 방어
			if (false == pObj->m_bDead)
			{
				m_vecGarbage.push_back(pObj);
				pObj->m_bDead = true;
			}
		}
		break;
		case EVENT_TYPE::DELETE_LINECOL:
		{
			//삭제예정 오브젝트를 Dead 상태로 두고 Garbage에 넣는다.
			CLineCollider* lineCol = (CLineCollider*)m_vecEvent[i].wParam;

			//낮은확률로 같은 tick 에서 동시에 오브젝트를 삭제요청 한 경우를 방어
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
