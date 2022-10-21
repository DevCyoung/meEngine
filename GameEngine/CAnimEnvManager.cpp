#include "pch.h"
#include "CAnimEnvManager.h"

CAnimEnvManager::CAnimEnvManager()
{

}

CAnimEnvManager::~CAnimEnvManager()
{
	
}

void CAnimEnvManager::tick()
{
	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		tAnimEvent env = m_vecEvent[i];		

		if (env.instance && env.func)
		{
			(env.instance->*env.func)();
		}
	}
	m_vecEvent.clear();
}
