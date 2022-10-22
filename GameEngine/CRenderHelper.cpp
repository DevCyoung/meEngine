#include "pch.h"
#include "CRenderHelper.h"
#include "CCamera.h"
#include "CEngine.h"

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