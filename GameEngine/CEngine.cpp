#include "pch.h"
#include "CEngine.h"


#include "CPathManager.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CLevelManager.h"
#include "CCollisionManager.h"
#include "CEventManager.h"
#include "CCamera.h"
#include "CAnimEnvManager.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_hMainDC(nullptr)
	, m_hBufferDC(nullptr)
	, m_hBufferBit(nullptr)
	, m_ptWndScreenSize{}
	, m_arrpen{}
{
}

CEngine::~CEngine()
{
	//DC해제
	//m_hDCl 아이디가 겹칠수있음 윈도우전용이기때문에!
	ReleaseDC(m_hMainWnd, m_hMainDC); //GetDC

	//그냥 윈도우가 시키는대로하는거임
	DeleteDC(m_hBufferDC);				//CreateDC
	DeleteObject(m_hBufferBit);

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

	//Window
	RECT rect = { 0,0, (LONG)m_ptWndScreenSize.x, (LONG)m_ptWndScreenSize.y };
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, m_ptWndScreenSize.x, m_ptWndScreenSize.y, 0);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false); // -> inout
	SetWindowPos(m_hMainWnd, nullptr, 1920 / 2 - _iWidth / 2, 1080 / 2 - _iHeight / 2 - 100, rect.right - rect.left, rect.bottom - rect.top, 0);

	//메인 DC초기화
	//커널오브젝트
	m_hMainDC = GetDC(m_hMainWnd);
	
	//m_hDC와 호환가능한 BITMAP
	m_hBufferBit = CreateCompatibleBitmap(m_hMainDC, m_ptWndScreenSize.x, m_ptWndScreenSize.y);
	//m_hDC와 호환가능한 DC
	m_hBufferDC = CreateCompatibleDC(m_hMainDC);

	//dc 도 만들어졌을때 기본적으로 1픽셀 짜리 비트맵을 물고있다.
	HBITMAP hPrebit = (HBITMAP)SelectObject(m_hBufferDC, m_hBufferBit);
	DeleteObject(hPrebit);

	//Pen 초기화
	CreatePenBrush();


	//각종 Manager 초기화
	GETINSTANCE(CPathManager)->init();
	GETINSTANCE(CTimeManager)->init();
	GETINSTANCE(CKeyManager)->init();
	GETINSTANCE(CLevelManager)->init();


	//GETINSTANCE(CCamera)->SetLook(Vector2(m_ptWndScreenSize.x / 2.f, m_ptWndScreenSize.y / 2.f));
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
	Rectangle(m_hBufferDC, -1, -1, m_ptWndScreenSize.x + 1, m_ptWndScreenSize.y + 1);	

	GETINSTANCE(CLevelManager)->render(m_hBufferDC);

	//Rectangle(m_hBufferDC, (int)test.x, (int)test.y, (int)test.x  + 100, (int)test.y  + 100);
	
	// MemBitmap -> MainWindowBitmap
	// 더블버퍼링
	BitBlt(m_hMainDC, 0, 0, m_ptWndScreenSize.x, m_ptWndScreenSize.y, m_hBufferDC, 0, 0, SRCCOPY);


	//
	GETINSTANCE(CTimeManager)->render();
}

void CEngine::CreatePenBrush()
{
	//한칸의 색상정보 4바이트
	m_arrpen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrpen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrpen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
