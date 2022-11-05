#pragma once

class CMap;

class CMapManager
{
	SINGLETON(CMapManager);

	vector<CMap*>	m_vecMap;
	CMap*			m_curMap;

public:
	void AddMap(CMap* map);

	//¿¹ºñ¿ë
public:
	void MapCameraSet(UINT camIdx);


public:
	void Load();
	void Save();
};

