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
    // Bitmap �ε�
    m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);

    // Bitmap �� ���� ��ų DC ����
    m_hDC = CreateCompatibleDC(GETINSTANCE(CEngine)->GetMainDC());
    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBit);

    return S_OK;
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
    // ������ ��Ʈ���� ������� ������ �ػ󵵷� ������Ŵ    
    m_hBit = CreateCompatibleBitmap(GETINSTANCE(CEngine)->GetMainDC(), _iWidth, _iHeight);

    // ������Ų ��Ʈ���� �������� �ϴ� DC �� ������
    m_hDC = CreateCompatibleDC(GETINSTANCE(CEngine)->GetMainDC());

    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBit);    

    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
}

void CTexture::Create(UINT _iWidth, UINT _iHeight, UINT _fillColor)
{
    // ������ ��Ʈ���� ������� ������ �ػ󵵷� ������Ŵ    
    m_hBit = CreateCompatibleBitmap(GETINSTANCE(CEngine)->GetMainDC(), _iWidth, _iHeight);

    // ������Ų ��Ʈ���� �������� �ϴ� DC �� ������
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
    // ���ο��Ʈ�� DC�� ����
    HBITMAP hNewBit = CreateCompatibleBitmap(GETINSTANCE(CEngine)->GetMainDC(), _iWidth, _iHeight);   
    HDC hNewDC = CreateCompatibleDC(GETINSTANCE(CEngine)->GetMainDC());

    HBITMAP hPrevBit = (HBITMAP)SelectObject(hNewDC, hNewBit);
    DeleteObject(hPrevBit);

    BitBlt(hNewDC, 0, 0, m_tBitmapInfo.bmWidth, m_tBitmapInfo.bmHeight, m_hDC, 0, 0, SRCCOPY);

    //������Ʈ��DC����
    DeleteObject(m_hBit);
    DeleteDC(m_hDC);

    //����
    m_hBit = hNewBit;
    m_hDC = hNewDC;
    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
}