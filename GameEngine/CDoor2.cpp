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

#include "CTextureAnim.h"

#include "CCyberKujacer.h"

#include "CZero.h"

CDoor2::CDoor2()
	:m_warningDelay(0.f)
	,m_boss(nullptr)
{
	m_mode = COLIDE_EIDT_MODE::BOSSDOOR2BOX;
	m_sponType = MONSETER_TYPE::DOOR2;	
	m_destPos = 2712.f;
	m_zeroPos = 80.f;

	m_closeTo = PLAYER_STATE::EVENT;

	GETINSTANCE(CResourceManager)->LoadSound(L"bossbackground", L"sound\\bossbackground.wav");
	GETINSTANCE(CResourceManager)->FindSound(L"bossbackground")->SetPosition(0.f);
	GETINSTANCE(CResourceManager)->FindSound(L"bossbackground")->SetVolume(25.f);
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
		m_state = DOORSTATE::WARNING;
	}

	if (m_state == DOORSTATE::WARNING)
	{
		m_warningDelay += DELTATIME;
		if (m_warningDelay >= 3.f)
		{
			CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
			CRockmanLevel* rmLevel = dynamic_cast<CRockmanLevel*>(lv);
			m_state = DOORSTATE::WARNINGEXIT;
			rmLevel->m_textureReadyAnim->Remove();
			m_warningDelay = 0.f;
		}
	}
	else if (m_state == DOORSTATE::WARNINGEXIT)
	{
		m_warningDelay += DELTATIME;
		if (m_warningDelay >= 1.5f)
		{	
			m_boss = new CCyberKujacer();
			m_boss->m_bossState = CYBERBOSS_STATE::SPON;
			CGameObject::Instantiate(m_boss, m_zero->GetPos() + Vector2(500.f, -300.f), LAYER::MONSTER);
			m_warningDelay = 0.f;
			m_state = DOORSTATE::MONSTERSPON;
		}
	}
	else  if (m_state == DOORSTATE::MONSTERSPON)
	{
		if (m_boss->GetAnimator()->GetCurAnimation()->IsFinish() == true)
		{
			m_warningDelay += DELTATIME;
			if (m_warningDelay >= 1.5f)
			{			
				m_boss->GetAnimator()->Play(L"TING", false);
				m_state = DOORSTATE::MONSTERSTART;
				m_warningDelay = 0.f;
			}
		}
	}
	else  if (m_state == DOORSTATE::MONSTERSTART)
	{
		if (m_boss->GetAnimator()->GetCurAnimation()->IsFinish() == true)
		{
			m_warningDelay += DELTATIME;
			if (m_warningDelay >= 0.9f)
			{
				m_boss->GetAnimator()->Play(L"MOVE", false);
				m_zero->SetState(PLAYER_STATE::IDLE);
				m_boss->m_stateDelay = 0.f;
				m_boss->m_bossState = CYBERBOSS_STATE::MOVEINVISIBLE;				
				m_state = DOORSTATE::DOORFINISH;
				
				m_warningDelay = 0.f;
				GETINSTANCE(CResourceManager)->FindSound(L"bossbackground")->PlayToBGM(true);
			}
		}
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
	if (m_state == DOORSTATE::DOORFINISH)
	{
		return;
	}
	CDoor1::OnTriggerEnter(_pOther);
}


