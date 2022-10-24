#include "pch.h"
#include "CEditorLevel.h"
#include "CResourceManager.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CTexture.h"

#include "CTile.h"
#include "resource.h"
#include "CLevelManager.h"
#include "CKeyManager.h"
#include "CPathManager.h"
#include "CUI.h"
#include "CButton.h"

//���� ���ϰ� ����ϱ����� UI�� ������
//UI�� �ᱹ ������Ʈ�� ��ӹ޴´�.
void CEditorLevel::SaveTIle()
{
	// open a file name
	//�̹� ������� �����쿡�� �������ִ� �ſ����� ��޹���� ������
	//�ش�â�� �׳� Path ���ڿ��� �����һ���
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = GETINSTANCE(CPathManager)->GetContentPath();
	strTileFolderPath += L"tile\\";


	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));														//
	ofn.lStructSize = sizeof(ofn);														//
	ofn.hwndOwner = NULL;																//
	ofn.lpstrFile = szFilePath;															//
	ofn.lpstrFile[0] = '\0';															//
	ofn.nMaxFile = 256;																	//
	ofn.lpstrFilter = L"Tile\0*.tile\0Animation\0*.anim\0ALL\0*.*";						//�ǽ��� �ִϸ��̼�
	ofn.nFilterIndex = 1;																//�⺻��������
	ofn.lpstrFileTitle = NULL;															//
	ofn.nMaxFileTitle = 0;																//
	ofn.lpstrInitialDir = strTileFolderPath.c_str();									//�Ź� �ʿ���°�θ����� ��ȿ�����̱⶧���� �װ���������
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;									//

	//���̾�α׿���
	if (false == GetSaveFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");
	assert(pFile);



	// Ÿ�� ���� ���� ��������
	UINT iTileXCount = GetTIleXCount();
	UINT iTileYCount = GetTIleYCount();

	fwrite(&iTileXCount, sizeof(UINT), 1, pFile);
	fwrite(&iTileYCount, sizeof(UINT), 1, pFile);

	const vector<CGameObject*>& vecTile = GetLayer(LAYER::TILE);
	//������ �����ؾ��ϴ����� Ȯ��������������.

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CEditorLevel::LoadTIle()
{
	// open a file name
	//�̹� ������� �����쿡�� �������ִ� �ſ����� ��޹���� ������
	//�ش�â�� �׳� Path ���ڿ��� �����һ���
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = GETINSTANCE(CPathManager)->GetContentPath();
	strTileFolderPath += L"tile\\";


	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));														//
	ofn.lStructSize = sizeof(ofn);														//
	ofn.hwndOwner = NULL;																//
	ofn.lpstrFile = szFilePath;															//
	ofn.lpstrFile[0] = '\0';															//
	ofn.nMaxFile = 256;																	//
	ofn.lpstrFilter = L"Tile\0*.tile\0Animation\0*.anim\0ALL\0*.*";						//�ǽ��� �ִϸ��̼�
	ofn.nFilterIndex = 1;																//�⺻��������
	ofn.lpstrFileTitle = NULL;															//
	ofn.nMaxFileTitle = 0;																//
	ofn.lpstrInitialDir = strTileFolderPath.c_str();									//�Ź� �ʿ���°�θ����� ��ȿ�����̱⶧���� �װ���������
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;									//

	//���̾�α׿��� ID�������� ����
	if (false == GetOpenFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");
	assert(pFile);

	const vector<CGameObject*>& vecTile = GetLayer(LAYER::TILE);


	UINT iTileXCount = 0;
	UINT iTileYCount = 0;

	fread(&iTileXCount, sizeof(UINT), 1, pFile);
	fread(&iTileYCount, sizeof(UINT), 1, pFile);

	CreateTile(iTileXCount, iTileYCount);

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}