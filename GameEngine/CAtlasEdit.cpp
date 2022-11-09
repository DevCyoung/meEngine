#include "pch.h"
#include "CAtlasEdit.h"
#include "CKeyManager.h"
#include "CPathManager.h"
#include "CMap.h"
#include "CResourceManager.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CTexture.h"
#include "CMapManager.h"

CAtlasEdit::CAtlasEdit()
	:m_backGround(nullptr)
{
}

CAtlasEdit::CAtlasEdit(const CAtlasEdit& _other)
	:m_backGround(nullptr)
{

}

CAtlasEdit::~CAtlasEdit()
{
}


void CAtlasEdit::tick()
{
}

void CAtlasEdit::render(HDC _dc)
{	
	if (nullptr == m_backGround)
		return;

	DrawRect(Vector2(50.f, 50.f), PEN_TYPE::ORANGE, m_backGround->m_cameraPos, _dc);
	DrawRect(Vector2(50.f, 50.f), PEN_TYPE::YELLOW, m_backGround->m_playerPos, _dc);
}

void CAtlasEdit::Update()
{
	if (IS_INPUT_TAB(KEY::O))
	{
		// open a file name
		//�̹� ������� �����쿡�� �������ִ� �ſ����� ��޹���� ������
		//�ش�â�� �׳� Path ���ڿ��� �����һ���

		OPENFILENAME ofn = {};

		wstring strTileFolderPath = GETINSTANCE(CPathManager)->GetMapPath();

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));														//
		ofn.lStructSize = sizeof(ofn);														//
		ofn.hwndOwner = NULL;																//
		ofn.lpstrFile = szFilePath;															//
		ofn.lpstrFile[0] = '\0';															//
		ofn.nMaxFile = 256;																	//
		ofn.lpstrFilter = L"ATLASMAP\0*.bmp";												//�ǽ��� �ִϸ��̼�
		ofn.nFilterIndex = 1;																//�⺻��������
		ofn.lpstrFileTitle = NULL;															//
		ofn.nMaxFileTitle = 0;																//
		ofn.lpstrInitialDir = strTileFolderPath.c_str();									//�Ź� �ʿ���°�θ����� ��ȿ�����̱⶧���� �װ���������
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;									//

		//���̾�α׿��� ID�������� ����
		if (false == GetOpenFileName(&ofn))
			return;
		if (nullptr != m_backGround)
		{
			m_backGround->Destroy();
		}
		//ofn.name
		wstring temp = szFilePath;
		GETINSTANCE(CPathManager)->FulloRelativePath(temp);

		m_backGround = new CMap();
		CTexture* tex = GETINSTANCE(CResourceManager)->LoadTexture(temp.c_str(), temp.c_str());
		m_backGround->SetAtlas(tex);
		CGameObject::Instantiate(m_backGround, Vector2(0.f, 0.f), LAYER::BACKGROUND);
	}

	// Start Camera Point
	if (IS_INPUT_TAB(KEY::P))
	{
		Vector2 cmaPos = GETINSTANCE(CCamera)->GetLook();
		m_backGround->m_cameraPos.push_back(cmaPos);
	}

	// Start Character Point
	if (IS_INPUT_TAB(KEY::I))
	{
		Vector2 playerPos = GETINSTANCE(CCamera)->GetRealMousePos();
		m_backGround->m_playerPos.push_back(playerPos);
	}

	// Camera Character reset
	if (IS_INPUT_TAB(KEY::R))
	{
		m_backGround->m_cameraPos.clear();
		m_backGround->m_playerPos.clear();
	}

}

void CAtlasEdit::DrawRect(Vector2 scale, PEN_TYPE pen, vector<Vector2>& vec, HDC _dc)
{
	//�浹ü�� �׸���.
	HPEN hPen = GETINSTANCE(CEngine)->GetPen(pen);

	HBRUSH	hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HPEN	hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH	hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	for (size_t i = 0; i < vec.size(); i++)
	{
		Vector2 vPos = GETINSTANCE(CCamera)->GetRenderPos(vec[i]);
		Rectangle
		(
			_dc
			, (int)(vPos.x - scale.x / 2)
			, (int)(vPos.y - scale.y / 2)
			, (int)(vPos.x + scale.x / 2)
			, (int)(vPos.y + scale.y / 2)
		);
	}


	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);
}

//�ʸŴ������� ������� ������ ������

//��׶��� ��Ʋ���� ���������
//�ش���� �÷��̾���� ��ġ����, ī�޶���� ��ġ������ �����Ѵ�.
void CAtlasEdit::Save(FILE* pFile)
{
	assert(m_backGround);
	
	//size_t strCount = m_backGround->m_mapAtlas->GetRelativePath().length();
//	//fwrite(&strCount, sizeof(size_t), 1, pFile);
//	//fwrite(m_backGround->m_mapAtlas->GetRelativePath().c_str(), sizeof(wchar_t), strCount, pFile);

	wstring atlasPath	= m_backGround->GetAtlas()->GetRelativePath();
	UINT	stringLen	= atlasPath.length();

	Vector2 pos = m_backGround->GetPos();
	fwrite(&stringLen, sizeof(UINT), 1, pFile);
	fwrite(atlasPath.c_str(), sizeof(wchar_t), stringLen, pFile);
	fwrite(&pos, sizeof(Vector2), 1, pFile);

	UINT	m_camCount = m_backGround->m_cameraPos.size();
	fwrite(&m_camCount, sizeof(UINT), 1, pFile);
	for (UINT i = 0; i < m_camCount; i++)
	{
		fwrite(&m_backGround->m_cameraPos[i], sizeof(Vector2), 1, pFile);
	}

	UINT	m_playerCount = m_backGround->m_playerPos.size();
	fwrite(&m_playerCount, sizeof(UINT), 1, pFile);
	for (UINT i = 0; i < m_playerCount; i++)
	{
		fwrite(&m_backGround->m_playerPos[i], sizeof(Vector2), 1, pFile);
	}

	
}

void CAtlasEdit::Load(FILE* pFile)
{	
	wchar_t buffer[256] = {};

	UINT stringLen = 1;

	CMap* map = new CMap();
	Vector2 pos;

	fread(&stringLen, sizeof(UINT), 1, pFile);
	fread(buffer, sizeof(wchar_t), stringLen, pFile);
	fread(&pos, sizeof(Vector2), 1, pFile);
	wstring atlasRelativePath	= buffer;

	map->SetAtlas(GETINSTANCE(CResourceManager)->LoadTexture(atlasRelativePath, atlasRelativePath));
	map->SetPos(pos);
	UINT	m_camCount;
	fread(&m_camCount, sizeof(UINT), 1, pFile);
	for (UINT i = 0; i < m_camCount; i++)
	{
		Vector2 camPos;
		fread(&camPos, sizeof(Vector2), 1, pFile);
		map->m_cameraPos.push_back(camPos);
	}

	UINT	m_playerCount = map->m_playerPos.size();
	fread(&m_playerCount, sizeof(UINT), 1, pFile);
	for (UINT i = 0; i < m_playerCount; i++)
	{
		Vector2 playerPos;
		fread(&playerPos, sizeof(Vector2), 1, pFile);
		map->m_playerPos.push_back(playerPos);
	}
	GETINSTANCE(CMapManager)->AddMap(map);
	GETINSTANCE(CMapManager)->MapCameraSet(0);
	m_backGround = map;
}
