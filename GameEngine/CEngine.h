#pragma once

class CEngine
{
	SINGLETON(CEngine);

private:
	HWND	m_hMainWnd;
	HDC		m_hMainDC;
	HDC		m_hBufferDC;
	HBITMAP m_hBufferBit;

	POINT	m_ptWndScreenSize;
	HPEN	m_arrpen[(UINT)PEN_TYPE::END];

public:
	HWND	GetMainWnd() { return m_hMainWnd; }
	HDC		GetMainDC() { return m_hMainDC; }
	HPEN	GetPen(PEN_TYPE type) { return m_arrpen[(UINT)type]; }
	Vector2	GetWndScreenSize() { return m_ptWndScreenSize; }

	void Init(HWND _hwnd, UINT _iWidth, UINT _iheight);
	void progress();
	void tick(); // 갱신 update
	void render(); // 그리기

private:
	void CreatePenBrush();



};

