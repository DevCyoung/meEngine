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

	// ���� ���� ����
	// UI Layer ��������
	CLevel* pCurLevel = GETINSTANCE(CLevelManager)->GetCurLevel();
	const vector<CGameObject*>& vecUI = pCurLevel->GetLayer(LAYER::UI);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		//
		//CUI* GetPriorityUI(pParentUI);

		// UI ���� ���콺�� �ִ�.
		if (pUI->IsMouseOn())
		{
			// ���콺�� �̺�Ʈ ȣ��
			pUI->MouseOn();

			// �̹��� LBTN �� ���ȴ�
			if (bLbtnPressed)
			{
				// LbtnDown �̺�Ʈ ȣ��
				pUI->MouseLbtnDown();
			}

			// �̹��� LBTN �� ������
			else if (bLbtnReleased)
			{
				// ������ �������� �ִ�.
				if (pUI->m_bLbtnDown)
				{
					// Ŭ�� �̺�Ʈ ȣ��
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
