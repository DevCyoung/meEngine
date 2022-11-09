#pragma once
#include "CRockmanObj.h"



class CEventBox :
    public CRockmanObj
{

public:
	tBoxEvent			m_evt;
	COLIDE_EIDT_MODE	m_mode;

	virtual void tick() override;
	virtual void render(HDC _dc) override;	

	void ResizeCollider(Vector2 leftTop, Vector2 bottom);
	void SetCollisionEvent(CEntity* obj, DELEGATE func);


	virtual void OnTriggerEnter(CCollider* _pOther);

	virtual void Save(FILE* pFile) = 0;
	virtual void Load(FILE* pFile) = 0;
	
public:
	CEventBox();	
	~CEventBox();

};
