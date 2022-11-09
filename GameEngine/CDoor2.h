#pragma once
#include "CEventBox.h"

class CDoor2 :
    public CEventBox
{

public:
	virtual void tick() override;
	virtual void render(HDC _dc) override;

public:
	virtual void OnTriggerEnter(CCollider* _pOther);

public:
	CDoor2();
	~CDoor2();

	// CEventBox��(��) ���� ��ӵ�
	virtual void Save(FILE* pFile) override;
	virtual void Load(FILE* pFile) override;
};

