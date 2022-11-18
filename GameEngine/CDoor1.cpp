#include "pch.h"
#include "CDoor1.h"

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

CDoor1::CDoor1()
	: m_wall(nullptr)
	, m_cameraWall(nullptr)
	, m_state(DOORSTATE::IDLE)
	, m_closeTo(PLAYER_STATE::IDLE)
	, m_destPos(0.f)
	, m_zeroPos(0.f)	
{
	m_mode = COLIDE_EIDT_MODE::BOSSDOOR1BOX;

	

	CreateAnimator();

	GetAnimator()->LoadAnimation(L"animation\\object\\door\\idle.anim");
	GetAnimator()->LoadAnimation(L"animation\\object\\door\\open.anim");
	GetAnimator()->LoadAnimation(L"animation\\object\\door\\close.anim");

	GetAnimator()->SetAnimFrameFunc(L"OPEN", 28, this, (DELEGATE)&CDoor1::WorkDoor);
	GetAnimator()->SetAnimFrameFunc(L"OPEN", 0, this, (DELEGATE)&CDoor1::InterRactDoor);

	GetAnimator()->SetAnimFrameFunc(L"CLOSE", 0, this, (DELEGATE)&CDoor1::WorkDoor);
	GetAnimator()->SetAnimFrameFunc(L"CLOSE", 14, this, (DELEGATE)&CDoor1::InterRactDoor);



	GetAnimator()->Play(L"IDLE", false);


	
	GETINSTANCE(CResourceManager)->LoadSound(L"opendoor", L"sound\\openbossroom.wav")->SetVolume(18.f);
	GETINSTANCE(CResourceManager)->LoadSound(L"closedoor", L"sound\\closedoor.wav")->SetVolume(18.f);


	

	m_sponType = MONSETER_TYPE::DOOR1;
	m_destPos = 1760.f;
	m_zeroPos = 60;
}

CDoor1::~CDoor1()
{

}


void CDoor1::tick()
{
	CEventBox::tick();
	switch (m_state)
	{
	case DOORSTATE::IDLE:
		break;
	case DOORSTATE::OPEN:
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish())
		{
			CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
			CRockmanLevel* rmLevel = dynamic_cast<CRockmanLevel*>(lv);

			if (nullptr != m_cameraWall)
			{							
				
				rmLevel->m_cam->m_isFollow = false;
				m_cameraWall->Destroy();
				m_cameraWall = nullptr;
			}

			//GETINSTANCE(CCamera)->SetLook(m_zero->GetPos());

			rmLevel->m_cam->m_position.x += 200.f * DELTATIME * 2;
			
			m_zero->GetAnimator()->SetPlayable(true);
			Vector2 pos = m_zero->GetPos();
			pos.x += m_zeroPos * DELTATIME  * 2;
			m_zero->SetPos(pos);
			rmLevel->m_cam->SetPos(pos);
			if (rmLevel->m_cam->m_position.x >= m_destPos)
			{
				m_state = DOORSTATE::CLOSE;
				m_zero->GetAnimator()->TrigerPlay(L"IDLE", true);
				//m_destPos = 2500.f;
				GetAnimator()->Play(L"CLOSE", false);		

				if (m_closeTo == PLAYER_STATE::EVENT)
				{
					rmLevel->m_textureReadyAnim->Enter();
					GETINSTANCE(CCamera)->SetTextureType(eFADECOLOR::WARNING);
					for (size_t i = 0; i < 6; i++)
					{
						GETINSTANCE(CCamera)->FadeOut(0.45f, 0.6f);
						GETINSTANCE(CCamera)->FadeIn(0.45f, 0.6f);
					}								
				}


			}
		}
	}
		break;
	case DOORSTATE::CLOSE:
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish())
		{
			m_zero->SetState(m_closeTo);
			m_zero->m_playerController->m_curdashScale = 1.f;
			m_state = DOORSTATE::NONE;			
			m_wall = new CWall();
			m_wall->GetCollider()->SetScale(Vector2(110.f, 4000.f));
			CGameObject::Instantiate(m_wall, GetPos(), LAYER::WALL);

		}
	}
		break;
	}
}


void CDoor1::render(HDC _dc)
{
	CRockmanObj::render(_dc);


	if (GETINSTANCE(CCollisionManager)->GetDrawCollide())
	{
		Vector2 pos = GETINSTANCE(CCamera)->GetRenderPos(GetPos());
		TextOut(_dc, pos.x, pos.y, L"DOOR1", 5);
	}

	
}

void CDoor1::OnTriggerEnter(CCollider* _pOther)
{
	if (LAYER::PLAYER == _pOther->GetOwner()->GetLayer())
	{
		CEventBox::OnTriggerEnter(_pOther);
	}

	if (nullptr != m_zero && m_state == DOORSTATE::IDLE)
	{
		m_zero->GetAnimator()->SetPlayable(false);
		m_zero->SetState(PLAYER_STATE::EVENT);
		m_state = DOORSTATE::OPEN;
		GetAnimator()->Play(L"OPEN", false);

	}
}

void CDoor1::WorkDoor()
{	
	GETINSTANCE(CResourceManager)->FindSound(L"closedoor")->SetPosition(0);
	GETINSTANCE(CResourceManager)->FindSound(L"closedoor")->Play();
}


void CDoor1::InterRactDoor()
{
	GETINSTANCE(CResourceManager)->FindSound(L"opendoor")->SetPosition(0);
	GETINSTANCE(CResourceManager)->FindSound(L"opendoor")->Play();

}


void CDoor1::Save(FILE* pFile)
{
	Vector2 pos = GetPos();
	Vector2 scale = GetCollider()->GetScale();

	fwrite(&pos, sizeof(Vector2), 1, pFile);
	fwrite(&scale, sizeof(Vector2), 1, pFile);
}

void CDoor1::Load(FILE* pFile)
{
	Vector2 pos;
	Vector2 scale;

	fread(&pos, sizeof(Vector2), 1, pFile);
	fread(&scale, sizeof(Vector2), 1, pFile);

	GetCollider()->SetScale(scale);
	GetCollider()->SetScale(Vector2(100.f, 200.f));
	SetPos(pos);




	m_cameraWall = new CCameraWall();
	m_cameraWall->m_dir = COLLIDE_DIR::RIGHT;
	m_cameraWall->GetCollider()->SetScale(Vector2(100.f, 1000.f));
	pos.x += 100.f;
	m_cameraWall->SetPos(pos);
	CGameObject::Instantiate(m_cameraWall, pos, LAYER::CAMERAWALL);
}

