#pragma once
#include "CEventBox.h"


class CDoor1 :
    public CEventBox
{
public:
	virtual void tick() override;
	virtual void render(HDC _dc) override;

public:
	virtual void OnTriggerEnter(CCollider* _pOther);

public:
	CDoor1();
	~CDoor1();

	// CEventBox��(��) ���� ��ӵ�
	virtual void Save(FILE* pFile) override;
	virtual void Load(FILE* pFile) override;
};

