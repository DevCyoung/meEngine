#pragma once
#include "CEventBox.h"

#include "CDoor1.h"

class CDoor2 :
    public CDoor1
{

public:
	virtual void tick() override;
	virtual void render(HDC _dc) override;

public:
	virtual void OnTriggerEnter(CCollider* _pOther);

public:
	CDoor2();
	~CDoor2();
};

