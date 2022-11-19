#include "pch.h"
#include "CZero.h"
#include "CLineColManager.h"
#include "CLineCollider.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CCamera.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResourceManager.h"

#include "CRigidbody.h"
#include "CPlayerController.h"
#include "CPlayerAnimEvent.h"
#include "CLevelManager.h"

#include "CRockmanManager.h"

#include "CResourceManager.h"
#include "CSound.h"
#include "CRockmanLevel.h"

#include "CSoundMgr.h"
void CZero::OnTriggerEnter(CCollider* _pOther)
{
	CRockmanObj::OnTriggerEnter(_pOther);

	
	
}

void CZero::OnTriggerStay(CCollider* _pOther)
{

	if ((_pOther->GetOwner()->GetLayer() == LAYER::MONSTERATTACK || _pOther->GetOwner()->GetLayer() == LAYER::MONSTER) && m_damagedState != DAMAGED_STATE::ULTIMAGE)
	{

		if (_pOther->GetOwner()->m_isAttackable == false)
			return;

		if (m_playerController->m_state == PLAYER_STATE::RETURNREADY || m_playerController->m_state == PLAYER_STATE::BLINK || m_playerController->m_isKeyinput == false)
		{
			return;
		}
		
		if (m_playerController->m_state == PLAYER_STATE::DIE)
		{
			return;
		}

		SetState(PLAYER_STATE::DAMAGED);
		m_damagedState = DAMAGED_STATE::ULTIMAGE;
		GetAnimator()->Play(L"DAMAGEDREADY", false);
		m_playerController->m_arrDashFrame.clear();
		m_playerController->m_dashMoveScale = 1.f;

		Vector2 dir = _pOther->GetOwner()->GetPos() - GetPos();
		dir.Normalize();
		m_playerController->m_hitDir = dir;
		//GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));
		



		//여기서 데미지를 처리합니다.
		if (m_zeroMode == ZEROMODE::REDZERO)
		{
			m_hp -= 1.f;
		}
		else
		{

		}
		
		//여기서 죽습니다.
		//애니메이션끄기?
		//여기는DIE입니다.
		if (m_hp <= 0)
		{
			//죽습니다.
			
			//GETINSTANCE(CLevelManager)->get
			//우악우악우악
			
			
			//Die.wav
			GETINSTANCE(CResourceManager)->LoadSound(L"die", L"sound\\Die.wav")->SetPosition(0);
			GETINSTANCE(CResourceManager)->LoadSound(L"die", L"sound\\Die.wav")->SetVolume(18.f);
			GETINSTANCE(CResourceManager)->LoadSound(L"die", L"sound\\Die.wav")->Play();

			//GETINSTANCE(CRockmanManager)->m_zeroCurHP = GETINSTANCE(CRockmanManager)->m_zeroMaxHp;
			--GETINSTANCE(CRockmanManager)->m_zeroLife;

			GetAnimator()->Play(L"DIE", false);

			CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
			CRockmanLevel* rmLevel = dynamic_cast<CRockmanLevel*>(lv);
			//현재레벨에접근
			GETINSTANCE(CRockmanManager)->SetEvent(ROCKEVENT::ZERODIE);
			m_playerController->m_state = PLAYER_STATE::DIE;			
			rmLevel->m_isReady = true;

			/*GETINSTANCE(CRockmanManager)->m_backGroundsound->Stop();
			GETINSTANCE(CRockmanManager)->m_backGroundsound->SetPosition(0.f);*/
			//GETINSTANCE(CResourceManager)->FindSound()
			//GETINSTANCE(CLevelManager)->LoadLevel(LEVEL_TYPE::CYBERSPACE2);
		}
	}

}

void CZero::OnTriggerExit(CCollider* _pOther)
{
	CRockmanObj::OnTriggerExit(_pOther);
}



void CZero::OnTriggerEnterLeft(CCollider* _pOther)
{
	CRockmanObj::OnTriggerEnterLeft(_pOther);

	/*Vector2 vPos = GetRigidbody()->GetVelocity();
	GetRigidbody()->SetVelocity(Vector2(0.f, vPos.y));*/
}

void CZero::OnTriggerEnterRight(CCollider* _pOther)
{
	CRockmanObj::OnTriggerEnterRight(_pOther);

	/*Vector2 vPos = GetRigidbody()->GetVelocity();
	GetRigidbody()->SetVelocity(Vector2(0.f, vPos.y));*/
}

void CZero::OnTriggerEnterUp(CCollider* _pOther)

{
	CRockmanObj::OnTriggerEnterUp(_pOther);

	Vector2 scale = _pOther->GetScale();
	Vector2 meScale = GetCollider()->GetScale();

	float dis = scale.y / 2 + meScale.y / 2 - 20.f;

	
	//GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));
}

void CZero::OnTriggerEnterDown(CCollider* _pOther)
{

	CRockmanObj::OnTriggerEnterDown(_pOther);
	m_dirMoveBox = _pOther;

	/*GetRigidbody()->SetGravity(false);
	GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));*/
	
	/*Vector2 vPos = GetPos();
	float disY = _pOther->GetFinalPos().y - _pOther->GetScale().y / 2 - 49.f;
	vPos.y = disY;
	SetPos(vPos);*/
}


void CZero::OnTriggerExitLeft(CCollider* _pOther)
{
	CRockmanObj::OnTriggerExitLeft(_pOther);
}

void CZero::OnTriggerExitRight(CCollider* _pOther)
{
	CRockmanObj::OnTriggerExitRight(_pOther);
}

void CZero::OnTriggerExitUp(CCollider* _pOther)
{
	CRockmanObj::OnTriggerExitUp(_pOther);
}

void CZero::OnTriggerExitDown(CCollider* _pOther)
{
	//m_dirMoveBox = nullptr;
	CRockmanObj::OnTriggerExitDown(_pOther);
	//GetRigidbody()->SetGravity(true);
	//GetRigidbody()->SetVelocity(Vector2(0.f, 0.f));
}

void CZero::CreatePlayerController()
{
	m_playerController = new CPlayerController(this);
}

void CZero::CreateAnimEvent()
{
	m_animEvent = new CPlayerAnimEvent(this);
}
