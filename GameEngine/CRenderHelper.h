#pragma once

class CRenderHelper
{
public:
    static void StretchRender(HDC HDCsource, int leftX, int leftY, int sizeX, int sizeY, HDC HDCdest, int posX, int posY, int offsetX, int offsetY, bool isFlip);
    static void ColorSwap(HDC HDCsource, int width, int height, vector<UNIONCOLOR32> sourceColors, vector<UNIONCOLOR32> destColors);

public:
    CRenderHelper();
    ~CRenderHelper();
};

