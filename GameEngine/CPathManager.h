#pragma once
class CPathManager
{
	SINGLETON(CPathManager)
private:
	WCHAR	m_szContentPath[256];

public:
	void init();
	void render();

public:
	const wchar_t* GetContentPath() { return m_szContentPath; }
};

