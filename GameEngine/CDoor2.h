#pragma once
#include "CEventBox.h"

#include "CDoor1.h"
class CCyberKujacer;

class CDoor2 :
    public CDoor1
{

public:
	float			m_warningDelay;
	CCyberKujacer* m_boss;
	virtual void tick() override;
	virtual void render(HDC _dc) override;

public:
	virtual void OnTriggerEnter(CCollider* _pOther);

public:
	CDoor2();
	~CDoor2();
};

