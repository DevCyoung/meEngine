#include "pch.h"
#include "CTile.h"
#include "CCamera.h"
#include "CTexture.h"
#include "CResourceManager.h"

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
	assert(m_pAtlas);
	int xSize = m_pAtlas->Width() / TILE_SIZE;
	int ySIze = m_pAtlas->Height() / TILE_SIZE;
	int iImgMaxCount = xSize * ySIze;
	++m_iImgIdx;
	m_iImgIdx %= iImgMaxCount;	
}

void CTile::Save(FILE* _pFile)
{
	//��ġ����
	Vector2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vector2), 1, _pFile);
	//��Ʋ�� �̹��� ���� �ּҰ����־����� 1 �ƴϸ� 0
	bool bAtlas = m_pAtlas;
	fwrite(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		//Ű�� ����
		wstring strKey = m_pAtlas->GetKey();
		SaveWString(strKey, _pFile);

		//�����
		wstring strRelativePath = m_pAtlas->GetRelativePath();
		SaveWString(strRelativePath, _pFile);	
	}

	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
	//�̹��� �ε������� ��������� �׸������ߴ���
}

void CTile::Load(FILE* _pFile)
{
	Vector2 vPos;
	fread(&vPos, sizeof(Vector2), 1, _pFile);
	SetPos(vPos);

	bool bAtlas = m_pAtlas;
	fread(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		//Ű�� ����
		wstring strKey;
		wstring strRelativePath;		
		LoadWString(strKey, _pFile);
		LoadWString(strRelativePath, _pFile);
		this->m_pAtlas = GETINSTANCE(CResourceManager)->LoadTexture(strKey, strRelativePath);
	}
	
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}