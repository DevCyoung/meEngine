#include "pch.h"
#include "CUIManager.h"

#include "CLevel.h"
#include "CLevelManager.h"
#include "CKeyManager.h"
#include "CUI.h"

CUIManager::CUIManager()
	: m_pFocusedUI(nullptr)
	, m_pPriorityUI(nullptr)
{
}

CUIManager::~CUIManager()
{
}

void CUIManager::tick()
{
	bool bLbtnPressed = IS_INPUT_TAB(KEY::LBTN);
	bool bLbtnReleased = IS_INPUT_RELEASE(KEY::LBTN);

	// 현재 레벨 접근
	// UI Layer 가져오기
	CLevel* pCurLevel = GETINSTANCE(CLevelManager)->GetCurLevel();
	const vector<CGameObject*>& vecUI = pCurLevel->GetLayer(LAYER::UI);

	//뒤에서 부터 검사하는이유는 판넬ui중엣거 맨앞에 그려진애부터 하려고
	for (int i = (int)vecUI.size() - 1; 0 <= i; --i)
	{
		m_pPriorityUI = GetPriorityUI((CUI*)vecUI[i]);

		if (nullptr == m_pPriorityUI)
			continue;

		// 마우스온 이벤트 호출
		m_pPriorityUI->MouseOn();

		// 이번에 LBTN 이 눌렸다
		if (bLbtnPressed)
		{
			// LbtnDown 이벤트 호출
			m_pPriorityUI->MouseLbtnDown();

			// 부모UI 를 FocusedUI 로 설정
			m_pFocusedUI = (CUI*)vecUI[i];
			pCurLevel->SetFocusUI(m_pFocusedUI);
			break;
		}

		// 이번에 LBTN 이 떼졌다
		else if (bLbtnReleased)
		{
			// 이전에 눌린적이 있다.
			if (m_pPriorityUI->m_bLbtnDown)
			{
				// 클릭 이벤트 호출
				m_pPriorityUI->MouseLbtnClicked();
				m_pPriorityUI->m_bLbtnDown = false;
			}
		}
	}
}

CUI* CUIManager::GetPriorityUI(CUI* _pParentUI)
{

	bool bLbtnReleased = IS_INPUT_RELEASE(KEY::LBTN);

	CUI* pPriorityUI = nullptr;

	static list<CUI*> queue;
	queue.clear();
	queue.push_back(_pParentUI);


	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}

		// UI 의 상태 확인
		if (pUI->IsMouseOn())
		{
			// 우선순위 UI 로 지정됐지만, 더 높은 우선순위를 가진 다른 UI 가 나온 경우.
			// 기존 UI 의 LBTNDown 상태를 갱신한다.
			if (bLbtnReleased && nullptr != pPriorityUI && pPriorityUI->IsLbtnDown())
			{
				pUI->m_bLbtnDown = false;
			}

			// 우선순위 UI 로 지정
			pPriorityUI = pUI;
		}

		// 우선순위 UI 로 지정 안된 UI 는 마우스 해제조건이 발생하면 LBtnDown 을 해제해놓는다.
		else if (bLbtnReleased)
		{
			pUI->m_bLbtnDown = false;
		}
	}
	return pPriorityUI;
}