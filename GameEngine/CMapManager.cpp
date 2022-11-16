#include "pch.h"
#include "CMapManager.h"
#include "CLineColManager.h"
#include "CMap.h"
#include "CGameObject.h"
#include "CCamera.h"


CMapManager::CMapManager()
	:	m_curMap(nullptr)
	,	m_curPos(0)
{

}

CMapManager::~CMapManager()
{

}


void CMapManager::AddMap(CMap* map)
{
	m_curMap = map;
	CGameObject::Instantiate(map, map->GetPos(), LAYER::BACKGROUND);	
}

void CMapManager::MapCameraSet(UINT camIdx)
{
	assert(camIdx < m_curMap->m_cameraPos.size());	
	Vector2 pos = m_curMap->m_cameraPos[camIdx];
	GETINSTANCE(CCamera)->SetLook(pos);
}

Vector2 CMapManager::GetPlayerPos(UINT playIdx)
{
	assert(playIdx < m_curMap->m_playerPos.size());

	Vector2 pos = m_curMap->m_playerPos[playIdx];
	return pos;
}

Vector2 CMapManager::GetCameraPos(UINT camIdx)
{
	assert(camIdx < m_curMap->m_cameraPos.size());

	Vector2 pos = m_curMap->m_cameraPos[camIdx];
	return pos;
}

void CMapManager::Load()
{

}

void CMapManager::Save()
{

}
