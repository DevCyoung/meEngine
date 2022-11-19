#include "pch.h"
#include "CHPbar.h"
#include "CRenderHelper.h"
#include "CResourceManager.h"
#include "CEngine.h"
#include "CTexture.h"
#include "CRockmanObj.h"
#include "CTimeManager.h"
#include "CZero.h"
#include "CRockmanManager.h"

CHPbar::CHPbar()
	:m_hpTexture(nullptr)
	, m_Maxhp(0)
	, m_target(nullptr)
	, m_HPoffset(0)
	, m_prevHp(0)
	, m_redHp(false)
	, m_HPRedOffset(0)
	, m_distance(0.f)
	, m_lifes{}
{
	m_hpTexture = GETINSTANCE(CResourceManager)->LoadTexture(L"HPBAR", L"ui\\zerohpbar.bmp");

	m_lifes[0] = GETINSTANCE(CResourceManager)->LoadTexture(L"life0", L"ui\\lief0.bmp");
	m_lifes[1] = GETINSTANCE(CResourceManager)->LoadTexture(L"life1", L"ui\\lief1.bmp");
	m_lifes[2] = GETINSTANCE(CResourceManager)->LoadTexture(L"life2", L"ui\\lief2.bmp");


	Vector2 pos = GETINSTANCE(CEngine)->GetWndScreenSize();
	pos = pos / 2.f;
	pos.x = 70.f;
	pos.y = 140.f;

	//player

	Vector2 offset = {};

	offset.x = -8.f;
	offset.y = -8.f;

	pos += offset;
	m_distance = 224;
	SetPos(pos);
}

CHPbar::~CHPbar()
{

}


void CHPbar::tick()
{
	//비율 224;
	m_HPoffset = m_distance - (m_distance / (float)m_Maxhp) * (float)m_target->m_hp;
		
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

	m_HPRedOffset = (m_distance / (float)(m_Maxhp)) * (float)(m_prevHp - m_target->m_hp);
}

void CHPbar::render(HDC _dc)
{

	if (nullptr != m_target)
	{

		if (m_target->GetState() == PLAYER_STATE::ENTER || m_target->GetState() == PLAYER_STATE::RETURN || m_target->GetState() == PLAYER_STATE::RETURNREADY || m_target->GetState() == PLAYER_STATE::BLINK)
		{
			return;
		}
		
	}

	if (nullptr == m_target)
	{
		return;
	}

	Vector2 pos = GetPos();

	//충돌체를 그린다.
	HPEN hPen = hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::GREEN);;

	HBRUSH	hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);



	
	//HBRUSH	hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);		
	//red
	SelectObject(_dc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(_dc, RGB(128, 34, 28));

	Rectangle
		(
			_dc,
			pos.x - m_hpTexture->Width() / 2 - 10,
			pos.y - m_hpTexture->Width() / 2 - 100 +  m_HPoffset - m_HPRedOffset,
			pos.x + m_hpTexture->Width() / 2 - 20,
			pos.y + m_hpTexture->Width() / 2 - 100 +  m_HPoffset
		);

	if (m_prevHp > m_target->m_hp)
	{
	}


	SelectObject(_dc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(_dc, RGB(8, 207, 63));
	//128 34 28
	//8, 207, 63
	Rectangle	
	(
		_dc,
		pos.x - m_hpTexture->Width() / 2 - 10,
		pos.y - m_hpTexture->Width() / 2 - 100 + m_HPoffset,			//+124 -> 0 // hpbar = y.224
		pos.x + m_hpTexture->Width() / 2 - 20,
		pos.y + m_hpTexture->Width() / 2 + 100
	);

	//SelectObject(_dc, hOriginPen);
	//SelectObject(_dc, hOriginBrush);

	CRenderHelper::StretchRenderTextrue(_dc, m_hpTexture, GetPos());
	int lieft = GETINSTANCE(CRockmanManager)->m_zeroLife;

	if (lieft < 0)
	{
		lieft = 0;
	}

	lieft %= 3;
	
	pos = GetPos();
	pos.x += 24;
	pos.y += 131;
	CRenderHelper::StretchRenderTextrue(_dc, m_lifes[lieft], pos);
}
