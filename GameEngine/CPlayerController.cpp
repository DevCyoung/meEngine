#include "pch.h"
#include "CPlayerController.h"
#include "CKeyManager.h"
#include "CZero.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTimeManager.h"
#include "CCamera.h"
#include "CRigidbody.h"

CPlayerController::CPlayerController(CGameObject* obj)
	:CComponent(obj)
	, m_zero(nullptr)
	, m_state{}
	, m_attackDealy(0.f)
	, m_moveScale(0.f)
	, m_fallingMoveScale(0.f)
	, m_dashMoveScale(0.f)
	, m_dir(0)
	, m_velocity{}
	, m_jumpScale(0.f)
	, m_curdashScale(0.f)
{

	m_zero = dynamic_cast<CZero*>(obj);
	assert(m_zero);
	m_animator = m_zero->GetAnimator();
	m_state = PLAYER_STATE::IDLE;

	m_moveScale = 270.0f;
	m_fallingMoveScale = 220.f;
	m_dashMoveScale = 1.85f;
	m_curdashScale = 1.f;
	m_jumpScale = -720.f;
	
}

CPlayerController::CPlayerController(const CGameObject& _other)
	:CComponent(nullptr)
	, m_zero(nullptr)
	, m_state{}
	, m_attackDealy(0.f)
	, m_moveScale(0.f)
	, m_fallingMoveScale(0.f)
	, m_dashMoveScale(0.f)
	, m_dir(0)
	, m_velocity{}
	, m_jumpScale(0.f)
	, m_curdashScale(0.f)
{
}

CPlayerController::~CPlayerController()
{
}


void CPlayerController::tick()
{

	Vector2 pos = m_zero->GetPos();
	Vector2 velo = m_zero->GetRigidbody()->GetVelocity();

	velo.x = 0.f;
	m_velocity.x = 0.f;
	m_velocity.y = velo.y;

	//입력외의 변수들 설정
	if (m_zero->DownColState() == false && m_state != PLAYER_STATE::FALLING && m_state != PLAYER_STATE::WALLSLIDE && m_state != PLAYER_STATE::JUMP)
	{
		if (velo.y > 0.01f)
		{			
			m_state = PLAYER_STATE::FALLING;
			m_animator->TrigerPlay(L"FALLINGREADY", false);
		}
	}

	//입력에따른 변수를 설정
	InputTick();
	StateTick();

	//Move
	if (m_state == PLAYER_STATE::WALK || m_state == PLAYER_STATE::JUMP)
	{
		m_velocity.x = m_moveScale * m_dir * m_curdashScale;
	}
	else if (m_state == PLAYER_STATE::DASH)
	{
	}
	else if (m_state == PLAYER_STATE::FALLING)
	{
		m_velocity.x = m_fallingMoveScale * m_dir * m_curdashScale;
	}
	else if (m_state == PLAYER_STATE::IDLE)
	{
		//m_animator->TrigerPlay(L"IDLE", false);

		m_velocity.x = 0.f;
	}
	else if (m_state == PLAYER_STATE::WALLSLIDE)
	{
		//m_zero->GetRigidbody()->SetGravity(false);
		m_velocity.y = 0.f;
		pos.y += 200.f * DELTATIME;
	}

	if (m_zero->LeftColState() || m_zero->RightColState())
	{
		m_curdashScale = 1.f;
	}




	m_zero->SetPos(pos);
	m_zero->GetRigidbody()->SetVelocity(m_velocity);
	Vector2 camPos = GETINSTANCE(CCamera)->GetLook();
	camPos.x = pos.x;
	GETINSTANCE(CCamera)->SetLook(camPos);
}

void CPlayerController::InputTick()
{
	if (IS_INPUT_TAB(KEY::Z))
	{
		m_animator->Play(L"FALLINATTACK", false);
	}
	if (IS_INPUT_TAB(KEY::X))												//점프도 땅에만붙어있으면 언제든지 상태가바뀜
	{
		if (m_zero->DownColState() && m_state != PLAYER_STATE::FALLING && m_state != PLAYER_STATE::JUMP)
		{
			m_animator->Play(L"JUMPREADY", true);
			m_velocity.y = 0.f;
			m_state = PLAYER_STATE::JUMP;
		}
		else if (m_zero->DownColState() == false && (m_zero->LeftColState() == true || m_zero->RightColState() == true))
		{
			m_animator->Play(L"JUMPREADY", true);
			m_velocity.y = 0.f;
			m_state = PLAYER_STATE::JUMP;
		}

	}
	if (IS_INPUT_PRESSED(KEY::C))
	{
		if (m_zero->DownColState() && m_state != PLAYER_STATE::DASH)
		{
			m_animator->TrigerPlay(L"DASH", true);
			m_curdashScale = m_dashMoveScale;
			m_state = PLAYER_STATE::DASH;
		}
	}
	if (IS_INPUT_PRESSED(KEY::LEFT))
	{
		if (m_zero->LeftColState() == false)
		{
			m_dir = -1;
			if (m_zero->DownColState() && m_state == PLAYER_STATE::IDLE)
			{
				m_animator->Play(L"WALKREADY", false);
				m_state = PLAYER_STATE::WALK;
			}
		}
		else
		{
			m_dir = 0;
		}		
	}
	if (IS_INPUT_PRESSED(KEY::RIGHT) )
	{
		if (m_zero->RightColState() == false)
		{
			m_dir = 1;
			if (m_zero->DownColState() && m_state == PLAYER_STATE::IDLE)
			{
				m_animator->Play(L"WALKREADY", true);
				m_state = PLAYER_STATE::WALK;
			}
		}
		else
		{
			m_dir = 0;
		}
	}
	if (IS_INPUT_PRESSED(KEY::UP))
	{

	}
	if (IS_INPUT_PRESSED(KEY::DOWN))
	{

	}

	//이동하지않음
	if (IS_INPUT_PRESSED(KEY::LEFT) == false && IS_INPUT_PRESSED(KEY::RIGHT) == false)
	{
		m_dir = 0;
	}
	if (IS_INPUT_PRESSED(KEY::LEFT) == true && IS_INPUT_PRESSED(KEY::RIGHT) == true)
	{
		m_dir = 0;
	}
}


void CPlayerController::StateTick()
{
	switch (m_state)
	{
	case PLAYER_STATE::IDLE:
		Idle();
		break;
	case PLAYER_STATE::WALK:
		Walk();
		break;
	case PLAYER_STATE::DASH:
		LANDDASH();
		break;
	case PLAYER_STATE::JUMP:
		Jump();
		break;
	case PLAYER_STATE::LANDATTACK1:
		LandAttack1();
		break;
	case PLAYER_STATE::LANDATTACK2:
		LandAttack2();
		break;
	case PLAYER_STATE::LANDATTACK3:
		LandAttack3();
		break;
	case PLAYER_STATE::FALLINGATTACK:
		FallingAttack();
		break;
	case PLAYER_STATE::WALLSLIDEATTACK:
		WallSlideAttack();
		break;
	case PLAYER_STATE::FALLING:
		Falling();
		break;
	case PLAYER_STATE::WALLSLIDE:
		WallSlide();
		break;
	}
}

void CPlayerController::final_tick()
{

}

void CPlayerController::Walk()
{		
	m_velocity.x = m_moveScale * m_dir;

	if (IS_INPUT_RELEASE(KEY::LEFT) || IS_INPUT_RELEASE(KEY::RIGHT) || m_dir == 0)
	{
		m_animator->TrigerPlay(L"WALKFINISH", false);
		//m_animator->TrigerPlay(L"IDLE", true);
		m_state = PLAYER_STATE::IDLE;
	}

	//m_animator->TrigerPlay(L"IDLE", true);
}
void CPlayerController::Move()
{

}

void CPlayerController::render(HDC _dc)
{
}

void CPlayerController::Idle()
{
	//m_animator->TrigerPlay(L"IDLE", true);

	/*if (m_zero->DownColState() == false)
	{
		m_animator->TrigerPlay(L"IDLE", true);
	}*/
	
}



void CPlayerController::LANDDASH()
{
	/*if (INPUT_END_TIME(KEY::C, 0.15f) <= 0.14f)
	{
		m_velocity.x = m_jumpScale;
	}
	if (m_zero->DownColState() == false)
	{
		if (IS_INPUT_RELEASE(KEY::X) || m_velocity.y > 0.01f)
		{
			m_velocity.y = 0.f;
			m_animator->TrigerPlay(L"FALLINGREADY", false);
			m_state = PLAYER_STATE::FALLING;
		}
	}*/
}

void CPlayerController::Jump()
{/*
	if (IS_INPUT_PRESSED(KEY::X) && INPUT_END_TIME(KEY::X, 0.25f) <= 0.24f)
	{
		m_velocity.y = m_jumpScale  * INPUT_ACELL(KEY::X, 2.f, 1.f);
	}*/


	float jscale = m_jumpScale;
	

	if (m_zero->DownColState() == false && (m_zero->LeftColState() == true || m_zero->RightColState() == true))
	{
		jscale = m_jumpScale * 0.8f;
		//m_zero->GetRigidbody()->AddForce(Vector2(200000.f, 1.f));
	}

	
	if (INPUT_END_TIME(KEY::X, 0.15f) <= 0.14f && IS_INPUT_PRESSED(KEY::X))
	{
		m_velocity.y = jscale;
	}
	else if (m_zero->DownColState() == false)
	{
		if (IS_INPUT_RELEASE(KEY::X) || m_velocity.y > 0.01f)
		{
			m_velocity.y = 0.f;
			m_animator->TrigerPlay(L"FALLINGREADY", false);
			m_state = PLAYER_STATE::FALLING;
		}
	}
}

void CPlayerController::Falling()
{
	//m_animator->TrigerPlay(L"FALLING", true);
	//바닥과 붙어있다면 -> IDLE
	if (m_zero->DownColState() == true)
	{
		m_animator->Play(L"LANDING", false);
		m_state = PLAYER_STATE::IDLE;
	}
	else if (m_zero->LeftColState() == true && IS_INPUT_PRESSED(KEY::LEFT))
	{
		m_animator->TrigerPlay(L"WALLSLIDE", true);
		m_state = PLAYER_STATE::WALLSLIDE;
	}
	else if (m_zero->RightColState() == true && IS_INPUT_PRESSED(KEY::RIGHT))
	{
		m_animator->TrigerPlay(L"WALLSLIDE", true);
		m_state  = PLAYER_STATE::WALLSLIDE;
	}
	else 
	{
		
	}
}

void CPlayerController::LandAttack1()
{
	UINT cnt = m_zero->GetAttackState();

	if (IS_INPUT_TAB(KEY::Z) && cnt == 1)
	{
		m_animator->Play(L"ATTACK2", false);
		m_state = PLAYER_STATE::LANDATTACK2;
	}
}

void CPlayerController::LandAttack2()
{
	UINT cnt = m_zero->GetAttackState();

	if (IS_INPUT_TAB(KEY::Z) && cnt == 2)
	{
		m_animator->Play(L"ATTACK3", false);
		m_state = PLAYER_STATE::LANDATTACK3;
	}
}

void CPlayerController::LandAttack3()
{
	UINT cnt = m_zero->GetAttackState();

	if (IS_INPUT_TAB(KEY::Z) && cnt == 3)
	{
		cnt = 0;
		m_animator->Play(L"ATTACK1", false);
		m_state = PLAYER_STATE::LANDATTACK1;
	}
}

void CPlayerController::FallingAttack()
{
}

void CPlayerController::WallSlide()
{
	//m_zero->GetRigidbody()->SetGravity(false);	
	//m_velocity.y = 0.f;


	//else if (m_zero->LeftColState() == false && m_zero->RightColState() == false)
	//{
	//	m_animator->Play(L"FALLINGREADY", false);
	//	m_state = PLAYER_STATE::FALLING;
	//}
	if (m_zero->DownColState() == true)
	{
		m_animator->Play(L"LANDING", false);
		m_state = PLAYER_STATE::IDLE;
	}

	if (m_zero->LeftColState() == true)
	{
		if (IS_INPUT_RELEASE(KEY::LEFT) || IS_INPUT_TAB(KEY::RIGHT))
		{
			m_state = PLAYER_STATE::IDLE;
		}
	}
	if (m_zero->RightColState() == true)
	{
		if (IS_INPUT_RELEASE(KEY::RIGHT) || IS_INPUT_TAB(KEY::LEFT))
		{
			m_state = PLAYER_STATE::IDLE;
		}
	}

	if (IS_INPUT_PRESSED(KEY::LEFT) && m_zero->LeftColState() == false)
	{
		m_state = PLAYER_STATE::IDLE;
	}
	else if (IS_INPUT_PRESSED(KEY::RIGHT) && m_zero->RightColState() == false)
	{
		m_state = PLAYER_STATE::IDLE;
	}
}

void CPlayerController::WallSlideAttack()
{
}

