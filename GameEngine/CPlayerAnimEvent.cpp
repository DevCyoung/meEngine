#include "pch.h"
#include "CPlayerAnimEvent.h"
#include "CGameObject.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRenderHelper.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CZero.h"

#include "CResourceManager.h"
#include "CSound.h"

#include "CEffectManager.h"

CPlayerAnimEvent::CPlayerAnimEvent(CGameObject* obj)
	:CComponent(obj)
	, m_animztor(nullptr)
	, m_attackCount(0)
	, m_zero(nullptr)
{
	//GetAnimator()->LoadAnimation(L"animation\\zero\\thunder.anim");
	m_zero = dynamic_cast<CZero*>(obj);

	m_animztor = obj->GetAnimator();
	assert(m_animztor);
	m_animztor->LoadAnimation(L"animation\\zero\\IDLE.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\attack.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\walk.anim");
	
	m_animztor->LoadAnimation(L"animation\\zero\\jumpready.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\jump.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\fallingready.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\falling.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\landing.anim");

	m_animztor->LoadAnimation(L"animation\\zero\\wallslide.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\walkready.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\walkfinish.anim");

	m_animztor->LoadAnimation(L"animation\\zero\\walljumpready.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\wallslideready.anim");


	m_animztor->LoadAnimation(L"animation\\zero\\fallinattack.anim");


	m_animztor->LoadAnimation(L"animation\\zero\\fireready.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\fire.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\firefinish.anim");


	m_animztor->LoadAnimation(L"animation\\zero\\attack1.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\attack2.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\attack3.anim");

	m_animztor->LoadAnimation(L"animation\\zero\\thunder.anim");
	
	m_animztor->LoadAnimation(L"animation\\zero\\dashready.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\dash.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\dashfinish.anim");


	m_animztor->LoadAnimation(L"animation\\zero\\vimblink.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\enterzero.anim");


	m_animztor->LoadAnimation(L"animation\\zero\\returnready.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\returnblink.anim");

	//damaged
	m_animztor->LoadAnimation(L"animation\\zero\\damaged.anim");
	m_animztor->LoadAnimation(L"animation\\zero\\damagedready.anim");


	m_animztor->FindAnimation(L"JUMPREADY")->SetFrameEvent(1, this, (DELEGATE)&CPlayerAnimEvent::JumpReady);
	m_animztor->FindAnimation(L"FALLINGREADY")->SetFrameEvent(4, this, (DELEGATE)&CPlayerAnimEvent::FallingReady);
	m_animztor->FindAnimation(L"FIREREADY")->SetFrameEvent(4, this, (DELEGATE)&CPlayerAnimEvent::FireReady);
	
	m_animztor->FindAnimation(L"WALKREADY")->SetFrameEvent(2, this, (DELEGATE)&CPlayerAnimEvent::WalkReady);
	m_animztor->FindAnimation(L"WALKFINISH")->SetFrameEvent(2, this, (DELEGATE)&CPlayerAnimEvent::Idle);
	m_animztor->FindAnimation(L"LANDING")->SetFrameEvent(2, this, (DELEGATE)&CPlayerAnimEvent::Idle);
	m_animztor->FindAnimation(L"ENTERZERO")->SetFrameEvent(13, this, (DELEGATE)&CPlayerAnimEvent::Enter);

	m_animztor->FindAnimation(L"DASHFINISH")->SetFrameEvent(4, this, (DELEGATE)&CPlayerAnimEvent::Idle);

	m_animztor->FindAnimation(L"ATTACK1")->SetFrameEvent(18, this, (DELEGATE)&CPlayerAnimEvent::Idle);
	m_animztor->FindAnimation(L"ATTACK2")->SetFrameEvent(16, this, (DELEGATE)&CPlayerAnimEvent::Idle);
	m_animztor->FindAnimation(L"ATTACK3")->SetFrameEvent(19, this, (DELEGATE)&CPlayerAnimEvent::Idle);
	m_animztor->FindAnimation(L"FALLINATTACK")->SetFrameEvent(8, this, (DELEGATE)&CPlayerAnimEvent::Falling);


	m_animztor->FindAnimation(L"ATTACK1")->SetFrameEvent(5, this, (DELEGATE)&CPlayerAnimEvent::Attack1);
	m_animztor->FindAnimation(L"ATTACK2")->SetFrameEvent(5, this, (DELEGATE)&CPlayerAnimEvent::Attack2);
	m_animztor->FindAnimation(L"ATTACK3")->SetFrameEvent(6, this, (DELEGATE)&CPlayerAnimEvent::Attack3);

	m_animztor->FindAnimation(L"ATTACK1")->SetFrameEvent(0, this, (DELEGATE)&CPlayerAnimEvent::Attack1Reday);
	m_animztor->FindAnimation(L"ATTACK2")->SetFrameEvent(0, this, (DELEGATE)&CPlayerAnimEvent::Attack2Reday);
	m_animztor->FindAnimation(L"ATTACK3")->SetFrameEvent(0, this, (DELEGATE)&CPlayerAnimEvent::Attack3Reday);




	m_animztor->FindAnimation(L"WALLJUMPREADY")->SetFrameEvent(3, this, (DELEGATE)&CPlayerAnimEvent::JumpReady);
	m_animztor->FindAnimation(L"WALLJUMPREADY")->SetFrameEvent(0, this, (DELEGATE)&CPlayerAnimEvent::JumpReadyEffect);

	m_animztor->FindAnimation(L"WALLSLIDEREADY")->SetFrameEvent(2, this, (DELEGATE)&CPlayerAnimEvent::WallSlideReady);
	m_animztor->FindAnimation(L"RETURNREADY")->SetFrameEvent(8, this, (DELEGATE)&CPlayerAnimEvent::ReturnReady);



	m_animztor->FindAnimation(L"DASHREADY")->SetFrameEvent(2, this, (DELEGATE)&CPlayerAnimEvent::LandDashReady);
	m_animztor->FindAnimation(L"DASHREADY")->SetFrameEvent(0, this, (DELEGATE)&CPlayerAnimEvent::LandDashReadyEffect);

	m_animztor->FindAnimation(L"WALLSLIDE")->SetFrameEvent(0, this, (DELEGATE)&CPlayerAnimEvent::WallSlideEffect);
	//m_animztor->FindAnimation(L"WALLSLIDE")->SetFrameEvent(1, this, (DELEGATE)&CPlayerAnimEvent::WallSlideEffect);
	m_animztor->FindAnimation(L"WALLSLIDE")->SetFrameEvent(2, this, (DELEGATE)&CPlayerAnimEvent::WallSlideEffect);


	m_animztor->FindAnimation(L"DAMAGEDREADY")->SetFrameEvent(3, this, (DELEGATE)&CPlayerAnimEvent::DamagedReady);

	m_animztor->Play(L"IDLE", true);


}

CPlayerAnimEvent::CPlayerAnimEvent(const CGameObject& _other)
	:CComponent(nullptr)
	, m_animztor(nullptr)
	, m_attackCount(0)
	, m_zero(nullptr)
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

void CPlayerAnimEvent::WallJumpReady()
{ 
	m_animztor->Play(L"JUMP", true);
}

void CPlayerAnimEvent::WallSlideReady()
{
	m_animztor->Play(L"WALLSLIDE", true);
}

void CPlayerAnimEvent::LandDashReady()
{
	m_animztor->Play(L"DASH", true);

	GETINSTANCE(CEffectManager)->OnShootPlay(EFFECT_TYPE::LANDDASHPOWER, m_zero->GetPos(), !m_zero->GetFlipX());
}

void CPlayerAnimEvent::FireReady()
{
	m_animztor->Play(L"FIRE", true);
}

void CPlayerAnimEvent::DashFinish()
{
	m_animztor->Play(L"IDLE", true);
}

void CPlayerAnimEvent::ReturnReady()
{	
	m_zero->SetState(PLAYER_STATE::BLINK);
	m_animztor->Play(L"RETURNBLINK", true);
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

void CPlayerAnimEvent::Attack1Reday()
{	
	GETINSTANCE(CResourceManager)->LoadSound(L"ATTACK1", L"sound\\hu.wav")->Play();
	GETINSTANCE(CResourceManager)->LoadSound(L"saver",   L"sound\\saver.wav")->SetPosition(0);
	GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->SetVolume(18.f);
	GETINSTANCE(CResourceManager)->LoadSound(L"saver",   L"sound\\saver.wav")->Play();
}

void CPlayerAnimEvent::Attack2Reday()
{
	GETINSTANCE(CResourceManager)->LoadSound(L"ATTACK2", L"sound\\ha.wav")->Play();
	GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->SetPosition(0);
	GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->SetVolume(18.f);
	GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->Play();
}

void CPlayerAnimEvent::Attack3Reday()
{
	GETINSTANCE(CResourceManager)->LoadSound(L"ATTACK3", L"sound\\huo.wav")->Play();
	GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->SetPosition(0);
	GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->SetVolume(18.f);
	GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->Play();
}

void CPlayerAnimEvent::DamagedReady()
{
	m_animztor->Play(L"DAMAGED", true);
	GETINSTANCE(CResourceManager)->LoadSound(L"zeroHit", L"sound\\zeroHit.wav")->SetPosition(0);
	GETINSTANCE(CResourceManager)->LoadSound(L"zeroHit", L"sound\\zeroHit.wav")->SetVolume(18.f);
	GETINSTANCE(CResourceManager)->LoadSound(L"zeroHit", L"sound\\zeroHit.wav")->Play();
}

void CPlayerAnimEvent::Idle()
{
	m_animztor->Play(L"IDLE", true);
	m_attackCount = 0;
}

void CPlayerAnimEvent::Enter()
{
	m_animztor->Play(L"IDLE", true);
	m_zero->SetState(PLAYER_STATE::IDLE);
}

void CPlayerAnimEvent::WallSlideEffect()
{
	Vector2 pos = m_zero->GetPos();
	pos.y += 80.f;

	if (m_zero->GetFlipX())
	{
		pos.x += 45.f;
	}
	else
	{
		pos.x -= 45.f;
	}

	GETINSTANCE(CEffectManager)->OnShootPlay(EFFECT_TYPE::WALLSLIDEDUST, pos, !m_zero->GetFlipX());
}

void CPlayerAnimEvent::JumpReadyEffect()
{
	GETINSTANCE(CEffectManager)->OnShootPlay(EFFECT_TYPE::WALLHIT, m_zero->GetPos(), !m_zero->GetFlipX());
}

void CPlayerAnimEvent::LandDashReadyEffect()
{
	Vector2 pos = m_zero->GetPos();
	pos.y += 20.f;

	if (m_zero->GetFlipX())
	{
		pos.x -= 90.f;
	}
	else
	{
		pos.x += 90.f;
	}

	GETINSTANCE(CEffectManager)->OnShootPlay(EFFECT_TYPE::LANDDASH, pos, !m_zero->GetFlipX());

}

void CPlayerAnimEvent::Falling()
{
	m_animztor->TrigerPlay(L"FALLING", true);	
}