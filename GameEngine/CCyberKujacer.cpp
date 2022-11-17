#include "pch.h"
#include "CCyberKujacer.h"
#include "CMiru.h"
#include "CAnimator.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CLine.h"
#include "CTimeManager.h"
#include "CAnimation.h"
#include "CZero.h"
#include "CLevelManager.h"

//»èÁ¦
#include "CKeyManager.h"
#include "CLevel.h"
#include "CRockmanLevel.h"

#include "CResourceManager.h"
#include "CSound.h"
#include "CCollider.h"

#include "CMonsterHitBox.h"

#include "CKeyManager.h"

#include "CEffectManager.h"


#include "CCyberMissile.h"

CCyberKujacer::CCyberKujacer()
	:m_ultimateTime(0.f)
	, m_curUltimateTime(0.f)
	, m_reciveAttackCnt(0)
	, m_bossState(CYBERBOSS_STATE::IDLE)
	, m_stateDelay(0.f)
	, m_targetPos{}
	, m_randomAttack(0)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(150.f, 200.f));

	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\cyberboss\\attack1.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\cyberboss\\attack2.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\cyberboss\\attack3.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\cyberboss\\attack2ready.anim");

	GetAnimator()->LoadAnimation(L"animation\\monster\\cyberboss\\attack3shoot.anim");

	GetAnimator()->LoadAnimation(L"animation\\monster\\cyberboss\\enter.anim");	
	GetAnimator()->LoadAnimation(L"animation\\monster\\cyberboss\\ting.anim");

	GetAnimator()->LoadAnimation(L"animation\\monster\\cyberboss\\move.anim");

	//cyberbossmove.wav
	GETINSTANCE(CResourceManager)->LoadSound(L"cyberbossmove", L"sound\\cyberbossmove.wav")->SetPosition(0.f);
	GETINSTANCE(CResourceManager)->LoadSound(L"cyberbossmove", L"sound\\cyberbossmove.wav")->SetVolume(23.f);


	GETINSTANCE(CResourceManager)->LoadSound(L"cyberlandattack", L"sound\\cyberlandattack.wav")->SetPosition(0.f);
	GETINSTANCE(CResourceManager)->LoadSound(L"cyberlandattack", L"sound\\cyberlandattack.wav")->SetVolume(25.f);

	GETINSTANCE(CResourceManager)->LoadSound(L"cyberbossattack2", L"sound\\cyberbossattack2.wav")->SetPosition(0.f);
	GETINSTANCE(CResourceManager)->LoadSound(L"cyberbossattack2", L"sound\\cyberbossattack2.wav")->SetVolume(25.f);

	GETINSTANCE(CResourceManager)->LoadSound(L"tartgetfollow", L"sound\\tartgetfollow.wav")->SetPosition(0.f);
	GETINSTANCE(CResourceManager)->LoadSound(L"tartgetfollow", L"sound\\tartgetfollow.wav")->SetVolume(25.f);
	

	GETINSTANCE(CResourceManager)->LoadSound(L"bossenter", L"sound\\bossenter.wav")->SetPosition(0.f);
	GETINSTANCE(CResourceManager)->LoadSound(L"bossenter", L"sound\\bossenter.wav")->SetVolume(25.f);

	
	GetAnimator()->FindAnimation(L"ENTER")->SetFrameEvent(19, this, (DELEGATE)&CCyberKujacer::EnterEvent);


	//bossenter.wav
	
	GetAnimator()->FindAnimation(L"MOVE")->SetFrameEvent(0, this, (DELEGATE)&CCyberKujacer::MoveEvent);

	GetAnimator()->FindAnimation(L"ATTACK1")->SetFrameEvent(4, this, (DELEGATE)&CCyberKujacer::LandAttack1Event);
	GetAnimator()->FindAnimation(L"ATTACK2")->SetFrameEvent(0, this, (DELEGATE)&CCyberKujacer::Attack2Event);


	GetAnimator()->FindAnimation(L"ATTACK3")->SetFrameEvent(13, this, (DELEGATE)&CCyberKujacer::Attack3Event);

	GetAnimator()->FindAnimation(L"ATTACK3SHOOT")->SetFrameEvent(3, this, (DELEGATE)&CCyberKujacer::Attack3EventMissile);

	GetAnimator()->FindAnimation(L"TING")->SetFrameEvent(4, this, (DELEGATE)&CCyberKujacer::LandAttack1Event);
	

	m_sponType = MONSETER_TYPE::BOSS;
	m_damagedState = DAMAGED_STATE::IDLE;
	m_ultimateTime = 2.f;
	m_hp = 10;
	m_reciveAttackCnt = 0;
	m_bossState = CYBERBOSS_STATE::ENTER;
	GetAnimator()->Play(L"ENTER", false);

	CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
	CRockmanLevel* rmLv = dynamic_cast<CRockmanLevel*>(lv);
	assert(rmLv);
	m_zero = rmLv->m_zero;


	m_hitBox = new CMonsterHitBox();
	m_hitBox->SetOwner(this);
	CGameObject::Instantiate(m_hitBox, Vector2(0.f, 0.f), LAYER::MONSTERATTACK);
	srand((unsigned int)time(NULL));


	//GETINSTANCE(CEffectManager)->SetPlayerTarget(m_zero);
}

CCyberKujacer::CCyberKujacer(const CCyberKujacer& _other)
	:CRockmanMonster(_other)
	,m_ultimateTime(0.f)
	, m_curUltimateTime(0.f)
	, m_reciveAttackCnt(0)
	, m_bossState(CYBERBOSS_STATE::IDLE)
	, m_stateDelay(0.f)
	, m_targetPos{}
	, m_randomAttack(0)
{
}

CCyberKujacer::~CCyberKujacer()
{

}


void CCyberKujacer::tick()
{
	CRockmanMonster::tick();

	Vector2 pos = m_zero->GetPos();

	Vector2 offset = {};

	if (m_bossState == CYBERBOSS_STATE::SPON)
	{
		return;
	}
	//Ultimate
	if (m_damagedState != DAMAGED_STATE::ULTIMAGE && m_reciveAttackCnt >= 1)
	{
		m_damagedState = DAMAGED_STATE::ULTIMAGE;
	}

	if (m_damagedState == DAMAGED_STATE::ULTIMAGE)
	{
		m_curUltimateTime += DELTATIME;
		if (m_curUltimateTime >= m_ultimateTime)
		{
			m_curUltimateTime = 0.f;
			m_damagedState = DAMAGED_STATE::IDLE;
			m_reciveAttackCnt = 0;
		}
	}

	if (m_damagedState == DAMAGED_STATE::ULTIMAGE)
	{
		int t = m_curUltimateTime * 50;
		if (t % 2 == 0)
		{
			m_damagedTime = 0.f;
		}
		else
		{
			m_damagedTime = 1.f;
		}
	}
	else
	{
		m_damagedTime = 0.f;
	}

	int random = rand() % 3;
	//move Logic
	m_stateDelay += DELTATIME;


	if (m_bossState == CYBERBOSS_STATE::ENTER)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish() == true)
		{
			GetAnimator()->Play(L"MOVE", false);
			m_stateDelay = 0.f;
			m_bossState = CYBERBOSS_STATE::MOVEINVISIBLE;
		}
	}
	else if (m_bossState == CYBERBOSS_STATE::MOVEINVISIBLE)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish() == true)
		{
			SetPos(Vector2(-10000.f, -10000.f));	
		
			if (m_stateDelay >= 1.0f)
			{
				m_isAttackable = false;			
				m_bossState = CYBERBOSS_STATE::MOVEVISIBLE;
				
				GetAnimator()->Play(L"MOVE", false);
	
				m_stateDelay = 0.f;
				m_randomAttack = rand() % 3;

				if (m_randomAttack <= 1)
				{
					pos.y = 780.f;
					if (rand() % 2)
					{
						pos.x += 175;
					}
					else
					{
						pos.x -= 175;
					}

					
				}
				else
				{
					
					if (rand() % 2)
					{
						pos.x = 3116;
					}
					else
					{
						pos.x = 2400;
					}

					pos.y = 550;
				}
				SetPos(pos);

				if (GetPos().x > m_zero->GetPos().x)
				{
					SetFlipX(false);
				}
				else
				{
					SetFlipX(true);
				}

			}



		}		
	}
	else if (m_bossState == CYBERBOSS_STATE::MOVEVISIBLE)
	{
	
		if (GetAnimator()->GetCurAnimation()->IsFinish() == true)
		{			
			m_isAttackable = true;
			
			
			
			if (m_randomAttack <= 1)
			{
				if (rand() % 2 == 0)
				{
					GetAnimator()->Play(L"ATTACK1", false);
					m_bossState = CYBERBOSS_STATE::ATTACK1;
					
				}
				else
				{
					GetAnimator()->Play(L"ATTACK2READY", false);
					m_bossState = CYBERBOSS_STATE::ATTACK2READY;
					
				}
			}
			else
			{				
				GetAnimator()->Play(L"ATTACK3", false);
				m_bossState = CYBERBOSS_STATE::ATTACK3;
				m_stateDelay = 0.f;

				
			}
			m_stateDelay = 0.f;
		}
	
		
	}
	else if (m_bossState == CYBERBOSS_STATE::ATTACK1)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish() == true)
		{
			SetPos(Vector2(-10000.f, -10000.f));
			//GetAnimator()->Play(L"MOVE", false);
			m_stateDelay = 0.f;
			m_bossState = CYBERBOSS_STATE::MOVEINVISIBLE;
		}

		if (GetAnimator()->GetCurAnimation()->GetCurFrameIdx() >= 4)
		{
			if (GetFlipX())
			{
				offset.x = +60;
				offset.y = 50;
			}
			else
			{
				offset.x = -60;
				offset.y = 50;
			}
		}
		
		
		GetCollider()->SetOffsetPos(offset);
		
	}
	else if (m_bossState == CYBERBOSS_STATE::ATTACK2READY)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish() == true)
		{	
			GetAnimator()->Play(L"ATTACK2", false);
			m_bossState = CYBERBOSS_STATE::ATTACK2;			
		}		
	}
	else if (m_bossState == CYBERBOSS_STATE::ATTACK2)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish() == true)
		{
			SetPos(Vector2(-10000.f, -10000.f));
			m_stateDelay = 0.f;
			m_bossState = CYBERBOSS_STATE::MOVEINVISIBLE;
		}
		Vector2 pos = GetPos();
		pos.y -= 800 * GETINSTANCE(CTimeManager)->GEtRealDetaTime() + pos.y * DELTATIME * 0.1f;


		

		SetPos(pos);
	}
	else if (m_bossState == CYBERBOSS_STATE::ATTACK3)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish() == true)
		{
			GetAnimator()->Play(L"ATTACK3SHOOT", true);
			m_stateDelay = 0.f;
			m_bossState = CYBERBOSS_STATE::ATTACK3SHOOT;
		}
	}
	else if (m_bossState == CYBERBOSS_STATE::ATTACK3SHOOT)
	{
		if (m_stateDelay >= 5.f)
		{
			GetAnimator()->Play(L"MOVE", false);
			m_stateDelay = 0.f;
			m_bossState = CYBERBOSS_STATE::MOVEINVISIBLE;
		}
	}



	GetCollider()->SetOffsetPos(offset);

}

void CCyberKujacer::fixed_tick()
{
	CRockmanMonster::fixed_tick();
}

void CCyberKujacer::render(HDC _dc)
{
	
	CRockmanMonster::render(_dc);
}


void CCyberKujacer::OnTriggerEnter(CCollider* _pOhter)
{

	CRockmanMonster::OnTriggerEnter(_pOhter);

	if (LAYER::PLAYERATTACK == _pOhter->GetOwner()->GetLayer())
	{
		++m_reciveAttackCnt;
	}
	
}


void CCyberKujacer::OnTriggerStay(CCollider* _pOhter)
{
}

void CCyberKujacer::OnTriggerExit(CCollider* _pOhter)
{
}

void CCyberKujacer::MoveEvent()
{
	GETINSTANCE(CResourceManager)->FindSound(L"cyberbossmove")->Play();
}

void CCyberKujacer::LandAttack1Event()
{
	GETINSTANCE(CResourceManager)->FindSound(L"cyberlandattack")->Play();
}

void CCyberKujacer::Attack2Event()
{
	GETINSTANCE(CResourceManager)->FindSound(L"cyberbossattack2")->Play();


}

void CCyberKujacer::Attack3Event()
{
	Vector2 effectPos = GetPos();
	if (GetFlipX() == true)
	{
		effectPos.x += 180.f;
	}
	else
	{
		effectPos.x -= 180.f;
	}
	effectPos.y += 75.f;
	GETINSTANCE(CResourceManager)->FindSound(L"tartgetfollow")->Play();
	GETINSTANCE(CEffectManager)->OnShootPlay(EFFECT_TYPE::CYBERTARGET, effectPos, true, this);
}

void CCyberKujacer::Attack3EventMissile()
{
	Vector2 effectPos = GetPos();
	if (GetFlipX() == true)
	{
		effectPos.x += 180.f;
	}
	else
	{
		effectPos.x -= 180.f;
	}
	effectPos.y -= 55.f;
	//GETINSTANCE(CEffectManager)->OnShootPlay(EFFECT_TYPE::CYBERTARGET, effectPos, true, this);

	CCyberMissile* missile = new CCyberMissile();
	CGameObject::Instantiate(missile, effectPos, LAYER::MONSTERATTACK);
}

void CCyberKujacer::EnterEvent()
{
	GETINSTANCE(CResourceManager)->FindSound(L"bossenter")->Play();
}

void CCyberKujacer::TingEvent()
{
	GETINSTANCE(CResourceManager)->FindSound(L"bossting")->Play();
}

