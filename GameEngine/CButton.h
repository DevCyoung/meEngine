#pragma once
#include "CUI.h"
class CGameobject;
class CTexture;

//�Լ������� �ݹ�
typedef  void(*PPPPPPPP)(void);

//�Լ��� ��ü���� ��������Ʈ
//typedef void(CEditorLevel::*DELEGATE)(void);



class CButton :
    public CUI
{

//Very important
//�̹������� �ٽ�

private:  
    //PPPPPPPP m_PPPPP;
    CTexture*       m_pPressedTex;
    CTexture*       m_pHighlightTex;


    CEntity*        m_pInst;
    DELEGATE        m_pDelegateFunc;

public:

public:

    void SetHighlightTex(CTexture* _pTex) { m_pHighlightTex = _pTex; }
    void SetPressedTex(CTexture* _pTex) { m_pPressedTex = _pTex; }
    void SetDelegate(CEntity* _pInst, DELEGATE _Func)
    {
        m_pInst = _pInst;
        m_pDelegateFunc = _Func;
    }

    virtual void render(HDC _dc) override;

public:
    virtual void MouseLbtnClicked() override;

public:
    CLONE(CButton);

public:
    CButton();
    ~CButton();
};

