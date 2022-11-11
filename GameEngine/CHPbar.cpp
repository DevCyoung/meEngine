#include "pch.h"
#include "CHPbar.h"
#include "CRenderHelper.h"
#include "CResourceManager.h"
#include "CEngine.h"
#include "CTexture.h"

CHPbar::CHPbar()
	:m_hpTexture(nullptr)
{
	m_hpTexture = GETINSTANCE(CResourceManager)->LoadTexture(L"HPBAR", L"ui\\zerohpbar.bmp");
	Vector2 pos = GETINSTANCE(CEngine)->GetWndScreenSize();
	pos = pos / 2.f;
	pos.x = 70.f;
	pos.y = 140.f;
	SetPos(pos);
}

CHPbar::~CHPbar()
{

}


void CHPbar::tick()
{

}

void CHPbar::render(HDC _dc)
{
	Vector2 pos = GetPos();

	//충돌체를 그린다.
	HPEN hPen = hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::GREEN);;

	HBRUSH	hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);



	
	//HBRUSH	hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);	

	SelectObject(_dc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(_dc, RGB(8, 207, 63));

	//128 34 28
	//8, 207, 63
	Rectangle
	(
		_dc,
		pos.x - m_hpTexture->Width() / 2 - 10,
		pos.y - m_hpTexture->Width() / 2 - 100,			//+124 -> 0 // hpbar = y.224
		pos.x + m_hpTexture->Width() / 2 - 20,
		pos.y + m_hpTexture->Width() / 2 + 100
	);

	//SelectObject(_dc, hOriginPen);
	//SelectObject(_dc, hOriginBrush);

	CRenderHelper::StretchRenderTextrue(_dc, m_hpTexture, GetPos());	
}
