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

	// ���� ���� ����
	// UI Layer ��������
	CLevel* pCurLevel = GETINSTANCE(CLevelManager)->GetCurLevel();
	const vector<CGameObject*>& vecUI = pCurLevel->GetLayer(LAYER::UI);

	//�ڿ��� ���� �˻��ϴ������� �ǳ�ui�߿��� �Ǿտ� �׷����ֺ��� �Ϸ���
	for (int i = (int)vecUI.size() - 1; 0 <= i; --i)
	{
		m_pPriorityUI = GetPriorityUI((CUI*)vecUI[i]);

		if (nullptr == m_pPriorityUI)
			continue;

		// ���콺�� �̺�Ʈ ȣ��
		m_pPriorityUI->MouseOn();

		// �̹��� LBTN �� ���ȴ�
		if (bLbtnPressed)
		{
			// LbtnDown �̺�Ʈ ȣ��
			m_pPriorityUI->MouseLbtnDown();

			// �θ�UI �� FocusedUI �� ����
			m_pFocusedUI = (CUI*)vecUI[i];
			pCurLevel->SetFocusUI(m_pFocusedUI);
			break;
		}

		// �̹��� LBTN �� ������
		else if (bLbtnReleased)
		{
			// ������ �������� �ִ�.
			if (m_pPriorityUI->m_bLbtnDown)
			{
				// Ŭ�� �̺�Ʈ ȣ��
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

		// UI �� ���� Ȯ��
		if (pUI->IsMouseOn())
		{
			// �켱���� UI �� ����������, �� ���� �켱������ ���� �ٸ� UI �� ���� ���.
			// ���� UI �� LBTNDown ���¸� �����Ѵ�.
			if (bLbtnReleased && nullptr != pPriorityUI && pPriorityUI->IsLbtnDown())
			{
				pUI->m_bLbtnDown = false;
			}

			// �켱���� UI �� ����
			pPriorityUI = pUI;
		}

		// �켱���� UI �� ���� �ȵ� UI �� ���콺 ���������� �߻��ϸ� LBtnDown �� �����س��´�.
		else if (bLbtnReleased)
		{
			pUI->m_bLbtnDown = false;
		}
	}
	return pPriorityUI;
}