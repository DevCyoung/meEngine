#pragma once

class CMap;

class CMapManager
{
	SINGLETON(CMapManager);

	
	CMap*			m_curMap;
	UINT			m_curPos;

public:
	void AddMap(CMap* map);
	

	//¿¹ºñ¿ë
public:
	void MapCameraSet(UINT camIdx);
	Vector2 GetPlayerPos(UINT camIdx);

public:
	void Load();
	void Save();
};

