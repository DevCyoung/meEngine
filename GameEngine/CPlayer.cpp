#include "pch.h"
#include "CPlayer.h"
#include "CGameObject.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CCamera.h"
#include "CEventManager.h"
#include "CMissile.h"
#include "CLevel.h"
#include "CLevelManager.h"

#include "CRigidbody.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"


// helper union to cast pointer to member


CPlayer::CPlayer()
	:m_fSpeed(300.f)
	, attackCount(0)
	, canWalk(false)
	, canWalkReady(true)
	, isAtkkAvailable(true)
{
	this->CreateCollider();
	this->GetCollider()->SetOffsetPos(Vector2(0.f, 0.f));
	this->GetCollider()->SetScale(Vector2(50.f, 50.f));

	/*this->CreateRigidbody();
	this->GetRigidbody()->SetGravity(true);
	this->GetRigidbody()->SetGravityAccel(1600.f);
	this->GetRigidbody()->SetVelocityLimit(300.f);
	this->GetRigidbody()->SetGravityVelocityLimit(330.f);*/


	this->CreateAnimator();
	//GetAnimator()->LoadAnimation(L"animation\\WALK_DOWN.anim");

	/*GetAnimator()->LoadAnimation(L"animation\\LEFT_ATTACK.anim");
	GetAnimator()->LoadAnimation(L"animation\\LEFT_ATTACK2.anim");
	GetAnimator()->LoadAnimation(L"animation\\LEFT_ATTACK3.anim");
	GetAnimator()->LoadAnimation(L"animation\\START.anim");
	GetAnimator()->LoadAnimation(L"animation\\VIM.anim");*/

	//GetAnimator()->LoadAnimation(L"animation\\LEFT_WALK.anim");
	/*GetAnimator()->LoadAnimation(L"animation\\ATTACK_1.anim");
	GetAnimator()->LoadAnimation(L"animation\\ATTACK_2.anim");
	GetAnimator()->LoadAnimation(L"animation\\ATTACK_3.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK.anim");
	GetAnimator()->LoadAnimation(L"animation\\IDLE.anim");
	GetAnimator()->LoadAnimation(L"animation\\SCABBARD.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_READY.anim");
	GetAnimator()->LoadAnimation(L"animation\\START_VIM.anim");
	GetAnimator()->LoadAnimation(L"animation\\RETURN_HOME.anim");

	GetAnimator()->LoadAnimation(L"animation\\JUMP_READY.anim");
	GetAnimator()->LoadAnimation(L"animation\\JUMP.anim");
	GetAnimator()->LoadAnimation(L"animation\\DOWN_READY.anim");
	GetAnimator()->LoadAnimation(L"animation\\DOWN.anim");
	GetAnimator()->LoadAnimation(L"animation\\DOWN_FINISH.anim");*/






	/*GetAnimator()->SetAnimFrameFunc(L"ATTACK_1", 0, this, (DELEGATE)&CPlayer::EventAttack1);
	GetAnimator()->SetAnimFrameFunc(L"ATTACK_2", 0, this, (DELEGATE)&CPlayer::EventAttack2);
	GetAnimator()->SetAnimFrameFunc(L"ATTACK_3", 0, this, (DELEGATE)&CPlayer::EventAttack3);


	GetAnimator()->SetAnimFrameFunc(L"ATTACK_1", 13, this, (DELEGATE)&CPlayer::EventSCABBARD);
	GetAnimator()->SetAnimFrameFunc(L"ATTACK_2", 12, this, (DELEGATE)&CPlayer::EventSCABBARD);
	GetAnimator()->SetAnimFrameFunc(L"ATTACK_3", 15, this, (DELEGATE)&CPlayer::EventSCABBARD);

	GetAnimator()->SetAnimFrameFunc(L"ATTACK_1", 3, this, (DELEGATE)&CPlayer::EventAtkkAvailable);
	GetAnimator()->SetAnimFrameFunc(L"ATTACK_2", 4, this, (DELEGATE)&CPlayer::EventAtkkAvailable);
	GetAnimator()->SetAnimFrameFunc(L"ATTACK_3", 10, this, (DELEGATE)&CPlayer::EventAtkkAvailable);


	GetAnimator()->SetAnimFrameFunc(L"SCABBARD", 4, this, (DELEGATE)&CPlayer::EventIdle);
	GetAnimator()->SetAnimFrameFunc(L"WALK_READY", 2, this, (DELEGATE)&CPlayer::EventWalkReady);

	GetAnimator()->SetAnimFrameFunc(L"START_VIM", 1, this, (DELEGATE)&CPlayer::EventStartVim);
	GetAnimator()->SetAnimFrameFunc(L"START_VIM", 15, this, (DELEGATE)&CPlayer::EventIdle);

	GetAnimator()->SetAnimFrameFunc(L"RETURN_HOME", 5, this, (DELEGATE)&CPlayer::EventReturnHome);*/




	//GetAnimator()->LoadAnimation(L"animation\\WALK.anim");	
	//CTexture* pLinkTex = GETINSTANCE(CResourceManager)->LoadTexture(L"FLY", L"texture\\Zero.bmp");


	/*GetAnimator()->CreateAnimation(L"WALK_DOWN", pLinkTex, Vector2(0.f, 520.f), Vector2(120.f, 130.f), Vector2(0.f, -20.f), 10, 0.1f);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pLinkTex, Vector2(0.f, 650.f), Vector2(120.f, 130.f), Vector2(0.f, -20.f), 10, 0.1f);
	GetAnimator()->CreateAnimation(L"WALK_UP", pLinkTex, Vector2(0.f, 780.f), Vector2(120.f, 130.f), Vector2(0.f, -20.f), 10, 0.1f);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pLinkTex, Vector2(0.f, 910.f), Vector2(120.f, 130.f), Vector2(0.f, -20.f), 10, 0.1f)*/;

	/*GetAnimator()->FindAnimation(L"WALK_DOWN")->Save(L"animation\\WALK_DOWN.anim");
	GetAnimator()->FindAnimation(L"WALK_LEFT")->Save(L"animation\\WALK_LEFT.anim");
	GetAnimator()->FindAnimation(L"WALK_UP")->Save(L"animation\\WALK_UP.anim");
	GetAnimator()->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\WALK_RIGH.anim");*/

	/*GetAnimator()->LoadAnimation(L"animation\\WALK_DOWN.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_UP.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_RIGHT.anim");*/


	//GetAnimator()->Play(L"ATTACK", false);
	// 
	//GetAnimator()->Play(L"IDLE", true);
	//GetAnimator()->Play(L"START_VIM", false);

	//지워야ㅏㅎㅁ
	//m_pTexuture = GETINSTANCE(CResourceManager)->LoadTexture(L"Player", L"texture\\ppap.bmp");

	GetAnimator()->LoadAnimation(L"animation\\ZERO_IDLE.anim");
	GetAnimator()->Play(L"IDLE", true);
}

CPlayer::~CPlayer()
{

}



int cnt = 0;

float m_fRatio = 1.0f;
void CPlayer::tick()
{
	//Vector2 test = this->GetPos();

	//if (IS_INPUT_PRESSED(KEY::LEFT))
	//{
	//	test.x -= m_fSpeed * DELTATIME;
	//}
	//if (IS_INPUT_PRESSED(KEY::RIGHT))
	//{
	//	test.x += m_fSpeed * DELTATIME;
	//}
	//if (IS_INPUT_PRESSED(KEY::UP))
	//{
	//	test.y -= m_fSpeed * DELTATIME;
	//}
	//if (IS_INPUT_PRESSED(KEY::DOWN))
	//{
	//	test.y += m_fSpeed * DELTATIME;
	//}


	//if (IS_INPUT_TAB(KEY::SPACE) || IS_INPUT_PRESSED(KEY::LBTN))
	//{
	//	CMissile* missile = new CMissile();
	//	

	//	Instantiate(missile, GetPos(), LAYER::PLAYER_PROJECTILE);
	//}



	//this->SetPos(test);


	//점프

	if (IS_INPUT_TAB(KEY::LCTRL))
	{
		// 미사일 생성
		/*for (int i = 0; i < 3; ++i)
		{
			CMissile* pMissile = new CMissile;
			pMissile->SetScale(Vec2(20.f, 20.f));
			pMissile->SetSpeed(400.f);
			pMissile->SetDir(75.f + 15.f * (float)i);

			Instantiate(pMissile, GetPos(), LAYER::PLAYER_PROJECTILE);
		}*/

		/*Vector2 V = GetRigidbody()->GetVelocity();

		if (0.f < V.y)
		{
			GetRigidbody()->AddVelocity(Vector2(0.f, -(V.y + 400.f)));
		}
		else
		{
			GetRigidbody()->AddVelocity(Vector2(0.f, -400.f));
		}*/
	}

	////여기부터잠시주석
	//if (IS_INPUT_TAB(KEY::LEFT) && canWalkReady)
	//{
	//	canWalkReady = false;
	//	this->SetFilpX(false);
	//	GetAnimator()->Play(L"WALK_READY", false);
	//}
	//if (IS_INPUT_TAB(KEY::RIGHT) && canWalkReady)
	//{
	//	canWalkReady = false;
	//	this->SetFilpX(true);
	//	GetAnimator()->Play(L"WALK_READY", false);
	//}


	//if (IS_INPUT_RELEASE(KEY::LEFT) && false == canWalkReady)
	//{
	//	canWalkReady = true;
	//	canWalk = false;
	//	GetAnimator()->Play(L"IDLE", true);
	//}
	//if (IS_INPUT_RELEASE(KEY::RIGHT) && false == canWalkReady)
	//{
	//	canWalkReady = true;
	//	canWalk = false;
	//	GetAnimator()->Play(L"IDLE", true);
	//}

	//	//GETINSTANCE(CCamera)->SetLook(GetPos());
	//if (IS_INPUT_PRESSED(KEY::LEFT) && canWalk)
	//{
	//	this->SetFilpX(false);
	//	Vector2 pos = this->GetPos();
	//	pos.x -= 300 * DELTATIME;
	//	this->SetPos(pos);
	//	//GetAnimator()->Play(L"WALK_READY", false);
	//}
	//if (IS_INPUT_PRESSED(KEY::RIGHT) && canWalk)
	//{
	//	this->SetFilpX(true);
	//	Vector2 pos = this->GetPos();
	//	pos.x += 300 * DELTATIME;
	//	this->SetPos(pos);
	//	//GETINSTANCE(CCamera)->SetLook(GetPos());
	//	//GetAnimator()->Play(L"WALK_READY", false);
	//}
	//if (IS_INPUT_PRESSED(KEY::UP) && canWalk)
	//{
	//	Vector2 pos = this->GetPos();
	//	pos.y -= 300 * DELTATIME;
	//	this->SetPos(pos);
	//}
	//if (IS_INPUT_PRESSED(KEY::DOWN) && canWalk)
	//{
	//	Vector2 pos = this->GetPos();
	//	pos.y += 300 * DELTATIME;
	//	this->SetPos(pos);
	//}


	//if (isAtkkAvailable && IS_INPUT_TAB(KEY::Z))
	//{
	//	if (attackCount == 0)
	//	{
	//		GetAnimator()->Play(L"ATTACK_1", false);
	//	}
	//	else if (attackCount == 1)
	//	{
	//		GetAnimator()->Play(L"ATTACK_2", false);
	//	}
	//	else if (attackCount == 2)
	//	{
	//		GetAnimator()->Play(L"ATTACK_3", false);
	//	}		
	//}

	//if (IS_INPUT_TAB(KEY::TAB))
	//{
	//	GetAnimator()->Play(L"START_VIM", false);
	//}

	//if (IS_INPUT_TAB(KEY::ESE))
	//{
	//	GetAnimator()->Play(L"RETURN_HOME", false);
	//}

	//if (IS_INPUT_PRESSED(KEY::X))
	//{		
	//	GetRigidbody()->SetVelocity(Vector2(0, -400.f));		
	//}
	//else
	//{
	//	/*Vector2 pos = this->GetPos();
	//	pos.y += 300 * DELTATIME;
	//	this->SetPos(pos);*/
	//}

	///*if (IS_INPUT_PRESSED(KEY::LEFT))
	//{
	//	Vector2 pos = this->GetPos();
	//	pos.x -= 1000 * DELTATIME;
	//	this->SetPos(pos);
	//}
	//if (IS_INPUT_PRESSED(KEY::RIGHT))
	//{
	//	Vector2 pos = this->GetPos();
	//	pos.x += 1000 * DELTATIME;
	//	this->SetPos(pos);
	//}
	//if (IS_INPUT_PRESSED(KEY::UP))
	//{
	//	Vector2 pos = this->GetPos();
	//	pos.y -= 1000 * DELTATIME;
	//	this->SetPos(pos);
	//}
	//if (IS_INPUT_PRESSED(KEY::DOWN))
	//{
	//	Vector2 pos = this->GetPos();
	//	pos.y += 1000 * DELTATIME;
	//	this->SetPos(pos);
	//}*/



	///*if (IS_INPUT_TAB(KEY::TAB))
	//{
	//	GetAnimator()->Play(L"START", false);
	//}*/

	////if (IS_INPUT_TAB(KEY::LEFT))
	////{		
	////	GetAnimator()->Play(L"LEFT_WALK", true);
	////}

	////if (IS_INPUT_PRESSED(KEY::LEFT))
	////{
	////	Vector2 pos = this->GetPos();
	////	pos.x -= 100 * DELTATIME;
	////	this->SetPos(pos);
	////}

	////if (IS_INPUT_TAB(KEY::UP))
	////{
	////	m_fRatio += 0.1f;
	////	if (m_fRatio <= 1.0000001f)
	////		m_fRatio = 0.0f;

	////}

	////if (IS_INPUT_TAB(KEY::DOWN))
	////{
	////	m_fRatio -= 0.1f;
	////	if (m_fRatio >= 0.99999f)
	////		m_fRatio = 1.0f;
	////}

	///*if (IS_INPUT_TAB(KEY::RIGHT))
	//{
	//	GetAnimator()->Play(L"VIM", false);
	//}*/


	////충돌체등 위치보정
	//CGameObject::tick();
	if (IS_INPUT_TAB(KEY::SPACE))
	{
		//GETINSTANCE(CCamera)->SetLook(GetPos());
	}
}

void CPlayer::render(HDC _dc)
{
	//Vector2 pos = this->GetPos();
	//Vector2 scale = this->GetScale();

	//pos = GETINSTANCE(CCamera)->GetRenderPos(pos);

	//BLENDFUNCTION tBlend = {};

	//tBlend.AlphaFormat = 1;
	//tBlend.BlendFlags = 0;
	//tBlend.BlendOp = AC_SRC_OVER;
	//tBlend.SourceConstantAlpha = (int)(255.f * m_fRatio);
	//tBlend.SourceConstantAlpha = 255 * m_fRatio;
	//AlphaBlend
	//(
	//	_dc,
	//	pos.x - m_pTexuture->Width() / 2,
	//	pos.y - m_pTexuture->Height() / 2,
	//	m_pTexuture->Width(),
	//	m_pTexuture->Height(),
	//	m_pTexuture->GetDC(),
	//	0,
	//	0,
	//	m_pTexuture->Width(),
	//	m_pTexuture->Height(),
	//	tBlend
	//);

	/*BitBlt
	(
		_dc,
		pos.x - m_pTexuture->Width() / 2,
		pos.y - m_pTexuture->Height() / 2,
		m_pTexuture->Width(),
		m_pTexuture->Height(),
		m_pTexuture->GetDC(),
		0,
		0,
		SRCCOPY
	);*/

	/*Rectangle(
		_dc
		, pos.x - scale.x / 2
		, pos.y - scale.y / 2
		, pos.x + scale.x / 2
		, pos.y + scale.y / 2);*/

		//충돌체등 그리기


	CGameObject::render(_dc);
}



void CPlayer::OnTriggerEnter(CCollider* _pOhter)
{

}

void CPlayer::OnTriggerStay(CCollider* _pOhter)
{

}

void CPlayer::OnTriggerExit(CCollider* _pOhter)
{

}

