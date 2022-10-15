#include "pch.h"
#include "CTile.h"
#include "CCamera.h"
#include "CTexture.h"

CTile::CTile()
	:m_pAtlas(nullptr)
	, m_iImgIdx(-1)
{
}

CTile::~CTile()
{
}


void CTile::SetImgIdx(int _imgidx)
{
	assert(m_pAtlas);

	int xSize = m_pAtlas->Width() / TILE_SIZE;
	int ySIze = m_pAtlas->Height() / TILE_SIZE;
	int iImgMaxCount = xSize * ySIze;
	assert(_imgidx < iImgMaxCount);
	m_iImgIdx = _imgidx;
}


void CTile::tick()
{
	CGameObject::tick();
}

void CTile::render(HDC _dc)
{

	if (-1 == m_iImgIdx || nullptr == m_pAtlas)
		return;

	
	Vector2 vPos = GETINSTANCE(CCamera)->GetRenderPos(GetPos());

	/*Rectangle(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + TILE_SIZE)
		, (int)(vPos.y + TILE_SIZE));*/


	int iMaxCol = m_pAtlas->Width() / TILE_SIZE;

	int y = m_iImgIdx / iMaxCol;
	int x = m_iImgIdx % iMaxCol;

	BitBlt
	(
		_dc,
		vPos.x,
		vPos.y,
		TILE_SIZE,
		TILE_SIZE,
		m_pAtlas->GetDC(),
		x * TILE_SIZE,
		y * TILE_SIZE,
		SRCCOPY
	);

	//CGameObject::render(_dc);
}

void CTile::AddImgIdx()
{
}

void CTile::Save(FILE* _pFile)
{
}

void CTile::Load(FILE* _pFile)
{
}

