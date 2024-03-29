#include "pch.h"
#include "CEditorLevel.h"
#include "CResourceManager.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CTexture.h"

#include "CTile.h"
#include "resource.h"
#include "CLevelManager.h"
#include "CKeyManager.h"
#include "CPathManager.h"
#include "CUI.h"
#include "CButton.h"
#include "CPanelUI.h"
#include "CCollisionManager.h"
void CEditorLevel::init()
{
	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::WALL, LAYER::PLAYER);
}

//
//void CEditorLevel::CreateUI()
//{
//	//카메라시점
//	Vector2 vResolution = GETINSTANCE(CEngine)->GetWndScreenSize();
//	GETINSTANCE(CCamera)->SetLook(vResolution / 2.f);
//
//
//	// Button 이 사용할 텍스쳐
//	CTexture* pButtonTex = GETINSTANCE(CResourceManager)->LoadTexture(L"Button", L"texture\\button.bmp");
//	CTexture* pButtonPressedTex = GETINSTANCE(CResourceManager)->LoadTexture(L"Button_Pressed", L"texture\\button_pressed.bmp");
//	CTexture* pPanelTex = GETINSTANCE(CResourceManager)->LoadTexture(L"Panel", L"texture\\OakUI.bmp");
//
//	//UI배치
//	CPanelUI* pPanelUI = new CPanelUI();
//	pPanelUI->SetIdleTex(pPanelTex);
//	pPanelUI->SetPos(Vector2(vResolution.x - pPanelTex->Width() + 20.f, 10.f));	
//	
//
//	CButton* pSaveButton = new CButton();
//	pSaveButton->SetScale(Vector2(100.f, 50.f));
//	pSaveButton->SetPos(Vector2(10.f ,20.f));
//	pSaveButton->SetDelegate(this, (DELEGATE)&CEditorLevel::SaveTIle);
//	pSaveButton->SetIdleTex(pButtonTex);
//	pSaveButton->SetPressedTex(pButtonPressedTex);
//
//	//AddObject(pSaveButton, LAYER::UI);
//
//
//	CButton* pLoadButton = pSaveButton->Clone();	
//	pLoadButton->SetPos(Vector2(150.f, 20.f));
//	pLoadButton->SetDelegate(this, (DELEGATE)&CEditorLevel::LoadTIle);
//
//	//AddObject(pLoadButton, LAYER::UI);
//	pPanelUI->AddChildUI(pSaveButton);
//	pPanelUI->AddChildUI(pLoadButton);
//
//	AddObject(pPanelUI, LAYER::UI);
//
//	//for (size_t i = 0; i < 100; i++)
//	//{
//	//	pPanelUI = pPanelUI->Clone();
//	//	pPanelUI->SetPos(Vector2(vResolution.x - pPanelTex->Width() + 20.f - pPanelTex->Width(), 10.f));
//	//	AddObject(pPanelUI, LAYER::UI);
//	//}
//}
