#include "pch.h"
#include "CTexture.h"
#include "CEngine.h"

CTexture::CTexture()
    : m_hBit(nullptr)
    , m_hDC(nullptr)
    , m_tBitmapInfo{}
{
}

CTexture::~CTexture()
{
    DeleteObject(m_hBit);
    DeleteDC(m_hDC);
}

int CTexture::Load(const wstring& _strFilePath)
{
    // Bitmap 로딩
    m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);

    // Bitmap 과 연결 시킬 DC 생성
    m_hDC = CreateCompatibleDC(GETINSTANCE(CEngine)->GetMainDC());
    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBit);

    return S_OK;
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
    // 별도의 비트맵을 윈도우와 동일한 해상도로 생성시킴    
    m_hBit = CreateCompatibleBitmap(GETINSTANCE(CEngine)->GetMainDC(), _iWidth, _iHeight);

    // 생성시킨 비트맵을 목적지로 하는 DC 를 생성함
    m_hDC = CreateCompatibleDC(GETINSTANCE(CEngine)->GetMainDC());

    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBit);    

    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
}

void CTexture::Create(UINT _iWidth, UINT _iHeight, UINT _fillColor)
{
    // 별도의 비트맵을 윈도우와 동일한 해상도로 생성시킴    
    m_hBit = CreateCompatibleBitmap(GETINSTANCE(CEngine)->GetMainDC(), _iWidth, _iHeight);

    // 생성시킨 비트맵을 목적지로 하는 DC 를 생성함
    m_hDC = CreateCompatibleDC(GETINSTANCE(CEngine)->GetMainDC());

    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBit);

    SelectObject(m_hDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(m_hDC, _fillColor);
    Rectangle(m_hDC, 0, 0, _iWidth, _iHeight);

    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
}


void CTexture::Resize(UINT _iWidth, UINT _iHeight)
{
    // 새로운비트맵 DC를 생성
    HBITMAP hNewBit = CreateCompatibleBitmap(GETINSTANCE(CEngine)->GetMainDC(), _iWidth, _iHeight);   
    HDC hNewDC = CreateCompatibleDC(GETINSTANCE(CEngine)->GetMainDC());

    HBITMAP hPrevBit = (HBITMAP)SelectObject(hNewDC, hNewBit);
    DeleteObject(hPrevBit);

    BitBlt(hNewDC, 0, 0, m_tBitmapInfo.bmWidth, m_tBitmapInfo.bmHeight, m_hDC, 0, 0, SRCCOPY);

    //기존비트맵DC삭제
    DeleteObject(m_hBit);
    DeleteDC(m_hDC);

    //갱신
    m_hBit = hNewBit;
    m_hDC = hNewDC;
    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
}