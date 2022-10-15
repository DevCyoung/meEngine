#pragma once

typedef void(CGameObject::* DELEGATE)(void);
class CGameObject;

class CEventManager
{
	SINGLETON(CEventManager);

private:
	vector<tEvent>				m_vecEvent;
	vector<tAnimEvent>			m_vecAnimEvent;



private:
	vector<CGameObject*>		m_vecGarbage;
public:
	void AddEvent(const tAnimEvent& _evnet) { m_vecAnimEvent.push_back(_evnet); }

public:
	void AddEvent(const tEvent& _evnet) { m_vecEvent.push_back(_evnet); }

public:
	void tick();

};

