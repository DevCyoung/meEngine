#pragma once
#include "CUI.h"
class CGameobject;
class CTexture;

//함수만전달 콜백
typedef  void(*PPPPPPPP)(void);

//함수와 객체전달 델리게이트
//typedef void(CEditorLevel::*DELEGATE)(void);



class CButton :
    public CUI
{

//Very important
//이번수업의 핵심

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

