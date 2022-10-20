#pragma once

class CTexture;

#define WINDOWX_PER_X 3
#define WINDOWX_PER_Y 3

#define WINDOW_ORIGINAL_X 320
#define WINDOW_ORIGINAL_Y 240

class CEngine
{
	SINGLETON(CEngine);

private:
	HWND	m_hMainWnd;
	HDC		m_hMainDC;
	POINT	m_ptWndScreenSize;
	HPEN	m_arrpen[(UINT)PEN_TYPE::END];

	/*HDC		m_hBufferDC;
	HBITMAP m_hBufferBit;*/

	CTexture* m_pTexBuffer;
	CTexture* m_pRealBuffer;

public:
	HWND	GetMainWnd() { return m_hMainWnd; }
	HDC		GetMainDC() { return m_hMainDC; }
	HPEN	GetPen(PEN_TYPE type) { return m_arrpen[(UINT)type]; }
	POINT	GetWndScreenSize() { return m_ptWndScreenSize; }



	void Init(HWND _hwnd, UINT _iWidth, UINT _iheight);
	void progress();
	void tick(); // 갱신 update
	void render(); // 그리기

public:
	void WindowReSize(UINT _iWidth, UINT _iHeight);


private:
	void CreatePenBrush();



};

