#pragma once
#include "CRockmanMonster.h"
class CCyberCongBullet :
    public CRockmanMonster
{
public:
	float		m_lifeTIme;
	float		m_deadTime;
	Vector2		m_targetdir;
	bool		m_isBall;


	virtual void tick() override;
	
	


	//box 
	virtual void OnTriggerEnter(CCollider* _pOhter);
	


public:
	CCyberCongBullet();
	CCyberCongBullet(const CCyberCongBullet& _other);
	~CCyberCongBullet();
};


