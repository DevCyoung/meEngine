#pragma once
class CUI;

class CUIManager
{
	SINGLETON(CUIManager);

private:
	CUI* m_pFocusedUI;
	CUI* m_pPriorityUI;


public:
	void tick();

	
private:
	// �ֻ��� �θ�UI ����, �ڽ� UI ���� �����ؼ� ���� �켱������ ���� UI �� ã�Ƴ���.
	CUI* GetPriorityUI(CUI* _pParentUI);
};
