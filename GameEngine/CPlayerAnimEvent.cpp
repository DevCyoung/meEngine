#include "pch.h"
#include "CPlayerAnimEvent.h"
#include "CGameObject.h"
#include "CAnimator.h"
#include "CAnimation.h"


CPlayerAnimEvent::CPlayerAnimEvent(CGameObject* obj)
	:CComponent(obj)
	, m_animztor(nullptr)
	, m_attackCount(0)
{
	//GetAnimator()->LoadAnimation(L"animation\\zero\\thunder.anim");
	m_animztor = obj->GetAnimator();
	assert(m_animztor);
	m_animztor->LoadAnimation(L"animation\\zero\\IDLE.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\attack.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\walk.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\dash.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\jumpready.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\jump.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\fallingready.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\falling.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\landing.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\wallslide.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\walkready.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\walkfinish.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\fallinattack.anim");

	m_animztor->LoadAnimation(L"animation\\zero\\attack1.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\attack2.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\attack3.anim");
	
	m_animztor->Play(L"IDLE", true);



	m_animztor->FindAnimation(L"JUMPREADY")->SetFrameEvent(1, this, (DELEGATE)&CPlayerAnimEvent::JumpReady);
	m_animztor->FindAnimation(L"FALLINGREADY")->SetFrameEvent(4, this, (DELEGATE)&CPlayerAnimEvent::FallingReady);

	
	m_animztor->FindAnimation(L"WALKREADY")->SetFrameEvent(2, this, (DELEGATE)&CPlayerAnimEvent::WalkReady);
	m_animztor->FindAnimation(L"WALKFINISH")->SetFrameEvent(2, this, (DELEGATE)&CPlayerAnimEvent::Idle);


	m_animztor->FindAnimation(L"LANDING")->SetFrameEvent(2, this, (DELEGATE)&CPlayerAnimEvent::Idle);

	m_animztor->FindAnimation(L"ATTACK1")->SetFrameEvent(18, this, (DELEGATE)&CPlayerAnimEvent::Idle);
	m_animztor->FindAnimation(L"ATTACK2")->SetFrameEvent(16, this, (DELEGATE)&CPlayerAnimEvent::Idle);
	m_animztor->FindAnimation(L"ATTACK3")->SetFrameEvent(19, this, (DELEGATE)&CPlayerAnimEvent::Idle);
	m_animztor->FindAnimation(L"FALLINATTACK")->SetFrameEvent(8, this, (DELEGATE)&CPlayerAnimEvent::Falling);


	m_animztor->FindAnimation(L"ATTACK1")->SetFrameEvent(4, this, (DELEGATE)&CPlayerAnimEvent::Attack1);
	m_animztor->FindAnimation(L"ATTACK2")->SetFrameEvent(4, this, (DELEGATE)&CPlayerAnimEvent::Attack2);
	m_animztor->FindAnimation(L"ATTACK3")->SetFrameEvent(4, this, (DELEGATE)&CPlayerAnimEvent::Attack3);

}

CPlayerAnimEvent::CPlayerAnimEvent(const CGameObject& _other)
	:CComponent(nullptr)
	, m_animztor(nullptr)
	, m_attackCount(0)
{
}

CPlayerAnimEvent::~CPlayerAnimEvent()
{
}


void CPlayerAnimEvent::tick()
{

}

void CPlayerAnimEvent::final_tick()
{
}

void CPlayerAnimEvent::render(HDC _dc)
{
}

void CPlayerAnimEvent::WalkReady()
{
	m_animztor->Play(L"WALK", true);
}

void CPlayerAnimEvent::JumpReady()
{
	m_animztor->Play(L"JUMP", true);
}

void CPlayerAnimEvent::FallingReady()
{
	m_animztor->Play(L"FALLING", true);
}

void CPlayerAnimEvent::WalkFinish()
{

}

void CPlayerAnimEvent::Attack1()
{
	m_attackCount = 1;
}

void CPlayerAnimEvent::Attack2()
{
	m_attackCount = 2;
}

void CPlayerAnimEvent::Attack3()
{
	m_attackCount = 3;
}

void CPlayerAnimEvent::Idle()
{
	m_animztor->Play(L"IDLE", true);
	m_attackCount = 0;
}

void CPlayerAnimEvent::Falling()
{
	m_animztor->TrigerPlay(L"FALLING", true);	
}