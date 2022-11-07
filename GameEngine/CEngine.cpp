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

//�׳� �����찡 ��Ű�´���ϴ°���
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
	//DC����
	//m_hDCl ���̵� ��ĥ������ �����������̱⶧����!
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

	//���� DC�ʱ�ȭ
	m_hMainDC = GetDC(m_hMainWnd);	
	WindowReSize(_iWidth, _iHeight);
	m_pRealBuffer = GETINSTANCE(CResourceManager)->CreateTexture(L"RealBackBuffer", WINDOW_ORIGINAL_X, WINDOW_ORIGINAL_Y);


	//Pen �ʱ�ȭ
	CreatePenBrush();

	//���� Manager �ʱ�ȭ
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
	//�����ο���
	this->tick();

	//ȭ�� ����������
	this->render();

	//���������ӿ� ����Ǿ� �Ұ͵�	
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
	//ȭ�� Ŭ����
	//��ü������ ������� �ٽñ׸�
	//�׵θ� ������� 1�ȼ� ���� �׷����Եȴ�.
	//����Ͱ��ŷ�
	//�����쿡�� �ȼ� ����� ��Ʈ���̶���Ѵ�.
	//�츮�� ���ݱ��� �׸��� �׸��°� �����찡 �����ϰ��ִ� ��Ʈ�ʿ� �׸��� �׸��Ű� �츮�� �װ��� �����ִ����̴�.

	Rectangle(m_pTexBuffer->GetDC(), -1, -1, m_pTexBuffer->Width() + 1, m_pTexBuffer->Height() + 1);
	GETINSTANCE(CLevelManager)->render(m_pTexBuffer->GetDC());
	BitBlt(m_hMainDC, 0, 0, m_ptWndScreenSize.x, m_ptWndScreenSize.y, m_pTexBuffer->GetDC(), 0, 0, SRCCOPY);

	//if (LEVEL_MODE == LEVEL_EDITOR)
	//{
	//	Rectangle(m_pTexBuffer->GetDC(), -1, -1, m_pTexBuffer->Width() + 1, m_pTexBuffer->Height() + 1);
	//	GETINSTANCE(CLevelManager)->render(m_pTexBuffer->GetDC());

	//	////����«
	//	////GETINSTANCE(CLineColManager)->render(m_pTexBuffer->GetDC());

	//	//// ������۸�

	//	BitBlt(m_hMainDC, 0, 0, m_ptWndScreenSize.x, m_ptWndScreenSize.y, m_pTexBuffer->GetDC(), 0, 0, SRCCOPY);

	//}
	//else
	//{
	//	Rectangle(m_pRealBuffer->GetDC(), -1, -1, m_pRealBuffer->Width() + 1, m_pRealBuffer->Height() + 1);

	//	GETINSTANCE(CLevelManager)->render(m_pRealBuffer->GetDC());

	//	//����«
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
	//��ĭ�� �������� 4����Ʈ
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


	// ����۰� ������ ����
	if (nullptr == m_pTexBuffer)
	{
		// ����� �� ��Ʈ�� ����
		m_pTexBuffer = GETINSTANCE(CResourceManager)->CreateTexture(L"BackBuffer", m_ptWndScreenSize.x, m_ptWndScreenSize.y);
		
	}

	// ����۰� ������, ����� �ػ󵵿� ���߾� ũ�� ������
	else
	{
		m_pTexBuffer->Resize(m_ptWndScreenSize.x, m_ptWndScreenSize.y);
	}


}