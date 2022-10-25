#pragma once


class CMapManager
{
	SINGLETON(CMapManager);




public:
	void Load(const string& _path);
	void Save(const string& _path);
};

