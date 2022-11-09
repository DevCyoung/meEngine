#include "pch.h"
#include "CRenderHelper.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CTexture.h"

CRenderHelper::CRenderHelper()
{

}

CRenderHelper::~CRenderHelper()
{

}

void CRenderHelper::StretchRender(HDC HDCsource, int leftX, int leftY, int sizeX, int sizeY, HDC HDCdest, int posX, int posY ,int offsetX, int offsetY, bool isFlip)
{	

	HDC		HDCbuffer = CreateCompatibleDC(HDCdest);
	HBITMAP HBITMAPbuffer = CreateCompatibleBitmap(HDCdest, sizeX * WINDOWX_PER_X, sizeY * WINDOWX_PER_Y);

	HBITMAP hPrebit = (HBITMAP)SelectObject(HDCbuffer, HBITMAPbuffer);
	DeleteObject(hPrebit);

	


	if (isFlip)
	{
		StretchBlt
		(
			  HDCbuffer
			, sizeX * WINDOWX_PER_X - 1
			, 0
			, (int)(-sizeX  * WINDOWX_PER_X)
			, (int)( sizeY  * WINDOWX_PER_Y)
			, HDCsource
			, (int)(leftX)
			, (int)(leftY)
			, (int)(sizeX)
			, (int)(sizeY)
			, SRCCOPY
		);

		TransparentBlt
		(
			  HDCdest
			, int(posX - (int)(sizeX * WINDOWX_PER_X + offsetX * WINDOWX_PER_X) / 2)
			, int(posY - (int)(sizeY * WINDOWX_PER_Y - offsetY * WINDOWX_PER_Y) / 2)
			, int(sizeX * WINDOWX_PER_X)
			, int(sizeY * WINDOWX_PER_Y)
			, HDCbuffer
			, 0
			, 0
			, int(sizeX * WINDOWX_PER_X)
			, int(sizeY * WINDOWX_PER_Y)
			, RGB(255, 0, 255)
		);
	}
	else
	{
		StretchBlt
		(
			  HDCbuffer
			, 0
			, 0
			, sizeX * WINDOWX_PER_X
			, sizeY * WINDOWX_PER_Y
			, HDCsource
			, leftX
			, leftY
			, sizeX
			, sizeY
			, SRCCOPY
		);

		TransparentBlt
		(
			  HDCdest
			, int(posX - (int)(sizeX * WINDOWX_PER_X - offsetX * WINDOWX_PER_X) / 2)
			, int(posY - (int)(sizeY * WINDOWX_PER_Y - offsetY * WINDOWX_PER_Y) / 2)
			, int(sizeX * WINDOWX_PER_X)
			, int(sizeY * WINDOWX_PER_Y)
			, HDCbuffer
			, 0
			, 0
			, int(sizeX * WINDOWX_PER_X)
			, int(sizeY * WINDOWX_PER_Y)
			, RGB(255, 0, 255)
		);
	}

	DeleteObject(HBITMAPbuffer);
	DeleteDC(HDCbuffer);
}

void CRenderHelper::StretchRender(HDC HDCsource, int leftX, int leftY, int sizeX, int sizeY, HDC HDCdest, int posX, int posY, int offsetX, int offsetY, bool isFlipX, bool isFlipY)
{
	HDC		HDCbuffer = CreateCompatibleDC(HDCdest);
	HBITMAP HBITMAPbuffer = CreateCompatibleBitmap(HDCdest, sizeX * WINDOWX_PER_X, sizeY * WINDOWX_PER_Y);

	HBITMAP hPrebit = (HBITMAP)SelectObject(HDCbuffer, HBITMAPbuffer);
	DeleteObject(hPrebit);

	Vector2 vStretchLeft = {};
	Vector2 vStretchSize = {};

	Vector2 vTransLeft = {};
	
			
	if (isFlipX)
	{
		vStretchLeft.x = sizeX * WINDOWX_PER_X - 1;		
		vStretchSize.x = -sizeX * WINDOWX_PER_X;

		vTransLeft.x = posX - (int)(sizeX * WINDOWX_PER_X + offsetX * WINDOWX_PER_X) / 2;
		
	}
	else
	{
		vStretchLeft.x = 0.f;
		vStretchSize.x = sizeX * WINDOWX_PER_X;

		vTransLeft.x = posX - (int)(sizeX * WINDOWX_PER_X - offsetX * WINDOWX_PER_X) / 2;
		
	}
	//isFlipY = true;
	if (isFlipY)
	{
		vStretchLeft.y =  sizeY * WINDOWX_PER_Y - 1;
		vStretchSize.y = -sizeY * WINDOWX_PER_Y;

		vTransLeft.y = posY - (int)(sizeY * WINDOWX_PER_Y - offsetY * WINDOWX_PER_Y) / 2;
	}
	else
	{
		vStretchLeft.y = 0.f;
		vStretchSize.y = sizeY * WINDOWX_PER_Y;

		vTransLeft.y = posY - (int)(sizeY * WINDOWX_PER_Y - offsetY * WINDOWX_PER_Y) / 2;
	}

	StretchBlt
	(
		HDCbuffer
		, vStretchLeft.x
		, vStretchLeft.y
		, (int)vStretchSize.x
		, (int)vStretchSize.y
		, HDCsource
		, (int)(leftX)
		, (int)(leftY)
		, (int)(sizeX)
		, (int)(sizeY)
		, SRCCOPY
	);

	TransparentBlt
	(
		HDCdest
		, (int)vTransLeft.x
		, (int)vTransLeft.y
		, int(sizeX * WINDOWX_PER_X)
		, int(sizeY * WINDOWX_PER_Y)
		, HDCbuffer
		, 0
		, 0
		, int(sizeX * WINDOWX_PER_X)
		, int(sizeY * WINDOWX_PER_Y)
		, RGB(255, 0, 255)
	);


	DeleteObject(HBITMAPbuffer);
	DeleteDC(HDCbuffer);
}

void CRenderHelper::StretchRender(HDC HDCsource, tAnimFrm& frame, HDC HDCdest, Vector2 realPos, bool isFlip)
{
	//Vector2 pos = GETINSTANCE(CCamera)->GetRenderPos(realPos);
	CRenderHelper::StretchRender(HDCsource, frame.vLeftTop.x, frame.vLeftTop.y, frame.vSize.x, frame.vSize.y, HDCdest, realPos.x, realPos.y, frame.vOffset.x, frame.vOffset.y, isFlip);
}

void CRenderHelper::StretchRender(HDC HDCsource, tAnimFrm& frame, HDC HDCdest, Vector2 pos, bool isFlip, float alpha)
{

	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = 0;
	tBlend.BlendFlags = 1;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255.f * alpha);
	

	HDC		HDCbuffer		= CreateCompatibleDC(HDCdest);
	HBITMAP HBITMAPbuffer	= CreateCompatibleBitmap(HDCdest, frame.vSize.x * WINDOWX_PER_X, frame.vSize.y * WINDOWX_PER_Y);
	HBITMAP hPrebit = (HBITMAP)SelectObject(HDCbuffer, HBITMAPbuffer);

	DeleteObject(hPrebit);


	StretchBlit(HDCsource, frame, HDCbuffer, isFlip);

	AlphaBlend
	(
		HDCdest,
		int(pos.x - (int)(frame.vSize.x * WINDOWX_PER_X - frame.vOffset.x * WINDOWX_PER_X) / 2),
		int(pos.y - (int)(frame.vSize.y * WINDOWX_PER_Y - frame.vOffset.y * WINDOWX_PER_Y) / 2),
		int(frame.vSize.x * WINDOWX_PER_X),
		int(frame.vSize.y * WINDOWX_PER_Y),
		HDCbuffer,
		0,
		0,
		int(frame.vSize.x * WINDOWX_PER_X),
		int(frame.vSize.y * WINDOWX_PER_Y),
		tBlend
	);

	DeleteObject(HBITMAPbuffer);
	DeleteDC(HDCbuffer);
}



void CRenderHelper::StretchBlit(HDC HDCsource, tAnimFrm& frame, HDC HDCdest, bool isFlip)
{

	if (isFlip)
	{
		StretchBlt
		(
			  HDCdest
			, frame.vSize.x * WINDOWX_PER_X - 1
			, 0
			, (int)(-frame.vSize.x * WINDOWX_PER_X)
			, (int)( frame.vSize.y * WINDOWX_PER_Y)
			, HDCsource
			, (int)(frame.vLeftTop.x)
			, (int)(frame.vLeftTop.y)
			, (int)(frame.vSize.x)
			, (int)(frame.vSize.y)
			, SRCCOPY
		);


	}
	else
	{
		StretchBlt
		(
			  HDCdest
			, 0
			, 0
			, frame.vSize.x * WINDOWX_PER_X
			, frame.vSize.y * WINDOWX_PER_Y
			, HDCsource
			, frame.vLeftTop.x
			, frame.vLeftTop.y
			, frame.vSize.x
			, frame.vSize.y
			, SRCCOPY
		);
	}
}

void CRenderHelper::StretchRender(HDC dest, CTexture* texture, Vector2 Pos)
{
	StretchBlt
	(
		dest
		, (int)Pos.x 
		, (int)Pos.y 
		, texture->Width()  * WINDOWX_PER_X
		, texture->Height() * WINDOWX_PER_Y
		, texture->GetDC()
		, 0
		, 0
		, texture->Width()
		, texture->Height()
		, SRCCOPY
	);

}

void CRenderHelper::StretchRenderOnePer(HDC dest, CTexture* texture, Vector2 pos)
{
	TransparentBlt
	(
		dest,
		pos.x - texture->Width() / 2 ,
		pos.y - texture->Height() / 2,
		texture->Width(),
		texture->Height(),
		texture->GetDC(),
		0,
		0,
		texture->Width(),
		texture->Height(),
		RGB(255,0,255)
	);
}

void CRenderHelper::StretchRenderOnePer(HDC dest, CTexture* texture, tTexAnim texAnim, Vector2 pos)
{


	TransparentBlt
	(
		dest,
		pos.x - texture->Width()  / 2 + texAnim.vLeftTop.x ,
		pos.y - texture->Height() / 2 + texAnim.vLeftTop.y,
		texAnim.vSize.x,
		texAnim.vSize.y,
		texture->GetDC(),
		texAnim.vLeftTop.x,
		texAnim.vLeftTop.y,
		texAnim.vSize.x,
		texAnim.vSize.y,
		RGB(255, 0, 255)
	);
}

void CRenderHelper::StretchRender(HDC dest, CTexture* texture, Vector2 pos, bool isFlipY)
{
	
	if (isFlipY == false)
	{
		StretchBlt
		(
			dest
			, (int)pos.x
			, (int)pos.y
			, texture->Width() * WINDOWX_PER_X
			, texture->Height() * WINDOWX_PER_Y
			, texture->GetDC()
			, 0
			, 0
			, texture->Width()
			, texture->Height()
			, SRCCOPY
		);
	}
	else
	{
		StretchBlt
		(
			  dest
			, (int)pos.x
			, (int)pos.y
			, texture->Width() * WINDOWX_PER_X
			, -1 * texture->Height() * WINDOWX_PER_Y
			, texture->GetDC()
			, 0
			, 0
			, texture->Width() 
			, texture->Height() 
			, SRCCOPY
		);
	}

}
void CRenderHelper::StretchRenderCollider(HDC _dc, tAnimFrm& frame, Vector2 vPos, bool isflip)
{
	HPEN hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::BLUE);
	HBRUSH	hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN	hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH	hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	tColInfo colInfo = frame.colInfo;

	if (colInfo.vScale.x > 0.000001f || (colInfo.vScale.y > 0.000001f))
	{
		Vector2 vLPos;

		vLPos.x = vPos.x - ((colInfo.vOffset.x * WINDOWX_PER_X - colInfo.vScale.x * WINDOWX_PER_X)) / 2;
		vLPos.y = vPos.y - ((colInfo.vOffset.y * WINDOWX_PER_Y - colInfo.vScale.y * WINDOWX_PER_Y)) / 2;

		if (isflip == false)
		{
			vLPos.x = vPos.x - (colInfo.vScale.x  /  2  + colInfo.vOffset.x ) * WINDOWX_PER_X;
			vLPos.y = vPos.y - (colInfo.vScale.y  / 2  + colInfo.vOffset.y ) * WINDOWX_PER_Y;
		}
		else
		{
			vLPos.x = vPos.x + (colInfo.vOffset.x - colInfo.vScale.x / 2)  * WINDOWX_PER_X;
			vLPos.y = vPos.y - (colInfo.vOffset.y + colInfo.vScale.y / 2 ) * WINDOWX_PER_Y;
		}

		Rectangle(
			_dc
			, vLPos.x
			, vLPos.y
			, vLPos.x + colInfo.vScale.x * WINDOWX_PER_X
			, vLPos.y + colInfo.vScale.y * WINDOWX_PER_Y
		);

	}

	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);
}

void CRenderHelper::ColorSwap(HDC HDCsource, int width, int height, vector<UNIONCOLOR32> sourceColors, vector<UNIONCOLOR32> destColors)
{
	if (sourceColors.size() != destColors.size())
		return;

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{

			COLORREF color = GetPixel(HDCsource, j, i);
			
			for (size_t k = 0; k < sourceColors.size(); k++)
			{
				if (color == sourceColors[k].COLOR)
				{
					SetPixel(HDCsource, j, i, destColors[k].COLOR);
					break;
				}
			}

		}
	}

	vector<UNIONCOLOR32> vec;
	UNIONCOLOR32 color = {};
	color.R = 255;
	//color.B = 255;
	color.A = 255;
	vec.push_back(color);
	unsigned long cc = (unsigned long)color.COLOR;

}