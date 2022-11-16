#include "pch.h"
#include "CDoor2.h"


#include "CCollider.h"
#include "CCamera.h"
#include "CCollisionManager.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CWall.h"
#include "CCameraWall.h"

#include "CZero.h"


#include "CResourceManager.h"
#include "CSound.h"

#include "CTimeManager.h"

#include "CLevelManager.h"
#include "CRockmanLevel.h"

#include "CCameraObj.h"

#include "CKeyManager.h"

CDoor2::CDoor2()
{
	m_mode = COLIDE_EIDT_MODE::BOSSDOOR2BOX;
	m_sponType = MONSETER_TYPE::DOOR2;	
	m_destPos = 2712.f;
	m_zeroPos = 80.f;
}

CDoor2::~CDoor2()
{
}





void CDoor2::tick()
{
	CDoor1::tick();

	if (m_state == DOORSTATE::NONE)
	{
		CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
		CRockmanLevel* rmLevel = dynamic_cast<CRockmanLevel*>(lv);
		rmLevel->m_cam->m_isFollow = true;
		m_cameraWall = new CCameraWall();
		m_cameraWall->m_dir = COLLIDE_DIR::LEFT;
		m_cameraWall->GetCollider()->SetScale(Vector2(110.f, 4000.f));
		Vector2 pos = GetPos();
		pos.x -= 40.f;
		CGameObject::Instantiate(m_cameraWall, pos, LAYER::CAMERAWALL);
		m_state = DOORSTATE::SPONMONSTER;
	}


}

void CDoor2::render(HDC _dc)
{
	CRockmanObj::render(_dc);


	if (GETINSTANCE(CCollisionManager)->GetDrawCollide())
	{
		Vector2 pos = GETINSTANCE(CCamera)->GetRenderPos(GetPos());
		TextOut(_dc, pos.x, pos.y, L"DOOR2", 5);
	}

	

}

void CDoor2::OnTriggerEnter(CCollider* _pOther)
{
	CDoor1::OnTriggerEnter(_pOther);
}


