#pragma once
class CPathManager
{
	SINGLETON(CPathManager)
private:
	WCHAR	m_szContentPath[256];
	WCHAR	m_szMapPath[256];
	WCHAR	m_szAnimPath[256];
	WCHAR	m_szSoundPath[256];
	WCHAR	m_szEffectath[256];

public:
	void init();
	void render();

public:
	const wchar_t*	GetContentPath() { return m_szContentPath; }
	const wchar_t*	GetMapPath() { return m_szMapPath; }
	void			FulloRelativePath(wstring& fullpath);
};

