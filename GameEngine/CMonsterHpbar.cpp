#include "pch.h"
#include "CMonsterHpbar.h"
#include "CRenderHelper.h"
#include "CResourceManager.h"
#include "CEngine.h"
#include "CTexture.h"
#include "CRockmanObj.h"
#include "CTimeManager.h"
#include "CRockmanMonster.h"

#include "CCyberKujacer.h"

#include "CKeyManager.h"
CMonsterHpbar::CMonsterHpbar()
	 :m_hpTexture(nullptr)
	, m_Maxhp(0)
	, m_target(nullptr)
	, m_HPoffset(0)
	, m_prevHp(0)
	, m_redHp(false)
	, m_HPRedOffset(0)
	, m_distance(0.f)
{
	m_hpTexture = GETINSTANCE(CResourceManager)->LoadTexture(L"BOSSBAR", L"ui\\bosshpbar.bmp");
	Vector2 pos = GETINSTANCE(CEngine)->GetWndScreenSize();
	pos = pos / 2.f;

	pos.x += 430.f;
	pos.y = 176.f;

	//player

	Vector2 offset = {};

	offset.x = 0.f;
	offset.y = 0.f;

	pos += offset;
	m_distance = 252;
	SetPos(pos);
}

CMonsterHpbar::~CMonsterHpbar()
{

}


void CMonsterHpbar::tick()
{
	//비율 224;
	if (nullptr == m_target)
		return;

	if (IS_INPUT_TAB(KEY::SPACE))
	{
		--m_target->m_hp;
	}

	//몇개
	m_HPoffset = (m_distance / (float)m_Maxhp) * ((float)m_Maxhp - (float)m_target->m_hp);


	if (m_HPoffset >= m_distance)
	{
		m_HPoffset = m_distance;
	}

	if (m_prevHp > m_target->m_hp)
	{
		m_prevHp -= DELTATIME * 2;

		if (m_prevHp <= m_target->m_hp)
		{
			m_prevHp = m_target->m_hp;
		}

	}
	else
	{
		m_prevHp = m_target->m_hp;
	}

	m_HPRedOffset = (m_distance / (float)m_Maxhp) * ((float)m_Maxhp - (float)m_prevHp);
}

void CMonsterHpbar::render(HDC _dc)
{

	//if (nullptr != m_target)
	//{

	//	if (m_target->GetState() == PLAYER_STATE::ENTER || m_target->GetState() == PLAYER_STATE::RETURN || m_target->GetState() == PLAYER_STATE::RETURNREADY || m_target->GetState() == PLAYER_STATE::BLINK)
	//	{
	//		return;
	//	}

	//}

	if (nullptr != m_target)
	{
		if (m_target->m_bossState == CYBERBOSS_STATE::SPON || m_target->m_bossState == CYBERBOSS_STATE::ENTER || m_target->m_bossState == CYBERBOSS_STATE::HPZERO)
		{
			return;
		}
	}

	Vector2 pos = GetPos();

	//충돌체를 그린다.
	HPEN hPen = hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::GREEN);;

	HBRUSH	hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);




	HBRUSH	hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);		
	//red
	SelectObject(_dc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(_dc, RGB(128, 34, 28));

	Vector2 hpOffset = {};
	hpOffset.x = 90.f;

	Rectangle
	(
		_dc,
		pos.x - 100 + hpOffset.x,
		pos.y - 155  + m_HPRedOffset,
		pos.x - 80 + hpOffset.x,
		pos.y - 155  + m_distance			//+124 -> 0 // hpbar = y.224
	);
	



	SelectObject(_dc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(_dc, RGB(8, 207, 63));
	//128 34 28
	//8, 207, 63
	Rectangle
	(
		_dc,
		pos.x - 100 + hpOffset.x,
		pos.y - 155 + m_HPoffset,			//+124 -> 0 // hpbar = y.224
		pos.x - 80 + hpOffset.x,
		pos.y - 155 + m_distance
	);

	//SelectObject(_dc, hOriginPen);
	//SelectObject(_dc, hOriginBrush);

	CRenderHelper::StretchRenderTextrue(_dc, m_hpTexture, GetPos());
}
