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
	//DC����
	//m_hDCl ���̵� ��ĥ������ �����������̱⶧����!
	ReleaseDC(m_hMainWnd, m_hMainDC); //GetDC

	//�׳� �����찡 ��Ű�´���ϴ°���
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

	//���� DC�ʱ�ȭ
	//Ŀ�ο�����Ʈ
	m_hMainDC = GetDC(m_hMainWnd);
	
	//m_hDC�� ȣȯ������ BITMAP
	m_hBufferBit = CreateCompatibleBitmap(m_hMainDC, m_ptWndScreenSize.x, m_ptWndScreenSize.y);
	//m_hDC�� ȣȯ������ DC
	m_hBufferDC = CreateCompatibleDC(m_hMainDC);

	//dc �� ����������� �⺻������ 1�ȼ� ¥�� ��Ʈ���� �����ִ�.
	HBITMAP hPrebit = (HBITMAP)SelectObject(m_hBufferDC, m_hBufferBit);
	DeleteObject(hPrebit);

	//Pen �ʱ�ȭ
	CreatePenBrush();


	//���� Manager �ʱ�ȭ
	GETINSTANCE(CPathManager)->init();
	GETINSTANCE(CTimeManager)->init();
	GETINSTANCE(CKeyManager)->init();
	GETINSTANCE(CLevelManager)->init();


	//GETINSTANCE(CCamera)->SetLook(Vector2(m_ptWndScreenSize.x / 2.f, m_ptWndScreenSize.y / 2.f));
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
	Rectangle(m_hBufferDC, -1, -1, m_ptWndScreenSize.x + 1, m_ptWndScreenSize.y + 1);	

	GETINSTANCE(CLevelManager)->render(m_hBufferDC);

	//Rectangle(m_hBufferDC, (int)test.x, (int)test.y, (int)test.x  + 100, (int)test.y  + 100);
	
	// MemBitmap -> MainWindowBitmap
	// ������۸�
	BitBlt(m_hMainDC, 0, 0, m_ptWndScreenSize.x, m_ptWndScreenSize.y, m_hBufferDC, 0, 0, SRCCOPY);


	//
	GETINSTANCE(CTimeManager)->render();
}

void CEngine::CreatePenBrush()
{
	//��ĭ�� �������� 4����Ʈ
	m_arrpen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrpen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrpen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
