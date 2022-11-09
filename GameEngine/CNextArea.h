#pragma once

#include "CEventBox.h"

class CNextArea :
    public CEventBox
{
public:

public:
	virtual void tick() override;
	virtual void render(HDC _dc) override;

public:	
	virtual void OnTriggerEnter(CCollider* _pOther) override;
	
public:
	CNextArea();
	~CNextArea();

	// CEventBox��(��) ���� ��ӵ�
	virtual void Save(FILE* pFile) override;
	virtual void Load(FILE* pFile) override;
};

