#include "pch.h"
#include "CEngine.h"


#include "CPathManager.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CLevelManager.h"
#include "CCollisionManager.h"
#include "CResourceManager.h"
#include "CEventManager.h"
#include "CCamera.h"
#include "CAnimEnvManager.h"
#include "CTexture.h"
#include "CUIManager.h"
#include "CLineColManager.h"

//그냥 윈도우가 시키는대로하는거임
//DeleteDC(m_pTexBuffer->GetDC());
//DeleteObject(m_pTexBuffer->Get);

#include "CSoundMgr.h"
CTexture* m_pTexuturedd;

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_hMainDC(nullptr)	
	, m_ptWndScreenSize{}
	, m_arrpen{}
{

}

CEngine::~CEngine()
{
	//DC해제
	//m_hDCl 아이디가 겹칠수있음 윈도우전용이기때문에!
	ReleaseDC(m_hMainWnd, m_hMainDC);

	for (size_t i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrpen[i]);
	}
}

void CEngine::Init(HWND _hwnd, UINT _iWidth, UINT _iHeight)
{
	m_hMainWnd = _hwnd;
	m_ptWndScreenSize.x = _iWidth;
	m_ptWndScreenSize.y = _iHeight;

	//메인 DC초기화
	m_hMainDC = GetDC(m_hMainWnd);	
	WindowReSize(_iWidth, _iHeight);
	m_pRealBuffer = GETINSTANCE(CResourceManager)->CreateTexture(L"RealBackBuffer", WINDOW_ORIGINAL_X, WINDOW_ORIGINAL_Y);


	//Pen 초기화
	CreatePenBrush();

	//각종 Manager 초기화
	GETINSTANCE(CPathManager)->init();
	GETINSTANCE(CTimeManager)->init();
	GETINSTANCE(CKeyManager)->init();
	GETINSTANCE(CSoundMgr)->init();
	GETINSTANCE(CLevelManager)->init();


	GETINSTANCE(CCamera)->SetLook(Vector2(m_ptWndScreenSize.x / 2.f, m_ptWndScreenSize.y / 2.f));
	m_pTexuturedd = GETINSTANCE(CResourceManager)->LoadTexture(L"Playerd", L"texture\\c.bmp");
}

void CEngine::progress()
{
	//논리적인연산
	this->tick();

	//화면 렌더링연산
	this->render();

	//다음프레임에 적용되야 할것들	
 	GETINSTANCE(CEventManager)->tick();
}	

void CEngine::tick()
{
	GETINSTANCE(CTimeManager)->tick();
	GETINSTANCE(CKeyManager)->tick();
	GETINSTANCE(CCamera)->tick();

	GETINSTANCE(CLevelManager)->tick();	

	GETINSTANCE(CCollisionManager)->tick();
	GETINSTANCE(CLineColManager)->tick();

	//GETINSTANCE(CLevelManager)->fixed_tick();

	GETINSTANCE(CUIManager)->tick();
}

Vector2 test = {};


void CEngine::render()
{
	//화면 클리어
	//전체영역을 흰색으로 다시그림
	//테두리 안지우면 1픽셀 펜이 그려지게된다.
	//모니터갱신률
	//윈도우에선 픽셀 덩어리를 비트맵이라고한다.
	//우리가 지금까지 그림을 그리는건 윈도우가 소유하고있는 비트맵에 그림을 그린거고 우리가 그것을 보고있던것이다.

	Rectangle(m_pTexBuffer->GetDC(), -1, -1, m_pTexBuffer->Width() + 1, m_pTexBuffer->Height() + 1);
	GETINSTANCE(CLevelManager)->render(m_pTexBuffer->GetDC());
	BitBlt(m_hMainDC, 0, 0, m_ptWndScreenSize.x, m_ptWndScreenSize.y, m_pTexBuffer->GetDC(), 0, 0, SRCCOPY);

	//if (LEVEL_MODE == LEVEL_EDITOR)
	//{
	//	Rectangle(m_pTexBuffer->GetDC(), -1, -1, m_pTexBuffer->Width() + 1, m_pTexBuffer->Height() + 1);
	//	GETINSTANCE(CLevelManager)->render(m_pTexBuffer->GetDC());

	//	////내가짬
	//	////GETINSTANCE(CLineColManager)->render(m_pTexBuffer->GetDC());

	//	//// 더블버퍼링

	//	BitBlt(m_hMainDC, 0, 0, m_ptWndScreenSize.x, m_ptWndScreenSize.y, m_pTexBuffer->GetDC(), 0, 0, SRCCOPY);

	//}
	//else
	//{
	//	Rectangle(m_pRealBuffer->GetDC(), -1, -1, m_pRealBuffer->Width() + 1, m_pRealBuffer->Height() + 1);

	//	GETINSTANCE(CLevelManager)->render(m_pRealBuffer->GetDC());

	//	//내가짬
	//	//GETINSTANCE(CLineColManager)->render(m_pRealBuffer->GetDC());

	//	StretchBlt
	//	(
	//		m_hMainDC, 0, 0, m_ptWndScreenSize.x, m_ptWndScreenSize.y, m_pRealBuffer->GetDC(), 0, 0, m_pRealBuffer->Width(), m_pRealBuffer->Height(), SRCCOPY
	//	);
	//}

	GETINSTANCE(CTimeManager)->render();

}

void CEngine::CreatePenBrush()
{
	//한칸의 색상정보 4바이트
	m_arrpen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrpen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrpen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrpen[(UINT)PEN_TYPE::BLACK] = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	m_arrpen[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	m_arrpen[(UINT)PEN_TYPE::ORANGE] = CreatePen(PS_SOLID, 1, RGB(255, 127, 0));
}

void CEngine::WindowReSize(UINT _iWidth, UINT _iHeight)
{
	m_ptWndScreenSize.x = _iWidth;
	m_ptWndScreenSize.y = _iHeight;	

	RECT rt = { 0, 0, m_ptWndScreenSize.x, m_ptWndScreenSize.y };

	HMENU hMenu = GetMenu(m_hMainWnd);	

	if (nullptr != hMenu)
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	else
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	UINT sw = GetSystemMetrics(SM_CXSCREEN);
	UINT sh = GetSystemMetrics(SM_CYSCREEN);
	UINT ww = rt.right - rt.left;
	UINT wh = rt.bottom - rt.top;
	SetWindowPos(m_hMainWnd, nullptr, sw / 2 - ww / 2, sh / 2 - wh / 2, ww, wh, 0);


	// 백버퍼가 없으면 생성
	if (nullptr == m_pTexBuffer)
	{
		// 백버퍼 용 비트맵 제작
		m_pTexBuffer = GETINSTANCE(CResourceManager)->CreateTexture(L"BackBuffer", m_ptWndScreenSize.x, m_ptWndScreenSize.y);
		
	}

	// 백버퍼가 있으면, 변경된 해상도에 맞추어 크기 재조정
	else
	{
		m_pTexBuffer->Resize(m_ptWndScreenSize.x, m_ptWndScreenSize.y);
	}


}