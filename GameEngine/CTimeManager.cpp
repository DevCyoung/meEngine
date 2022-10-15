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
	//정밀도가 훨씬높다. 1초 = 천만
	//초당 카운팅 증가량
	//요즘은 보통 천만나옴 근데 컴퓨터마다 다를수도있어
	QueryPerformanceFrequency(&m_llFrequency); //1초기준 천만
	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceCounter(&m_llPrevCount);
}

void CTimeManager::tick()
{
	QueryPerformanceCounter(&m_llCurCount);

	//tick 간격시간
	m_fDeltaTime = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;

	//누적시간
	m_fTime += m_fDeltaTime;

	//함수 호출 횟수
	++m_iCallCount;
	//이전 카운트 값을 현재 카운트로 갱신
	m_llPrevCount = m_llCurCount;
}

void CTimeManager::render()
{
	//1초에 한번
	if (1.f <= m_fTime)
	{
		float FPS = 1.f / m_fDeltaTime;

		wchar_t szBuff[256] = {};
		swprintf_s(szBuff, L"FPS: %d DELTATIME : %f", m_iCallCount, m_fDeltaTime);
		//커널오브젝트에 접근하는것은 매우느리다. 프로그램이 엄청느려진다.
		SetWindowText(GETINSTANCE(CEngine)->GetMainWnd(), szBuff);
		m_fTime = 0.f;
		m_iCallCount = 0;
	}
}
