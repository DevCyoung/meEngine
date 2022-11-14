
#include "CRockmanMonster.h"
class CCongBullet :
    public CRockmanMonster
{
public:
	Vector2	m_dir;	
	float m_speed;
	bool m_isHit;
	float m_lifeTime;
	virtual void tick() override;
	virtual void render(HDC _dc) override;
	
	virtual void OnTriggerEnter(CCollider* _pOther);

	CLONE(CCongBullet);

public:
	CCongBullet();
	CCongBullet(const CCongBullet& _other);
	~CCongBullet();
};
