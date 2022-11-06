#pragma once

class CTexture;

class CRenderHelper
{
public:
    static void StretchRender(HDC HDCsource, int leftX, int leftY, int sizeX, int sizeY, HDC HDCdest, int posX, int posY, int offsetX, int offsetY, bool isFlip);
    static void StretchRender(HDC HDCsource, tAnimFrm& frame, HDC HDCdest, Vector2 pos, bool isFlip);
    static void StretchRender(HDC HDCsource, tAnimFrm& frame, HDC HDCdest, Vector2 pos, bool isFlip, float alpha);
    static void StretchBlit(HDC HDCsource, tAnimFrm& frame, HDC HDCdest, bool isFlip);
    static void StretchRender(HDC dest, CTexture* texture, Vector2 Pos);
    
    static void StretchRenderCollider(HDC _dc, tAnimFrm& frame, Vector2 vPos, bool isflip);
    static void ColorSwap(HDC HDCsource, int width, int height, vector<UNIONCOLOR32> sourceColors, vector<UNIONCOLOR32> destColors);

public:
    CRenderHelper();
    ~CRenderHelper();
};

