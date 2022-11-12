#pragma once

class CTexture;

class CRenderHelper
{
public:
    static void StretchRender(HDC HDCsource, int leftX, int leftY, int sizeX, int sizeY, HDC HDCdest, int posX, int posY, int offsetX, int offsetY, bool isFlipX);
    static void StretchRender(HDC HDCsource, int leftX, int leftY, int sizeX, int sizeY, HDC HDCdest, int posX, int posY, int offsetX, int offsetY, bool isFlipX, bool isFlipY, float renderPer);
    static void StretchRender(HDC HDCsource, tAnimFrm& frame, HDC HDCdest, Vector2 pos, bool isFlipX);
    static void StretchRender(HDC HDCsource, tAnimFrm& frame, HDC HDCdest, Vector2 pos, bool isFlip, float alpha);

    static void StretchRenderReplaceColor(HDC HDCsource, tAnimFrm& frame, HDC HDCdest, Vector2 pos, bool isFlip, float alpha, UINT oldColor, UINT newColor, bool isReverse, float renderPer);

    static void StretchRender(HDC dest, CTexture* texture, Vector2 Pos, bool isFlipY);

    static void StretchBlit(HDC HDCsource, tAnimFrm& frame, HDC HDCdest, bool isFlip);
    
    static void StretchRender(HDC dest, CTexture* texture, Vector2 Pos);
    static void StretchRenderTextrue(HDC dest, CTexture* texture, Vector2 Pos);

    static void StretchRenderOnePer(HDC dest, CTexture* texture, Vector2 Pos);
    static void StretchRenderOnePer(HDC dest, CTexture* texture, tTexAnim texAnim ,Vector2 Pos);

    static void StretchRenderCollider(HDC _dc, tAnimFrm& frame, Vector2 vPos, bool isflip);
    
    static void ColorSwap(HDC HDCsource, int width, int height, vector<UNIONCOLOR32> sourceColors, vector<UNIONCOLOR32> destColors);

    static HBITMAP ReplaceColor(HBITMAP HDCsource, COLORREF cOldColor, COLORREF cNewColor, HDC HDCdest, bool isReverse);

public:
    CRenderHelper();
    ~CRenderHelper();
};

