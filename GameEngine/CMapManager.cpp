#include "pch.h"
#include "CMapManager.h"
#include "CLineColManager.h"
#include "CMap.h"
#include "CGameObject.h"
#include "CCamera.h"


CMapManager::CMapManager()
	:	m_curMap(nullptr)
{

}

CMapManager::~CMapManager()
{

}


void CMapManager::AddMap(CMap* map)
{
	if (nullptr == m_curMap)
		m_curMap = map;
	CGameObject::Instantiate(map, map->GetPos(), LAYER::BACKGROUND);
	m_vecMap.push_back(map);
}

void CMapManager::MapCameraSet(UINT camIdx)
{
	Vector2 pos = m_curMap->m_cameraPos[camIdx];
	GETINSTANCE(CCamera)->SetLook(pos);
}

void CMapManager::Load()
{

}

void CMapManager::Save()
{

}
