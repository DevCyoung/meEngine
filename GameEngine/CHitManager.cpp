#include "pch.h"
#include "CHitManager.h"
#include "CTimeManager.h"

CHitManager::CHitManager()
	:m_hitTimedselay(0.f)
{

}

CHitManager::~CHitManager()
{

}

void CHitManager::tick()
{

	if (m_vecDuration.size() > 0)
	{
		m_hitTimedselay += GETINSTANCE(CTimeManager)->GEtRealDetaTime();

		GETINSTANCE(CTimeManager)->SetDelayTime(0.32f);

		if (0.42f <= m_hitTimedselay )
		{
			GETINSTANCE(CTimeManager)->SetDelayTime(1.f);
			m_hitTimedselay = 0.f;			
			m_vecDuration.clear();
		}
	}
	else
	{
		GETINSTANCE(CTimeManager)->SetDelayTime(1.f);
	}
}
