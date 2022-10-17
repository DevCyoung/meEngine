#pragma once

class CAnimEnvManager
{
	SINGLETON(CAnimEnvManager);


private:
	vector<tAnimEvent>			m_vecEvent;	

public:
	void AddEvent(const tAnimEvent& _evnet)
	{
		m_vecEvent.push_back(_evnet);
	}

public:
	void tick();

};

