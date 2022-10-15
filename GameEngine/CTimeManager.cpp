#include "pch.h"
#include "CTimeManager.h"
#include "CEngine.h"

CTimeManager::CTimeManager()
	: m_llPrevCount{}
	, m_llCurCount{}
	, m_llFrequency{}
	, m_fTime(0.f)
	, m_fDeltaTime(0.f)
	, m_iCallCount(0)
{

}

CTimeManager::~CTimeManager()
{
}

void CTimeManager::init()
{
	//���е��� �ξ�����. 1�� = õ��
	//�ʴ� ī���� ������
	//������ ���� õ������ �ٵ� ��ǻ�͸��� �ٸ������־�
	QueryPerformanceFrequency(&m_llFrequency); //1�ʱ��� õ��
	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceCounter(&m_llPrevCount);
}

void CTimeManager::tick()
{
	QueryPerformanceCounter(&m_llCurCount);

	//tick ���ݽð�
	m_fDeltaTime = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;

	//�����ð�
	m_fTime += m_fDeltaTime;

	//�Լ� ȣ�� Ƚ��
	++m_iCallCount;
	//���� ī��Ʈ ���� ���� ī��Ʈ�� ����
	m_llPrevCount = m_llCurCount;
}

void CTimeManager::render()
{
	//1�ʿ� �ѹ�
	if (1.f <= m_fTime)
	{
		float FPS = 1.f / m_fDeltaTime;

		wchar_t szBuff[256] = {};
		swprintf_s(szBuff, L"FPS: %d DELTATIME : %f", m_iCallCount, m_fDeltaTime);
		//Ŀ�ο�����Ʈ�� �����ϴ°��� �ſ������. ���α׷��� ��û��������.
		SetWindowText(GETINSTANCE(CEngine)->GetMainWnd(), szBuff);
		m_fTime = 0.f;
		m_iCallCount = 0;
	}
}
