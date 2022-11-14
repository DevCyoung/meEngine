#include "pch.h"
#include "CRockmanMonster.h"
#include "CCollider.h"
#include "CTimeManager.h"
#include "CEffectManager.h"
#include "CSoundMgr.h"
#include "CSound.h"
#include "CResourceManager.h"

#include "CCamera.h"
#include "CMonsterHitBox.h"
CRockmanMonster::CRockmanMonster()
	:m_hitBox(nullptr)
{
	SetTag(LAYER::MONSTER);
	m_hp = 10;
}

CRockmanMonster::CRockmanMonster(const CRockmanMonster& _other)
	:CRockmanObj(_other)
	, m_hitBox(nullptr)
{
}

CRockmanMonster::~CRockmanMonster()
{
}
void CRockmanMonster::tick()
{
	CRockmanObj::tick();

	//test
	if (m_damagedState == DAMAGED_STATE::DAMAGED)
	{
		m_damagedTime += DELTATIME;
		if (m_damagedTime >= 0.08f)
		{
			m_damagedTime = 0.f;
			m_damagedState = DAMAGED_STATE::IDLE;
		}
	}
	else if (m_damagedState == DAMAGED_STATE::ULTIMAGE)
	{
		//m_damagedState = DAMAGED_STATE::IDLE;
		m_damagedTime = 0.f;
	}
}

void CRockmanMonster::fixed_tick()
{
	CRockmanObj::fixed_tick();
}

void CRockmanMonster::render(HDC _dc)
{
	CRockmanObj::render(_dc);
}

void CRockmanMonster::OnTriggerEnter(CCollider* _pOhter)
{
	

	if (LAYER::PLAYERATTACK == _pOhter->GetOwner()->GetLayer())
	{
		if (m_damagedState != DAMAGED_STATE::ULTIMAGE)
		{
			m_damagedState = DAMAGED_STATE::DAMAGED;
			m_damagedTime = 0.f;
		}
		
		//player attack, monster deffenc
		if (m_damagedState != DAMAGED_STATE::ULTIMAGE)
		{
			--m_hp;
		}
		

		if (m_hp <= 0)
		{

			GETINSTANCE(CEffectManager)->OnShootPlay(EFFECT_TYPE::BOOMRED, GetPos(), GetFlipX());
			GETINSTANCE(CResourceManager)->LoadSound(L"zeroboom", L"sound\\zeroboom.wav")->SetPosition(0);
			GETINSTANCE(CResourceManager)->LoadSound(L"zeroboom", L"sound\\zeroboom.wav")->SetVolume(20.f);
			GETINSTANCE(CResourceManager)->LoadSound(L"zeroboom", L"sound\\zeroboom.wav")->Play();
			GETINSTANCE(CCamera)->CameraShake(10.f, 20.f, 10.f);
			if (nullptr != m_hitBox)
			{
				m_hitBox->_pOwnerAnim = nullptr;
				m_hitBox->Destroy();
			}
			
			this->Destroy();
		}

		if (m_damagedState == DAMAGED_STATE::ULTIMAGE)
		{
			GETINSTANCE(CResourceManager)->LoadSound(L"tin", L"sound\\tin.wav")->SetPosition(0);
			GETINSTANCE(CResourceManager)->LoadSound(L"tin", L"sound\\tin.wav")->SetVolume(20.f);
			GETINSTANCE(CResourceManager)->LoadSound(L"tin", L"sound\\tin.wav")->Play();

			GETINSTANCE(CEffectManager)->OnShootPlay(EFFECT_TYPE::TIN, this->GetPos(), GetFlipX());
		}
		else
		{
			GETINSTANCE(CResourceManager)->LoadSound(L"slice", L"sound\\slice.wav")->SetPosition(0);
			GETINSTANCE(CResourceManager)->LoadSound(L"slice", L"sound\\slice.wav")->SetVolume(20.f);
			GETINSTANCE(CResourceManager)->LoadSound(L"slice", L"sound\\slice.wav")->Play();

			GETINSTANCE(CEffectManager)->OnShootPlay(EFFECT_TYPE::SLOPSLICE, this->GetPos(), GetFlipX());
		}
	}

	

}

void CRockmanMonster::OnTriggerStay(CCollider* _pOhter)
{
}

void CRockmanMonster::OnTriggerExit(CCollider* _pOhter)
{
	//if (LAYER::PLAYERATTACK == _pOhter->GetOwner()->GetLayer())
	//{
	//	m_damagedState = DAMAGED_STATE::IDLE;
	//	m_damagedTime = 0.f;
	//}
}



void CRockmanMonster::Save(FILE* pFile)
{
	MONSTER_STATE monState	 = m_monsterState;
	fwrite(&monState , sizeof(MONSTER_STATE), 1, pFile);

	Vector2 Pos = GetPos();
	fwrite(&Pos, sizeof(Vector2), 1, pFile);

}
void CRockmanMonster::Load(FILE* pFile)
{
	MONSTER_STATE monState;
	fread(&monState, sizeof(MONSTER_STATE), 1, pFile);

	Vector2 pos;
	fread(&pos, sizeof(Vector2), 1, pFile);

	m_monsterState = monState;
	SetPos(pos);
}