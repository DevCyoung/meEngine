#include "pch.h"
#include "CPlayerController.h"
#include "CKeyManager.h"
#include "CZero.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTimeManager.h"
#include "CCamera.h"
#include "CRigidbody.h"
#include "CRenderHelper.h"
#include "CTexture.h"
#include "CCamera.h"

#include "CResourceManager.h"
#include "CSound.h"
int check = 0;


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
	, m_attackDelay(0.f)
	, m_jumpTrX(0.f)
	,m_fallingAttackDelay(0.f)
	, m_dashFrameDelay(0.f)
	, m_dashFrameIdx(0)
	, m_specialDelay(0.f)
	, m_isActable(false)
	
{

	m_zero = dynamic_cast<CZero*>(obj);
	assert(m_zero);
	m_animator = m_zero->GetAnimator();
	//m_state = PLAYER_STATE::IDLE;

	m_moveScale = 310.0f;
	m_fallingMoveScale = 220.f;
	m_dashMoveScale = 1.85f;
	m_curdashScale = 1.f;
	m_jumpScale = -720.f;


	//m_state = PLAYER_STATE::ENTER;
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
	, m_attackDelay(0.f)
	, m_jumpTrX(0.f)
	, m_fallingAttackDelay(0.f)
	, m_dashFrameDelay(0.f)
	, m_dashFrameIdx(0)
	, m_specialDelay(0.f)
	, m_isActable(false)
{
}

CPlayerController::~CPlayerController()
{
}


void CPlayerController::tick()
{
	Vector2 pos = m_zero->GetPos();
	Vector2 velo = m_zero->GetRigidbody()->GetVelocity();

	
	if (m_state == PLAYER_STATE::ENTER)
	{		
		if (m_zero->DownColState() == true)
		{
			m_zero->GetAnimator()->TrigerPlay(L"ENTERZERO", false);
		}
		else
		{
			pos.y += 800 * DELTATIME;
			
		}		
	}

	if (m_state == PLAYER_STATE::RETURNREADY)
	{
		if (m_zero->DownColState() == true)
		{
			m_zero->SetCollision(false);
			velo.x = 0.f;
			
			m_zero->GetRigidbody()->SetGravity(false);
			m_zero->GetAnimator()->TrigerPlay(L"RETURNREADY", false);
			GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\returnvim.wav")->SetPosition(0);
			GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\returnvim.wav")->SetVolume(18.f);
			GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\returnvim.wav")->Play();
			m_state = PLAYER_STATE::RETURN;
			m_arrDashFrame.clear();
			m_dashMoveScale = 1.f;
		}		
	}
	else if (m_state == PLAYER_STATE::BLINK)
	{
		pos.y -= 800 * DELTATIME;
	}

	m_zero->SetPos(pos);
	m_zero->GetRigidbody()->SetVelocity(Vector2(velo));
	if (m_state == PLAYER_STATE::ENTER || m_state == PLAYER_STATE::VICTORYRETURN || m_state == PLAYER_STATE::RETURNREADY || m_state == PLAYER_STATE::RETURN || m_state == PLAYER_STATE:: BLINK)
		return;

	

	velo.x = 0.f;
	m_velocity.x = velo.x;
	m_velocity.y = velo.y;
	////check = 0;
	////입력외의 변수들 설정
	if (m_zero->DownColState() == false && m_state != PLAYER_STATE::FALLING && m_state != PLAYER_STATE::WALLSLIDE && m_state != PLAYER_STATE::JUMP && m_state != PLAYER_STATE::FALLINGATTACK)
	{
		if (velo.y > 0.01f)
		{			
			m_state = PLAYER_STATE::FALLING;
			m_animator->Play(L"FALLINGREADY", false);
		}
	}

	//입력에따른 변수를 설정
	

	InputTick();
	StateTick();


	////Move
	if (m_state == PLAYER_STATE::WALK || m_state == PLAYER_STATE::JUMP )
	{
		m_velocity.x = m_moveScale * m_dir * m_curdashScale;
	}
	else if (m_state == PLAYER_STATE::DASH)
	{
		//m_velocity.x = m_moveScale  * m_curdashScale;
	}
	else if (m_state == PLAYER_STATE::FALLING)
	{
		m_velocity.x = m_fallingMoveScale * m_dir * m_curdashScale;
	}
	else if (m_state == PLAYER_STATE::IDLE)
	{		
		m_velocity.x = 0.f;
	}
	else if (m_state == PLAYER_STATE::WALLSLIDE)
	{
		m_velocity.y = 0.f;
		pos.y += 200.f * DELTATIME;
	}



	if (PLAYER_STATE::JUMP == m_state && INPUT_END_TIME(KEY::X, 0.15f) <= 0.14f && IS_INPUT_PRESSED(KEY::X) && m_zero->DownColState() == false)
	{
		if (check != 0)
		{
			if (m_velocity.x > 0)
			{
				m_zero->SetFlipX(false);
			}
			else
			{
				m_zero->SetFlipX(true);
			}
			m_velocity.x = 250 * check * (m_curdashScale * 1);
		}		
	}

	if (INPUT_END_TIME(KEY::C, 0.35f) > 0.08f && PLAYER_STATE::DASH == m_state && INPUT_END_TIME(KEY::C, 0.69f) < 0.68f && IS_INPUT_PRESSED(KEY::C) && m_zero->LeftColState() == false && m_zero->RightColState() == false && m_zero->DownColState() == true)
	{
	
		if (m_zero->GetFilpX() == true)
		{
			
			m_velocity.x = 600;
		}
		else
		{
			m_velocity.x = -600;
		}
	}
	DashFrame();


	m_zero->SetPos(pos);
	m_zero->GetRigidbody()->SetVelocity(m_velocity);
	/*Vector2 camPos = GETINSTANCE(CCamera)->GetLook();
	camPos.x = pos.x;
	camPos.y = pos.y;*/
	//GETINSTANCE(CCamera)->SetLook(camPos);
}

void CPlayerController::flip_tick()
{

	if (PLAYER_STATE::JUMP == m_state && INPUT_END_TIME(KEY::X, 0.15f) <= 0.14f && IS_INPUT_PRESSED(KEY::X) && m_zero->DownColState() == false)
	{
		if (check != 0)
		{
			if (m_velocity.x > 0)
			{
				m_zero->SetFlipX(false);
			}
			else
			{
				m_zero->SetFlipX(true);
			}			
		}
	}

}

void CPlayerController::InputTick()
{
	if (IS_INPUT_TAB(KEY::A))
	{
		if (IS_INPUT_PRESSED(KEY::UP))
		{
		
			m_state = PLAYER_STATE::SPECIALATTACK;
			m_specialDelay = 0.f;
			m_animator->Play(L"FIREREADY", false);
		}
		else
			m_animator->Play(L"THUNDER", false);
	}
	m_fallingAttackDelay += DELTATIME;
	if (IS_INPUT_TAB(KEY::Z))
	{
		if (m_zero->DownColState() == false () && m_state != PLAYER_STATE::WALLSLIDE && m_state != PLAYER_STATE::FALLINGATTACK)
		{
			if (m_fallingAttackDelay  >= 0.55f)
			{
				m_fallingAttackDelay = 0.f;
				m_animator->Play(L"FALLINATTACK", false);
				m_state = PLAYER_STATE::FALLINGATTACK;
				GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->SetPosition(0);
				GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->SetVolume(18.f);
				GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->Play();
				m_curdashScale = 1.f;
			}
		}

		else if (m_zero->DownColState() == true && m_state != PLAYER_STATE::LANDATTACK1 && m_state != PLAYER_STATE::LANDATTACK2 && m_state != PLAYER_STATE::LANDATTACK3)
		{			
			//m_animator->Play(L"ATTACK1", false);
			m_attackDelay = 0.f;
			m_animator->TrigerPlay(L"ATTACK1", false);
			GETINSTANCE(CResourceManager)->LoadSound(L"ATTACK1", L"sound\\hu.wav")->Play();
			GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->SetPosition(0);
			GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->Play();
			m_state = PLAYER_STATE::LANDATTACK1;
			m_curdashScale = 1.f;
		}
	}
	if (IS_INPUT_TAB(KEY::X))												//점프도 땅에만붙어있으면 언제든지 상태가바뀜
	{
		if (m_zero->DownColState() && m_state != PLAYER_STATE::FALLING && m_state != PLAYER_STATE::JUMP)
		{
			GETINSTANCE(CResourceManager)->LoadSound(L"jump", L"sound\\jump.wav")->SetPosition(0);
			GETINSTANCE(CResourceManager)->LoadSound(L"jump", L"sound\\jump.wav")->SetVolume(18.f);
			GETINSTANCE(CResourceManager)->LoadSound(L"jump", L"sound\\jump.wav")->Play();
	
			check = 0;
			m_animator->Play(L"JUMPREADY", true);
			m_velocity.y = 0.f;
			m_state = PLAYER_STATE::JUMP;
		}
		else if ((IS_INPUT_PRESSED(KEY::LEFT) || IS_INPUT_PRESSED(KEY::RIGHT))  && m_state != PLAYER_STATE::JUMP && m_zero->DownColState() == false && (m_zero->LeftColState() == true || m_zero->RightColState() == true))
		{		
			GETINSTANCE(CResourceManager)->LoadSound(L"walljump", L"sound\\walljump.wav")->SetPosition(0);
			GETINSTANCE(CResourceManager)->LoadSound(L"walljump", L"sound\\walljump.wav")->Play();
			GETINSTANCE(CResourceManager)->LoadSound(L"walljump", L"sound\\walljump.wav")->SetVolume(10.f);
			m_animator->TrigerPlay(L"WALLJUMPREADY", false);
			m_velocity.y = 0.f;
			m_state = PLAYER_STATE::JUMP;
		}

	}
	if (IS_INPUT_TAB(KEY::C))
	{
		if (m_state == PLAYER_STATE::WALLSLIDE)
		{
			//if (IS_INPUT_PRESSED(KEY::X))
			m_curdashScale = 2.f;
		}
		if (m_zero->DownColState() && m_state != PLAYER_STATE::DASH && m_zero->LeftColState() == false && m_zero->RightColState() == false)
		{
			GETINSTANCE(CResourceManager)->LoadSound(L"DASH", L"sound\\dash1.wav")->SetPosition(0);
			GETINSTANCE(CResourceManager)->LoadSound(L"DASH", L"sound\\dash1.wav")->Play();
			GETINSTANCE(CResourceManager)->LoadSound(L"DASH", L"sound\\dash1.wav")->SetVolume(20.f);
			m_animator->TrigerPlay(L"DASHREADY", false);
			//m_curdashScale = m_dashMoveScale;
			m_state = PLAYER_STATE::DASH;
			m_attackDealy = 0.f;
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

void CPlayerController::DashFrame()
{
	//대쉬상태일떄
	m_dashFrameDelay += DELTATIME;
	if (m_curdashScale >= 1.9f)
	{
		if (m_dashFrameDelay > 0.06f)
		{
			m_dashFrameIdx = m_dashFrameIdx % DASH_FRAME_SIZE;
			m_dashFrameDelay = 0.f;
			tDashFrame frame;
			frame.frame		= m_animator->GetCurAnimation()->GetCurFrame();
			frame.pos		= m_zero->GetPos();
			frame.duration	= 0.f;
			m_arrDashFrame.push_back(frame);
		}
	}

	for (size_t i = 0; i < m_arrDashFrame.size(); i++)
	{
		m_arrDashFrame[i].duration += DELTATIME;
	}

	for (int i = 0; i < m_arrDashFrame.size(); )
	{
		if (m_arrDashFrame[i].duration >= 0.23f)
		{
			m_arrDashFrame.erase(m_arrDashFrame.begin() + i);
		}
		else
		{
			i++;
		}
	}

}

void CPlayerController::final_tick()
{

}

void CPlayerController::render(HDC _dc)
{
	if (m_state == PLAYER_STATE::RETURN || m_state == PLAYER_STATE::RETURNREADY || m_state == PLAYER_STATE::ENTER)
		return;
	CTexture* tex = m_zero->GetAnimator()->GetCurAnimation()->GetAtlas();
	for (size_t i = 0; i < m_arrDashFrame.size(); i++)
	{
		float dist = (m_arrDashFrame[i].pos - m_zero->GetPos()).Length();
		if (dist <= 20.f)
			continue;
		Vector2 renPos = GETINSTANCE(CCamera)->GetRenderPos(m_arrDashFrame[i].pos);
		CRenderHelper::StretchRender(tex->GetDC(), m_arrDashFrame[i].frame, _dc, renPos, m_zero->GetFilpX());
	}
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
	float jscale = m_jumpScale;


	//if (m_zero->DownColState() == false && (m_zero->LeftColState() == true || m_zero->RightColState() == true))
	//{
	//	jscale = m_jumpScale * 0.75f;
	//	//m_jumpTrX = m_jumpScale * 20.f;
	//	//m_zero->GetRigidbody()->AddForce(Vector2(200000.f, 1.f));



		
	//}
	
	

	m_curdashScale = 2.f;
	if (INPUT_END_TIME(KEY::C, 0.69f) >= 0.68f && IS_INPUT_PRESSED(KEY::C))
	{
		m_animator->TrigerPlay(L"DASHFINISH", false);
		m_state = PLAYER_STATE::IDLE;
		m_curdashScale = 1.f;

	}
	else if (IS_INPUT_RELEASE(KEY::C))
	{
		m_animator->TrigerPlay(L"DASHFINISH", false);
		m_state = PLAYER_STATE::IDLE;
		m_curdashScale = 1.f;
	}
	else if (IS_INPUT_PRESSED(KEY::C))
	{
		//m_dir = 1;
	}

	//else if (m_zero->DownColState() == false)
	//{
	//	if (IS_INPUT_RELEASE(KEY::X) || m_velocity.y > 0.01f)
	//	{
	//		//m_jumpTrX = 0.f;
	//		check = 0;
	//		m_velocity.y = 0.f;
	//		m_animator->TrigerPlay(L"FALLINGREADY", false);
	//		m_state = PLAYER_STATE::FALLING;
	//	}
	//}
}


void CPlayerController::Jump()
{




	/*if (IS_INPUT_PRESSED(KEY::X) && INPUT_END_TIME(KEY::X, 0.25f) <= 0.24f)
	{
		m_velocity.y = m_jumpScale  * INPUT_ACELL(KEY::X, 2.f, 1.f);
	}*/

	float jscale = m_jumpScale;
	
	
	if (m_zero->DownColState() == false && (m_zero->LeftColState() == true || m_zero->RightColState() == true))
	{
		jscale = m_jumpScale * 0.75f;
		//m_jumpTrX = m_jumpScale * 20.f;
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
			//m_jumpTrX = 0.f;
			check = 0;
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
	//m_attackDelay += DELTATIME;
	m_fallingAttackDelay += DELTATIME;
	if (m_zero->DownColState() == true)
	{
		GETINSTANCE(CResourceManager)->LoadSound(L"LANDING", L"sound\\landing.wav")->SetPosition(0);
		GETINSTANCE(CResourceManager)->LoadSound(L"LANDING", L"sound\\landing.wav")->SetVolume(10.f);
		GETINSTANCE(CResourceManager)->LoadSound(L"LANDING", L"sound\\landing.wav")->Play();
		m_animator->Play(L"LANDING", false);
		m_state = PLAYER_STATE::IDLE;
		m_curdashScale = 1.f;
	}
	else if (m_zero->LeftColState() == true && IS_INPUT_PRESSED(KEY::LEFT))
	{
		GETINSTANCE(CResourceManager)->LoadSound(L"wallslidecatch", L"sound\\wallslidecatch.wav")->SetPosition(0);
		GETINSTANCE(CResourceManager)->LoadSound(L"wallslidecatch", L"sound\\wallslidecatch.wav")->Play();
		GETINSTANCE(CResourceManager)->LoadSound(L"wallslidecatch", L"sound\\wallslidecatch.wav")->SetVolume(4.5f);
		m_animator->TrigerPlay(L"WALLSLIDEREADY", false);
		m_state = PLAYER_STATE::WALLSLIDE;
		m_curdashScale = 1.f;
	}
	else if (m_zero->RightColState() == true && IS_INPUT_PRESSED(KEY::RIGHT))
	{
		GETINSTANCE(CResourceManager)->LoadSound(L"wallslidecatch", L"sound\\wallslidecatch.wav")->SetPosition(0);
		GETINSTANCE(CResourceManager)->LoadSound(L"wallslidecatch", L"sound\\wallslidecatch.wav")->Play();
		GETINSTANCE(CResourceManager)->LoadSound(L"wallslidecatch", L"sound\\wallslidecatch.wav")->SetVolume(4.5f);
		m_animator->TrigerPlay(L"WALLSLIDEREADY", false);
		m_state  = PLAYER_STATE::WALLSLIDE;
		m_curdashScale = 1.f;
	}
	else 
	{
		
	}
}

void CPlayerController::LandAttack1()
{
	//UINT cnt = m_zero->GetAttackState();
	m_attackDelay += DELTATIME;

	if (IS_INPUT_TAB(KEY::Z) && m_attackDelay >= 0.15f)
	{
		m_animator->Play(L"ATTACK2", false);
		GETINSTANCE(CResourceManager)->LoadSound(L"ATTACK2", L"sound\\ha.wav")->Play();
		GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->SetPosition(0);
		GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->SetVolume(18.f);
		GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->Play();
		m_state = PLAYER_STATE::LANDATTACK2;
		m_attackDelay = 0.f;
	}
	else if (IS_INPUT_TAB(KEY::X) || IS_INPUT_TAB(KEY::C) || m_attackDelay >= 0.35f)
	{
		m_state = PLAYER_STATE::IDLE;
		m_attackDelay = 0.f;
	}
}

void CPlayerController::LandAttack2()
{
	m_attackDelay += DELTATIME;
	if (IS_INPUT_TAB(KEY::Z) && m_attackDelay >= 0.15f)
	{
		
		GETINSTANCE(CResourceManager)->LoadSound(L"ATTACK3", L"sound\\huo.wav")->Play();
		GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->SetPosition(0);
		GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->SetVolume(18.f);
		GETINSTANCE(CResourceManager)->LoadSound(L"saver", L"sound\\saver.wav")->Play();
		m_animator->Play(L"ATTACK3", false);
		m_state = PLAYER_STATE::LANDATTACK3;
		m_attackDelay = 0.f;
	}
	else if (IS_INPUT_TAB(KEY::X) || IS_INPUT_TAB(KEY::C) || m_attackDelay >= 0.35f)
	{
		m_state = PLAYER_STATE::IDLE;
		m_attackDelay = 0.f;
	}
}

void CPlayerController::LandAttack3()
{
	m_attackDelay += DELTATIME;
	if (m_attackDelay >= 0.55f)
	{
		//m_animator->Play(L"ATTACK3", false);
		m_state = PLAYER_STATE::IDLE;
		m_attackDelay = 0.f;
	}
	else if (IS_INPUT_TAB(KEY::X) || IS_INPUT_TAB(KEY::C))
	{
		m_state = PLAYER_STATE::IDLE;
		m_attackDelay = 0.f;
	}		
}

void CPlayerController::FallingAttack()
{

	m_state = PLAYER_STATE::FALLING;
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
		
	

	if (m_zero->DownColState() == false && m_zero->LeftColState() == true)
	{
		check = 1;
	}
	else if ( m_zero->DownColState() == false && m_zero->RightColState() == true)
	{
		check = -1;
	}
	else
	{
		check = 0;
	}

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

