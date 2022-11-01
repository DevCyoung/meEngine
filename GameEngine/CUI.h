#pragma once
#include "CGameObject.h"

class CTexture;


class CUI :
	public CGameObject
{

private:
	//������ġ
	Vector2			m_vFinalPos;

	vector<CUI*>	m_vecChildUI;
	CUI*			m_pParentUI;
	CTexture*		m_pIdleTex;


	bool	m_bLbtnDown;
	bool	m_bMouseOn;
	
	bool	m_bCmrAfctd;


	
public:
	virtual void tick() override;
	virtual void render(HDC _dc) override;

	
	void render_childUI(HDC _dc);


public:
	void SetIdleTex(CTexture* _pTex);
	void SetCameraAffected(bool _bSet) { m_bCmrAfctd = _bSet; }
	Vector2 GetFinalPos() { return m_vFinalPos; }

	CUI* GetParentUI() { return m_pParentUI; }
	const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

	CTexture* GetIdleTex() { return m_pIdleTex; }

	void AddChildUI(CUI* _pChildUI)
	{
		_pChildUI->m_pParentUI = this;
		m_vecChildUI.push_back(_pChildUI);
	}

	bool IsMouseOn() { return m_bMouseOn; }
	bool IsLbtnDown() { return m_bLbtnDown; }
public:
	virtual void MouseLbtnDown() { m_bLbtnDown = true; } //�������̵��Ҷ� �ݵ�úθ𿡼� ȣ��
	virtual void MouseLbtnClicked() {};
	virtual void MouseOn() {};									//�ڽ��̻���ϵ���



private:
	void MouseOnCheck();


	CLONE(CUI);

public:
	CUI();
	CUI(const CUI& _other);
	~CUI();

	friend class CUIManager;
};

