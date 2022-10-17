#include "pch.h"
#include "CUIManager.h"

#include "CLevel.h"
#include "CLevelManager.h"
#include "CKeyManager.h"
#include "CUI.h"

CUIManager::CUIManager()
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

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		//
		//CUI* GetPriorityUI(pParentUI);

		// UI 위에 마우스가 있다.
		if (pUI->IsMouseOn())
		{
			// 마우스온 이벤트 호출
			pUI->MouseOn();

			// 이번에 LBTN 이 눌렸다
			if (bLbtnPressed)
			{
				// LbtnDown 이벤트 호출
				pUI->MouseLbtnDown();
			}

			// 이번에 LBTN 이 떼졌다
			else if (bLbtnReleased)
			{
				// 이전에 눌린적이 있다.
				if (pUI->m_bLbtnDown)
				{
					// 클릭 이벤트 호출
					pUI->MouseLbtnClicked();
				}
			}
		}

		if (bLbtnReleased)
		{
			pUI->m_bLbtnDown = false;
		}
	}
}
