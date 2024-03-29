#pragma once


class CTexture;
class CSound;
class CResourceManager
{
	SINGLETON(CResourceManager);
\
private:
	map<wstring, CTexture*>	m_mapTex;
	map<wstring, CSound*>	m_mapSounds;

public:
	CTexture* FindTexture(const wstring& _strKey);
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);

	CTexture* CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight);
	CTexture* CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight, UINT _fillColor);


	CSound* FindSound(const wstring& _strKey);
	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
};

