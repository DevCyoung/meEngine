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

CEditorLevel::CEditorLevel()
	: m_hMenu(nullptr)
	, m_eMode(EDITOR_MODE::NONE)
{

}

CEditorLevel::~CEditorLevel()
{	
	//DeleteMenu �� ���� ���� �� �����ϳ��� �����
	//DestroyMenu �޴������� ���������Ҷ�
	if (nullptr != m_hMenu)
		DestroyMenu(m_hMenu);
}







void CEditorLevel::tick()
{
	//�������������� ƽ���������
	CLevel::tick();
	
	if (IS_INPUT_TAB(KEY::_1))
	{
		m_eMode = EDITOR_MODE::TILE;
	}
	if (IS_INPUT_TAB(KEY::_2))
	{
		m_eMode = EDITOR_MODE::ANIMATION;
	}
	if (IS_INPUT_TAB(KEY::_3))
	{
		m_eMode = EDITOR_MODE::OBJECT;
	}
	
	if (IS_INPUT_TAB(KEY::ENTER))
	{		
		CLevelManager::LoadLevel(LEVEL_TYPE::TITLE);
	}
	Update();
}
void CEditorLevel::Update()
{
	switch (m_eMode)
	{
	case EDITOR_MODE::TILE:
		UpdateTile();
		break;
	case EDITOR_MODE::ANIMATION:
		break;
	case EDITOR_MODE::OBJECT:
		break;	
	}
}

void CEditorLevel::UpdateTile()
{
	if (IS_INPUT_TAB(KEY::LBTN))
	{
		//���콺 ��ǥ�� ������ǥ�� ��ȯ
		Vector2 vMousePos = GETINSTANCE(CKeyManager)->GetMousePos();
		//������ǥ�κ�ȯ
		vMousePos = GETINSTANCE(CCamera)->GetRealPos(vMousePos);

		
		//-32�� 64�� ������ 0�̴�.
		int x = (int)vMousePos.x / TILE_SIZE;
		int y = (int)vMousePos.y / TILE_SIZE;
		int idx = y * GetTIleXCount() + x;

		if (0.f <= vMousePos.x && x < (int)GetTIleXCount() && 0.f <= vMousePos.y && y < (int)GetTIleYCount())
		{
			const std::vector<CGameObject*>& tiles = GetLayer(LAYER::TILE);		
			idx %= tiles.size();;
			((CTile*)tiles[idx])->AddImgIdx();		
		}

	}


	//��� ������� �ص���������� �ϴ� �̷����غ��ƿ���
	if (IS_INPUT_TAB(KEY::_8))
	{
		SaveTIle();
	}
	else if (IS_INPUT_TAB(KEY::_9))
	{
		LoadTIle();
	}

}

void CEditorLevel::UpdateAnimation()
{
}

void CEditorLevel::UpdateObject()
{
}

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


void CEditorLevel::Enter()
{
	//�޴��ٻ���
	if (nullptr == m_hMenu)
	{
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_GAMEENGINE));
	}

	HWND hWnd = GETINSTANCE(CEngine)->GetMainWnd();
	SetMenu(hWnd, m_hMenu);
	
	POINT ptWndScreenSize = GETINSTANCE(CEngine)->GetWndScreenSize();
	GETINSTANCE(CEngine)->WindowReSize(ptWndScreenSize.x, ptWndScreenSize.y);



	//�ʱ� ������Ʈ ����
	init();
}

void CEditorLevel::Exit()
{
	//�޴��ٻ̱�
	HWND hWnd = GETINSTANCE(CEngine)->GetMainWnd();
	SetMenu(hWnd, nullptr);

	POINT ptWndScreenSize = GETINSTANCE(CEngine)->GetWndScreenSize();
	GETINSTANCE(CEngine)->WindowReSize(ptWndScreenSize.x, ptWndScreenSize.y);
}




// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
// this prc my engine important
INT_PTR CALLBACK TileCount(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		//�ظ��ϸ� OK CANCLE ID�� �״�� ����
		if (LOWORD(wParam) == IDOK)
		{
			// Editor COntrol ���Էµȼ��� �޾ƿ���.
			// ���͸� ������ OK�� �����̵�����
			// ESC�� CANCLE �θ��εǾ�����
			// Ȯ�� ��ҹ�ư�� ��ü ID�� �Ұ� Ű�Է����� ������ ������ �߻��Ҽ��ִ�. �����̾ȵ�
			int iTileXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int iTileYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);

			//�޼����ڽ��� �̹� �ϼ��� ������
			if (iTileXCount == 0 || iTileYCount == 0)
			{
				MessageBox(nullptr, L"Ÿ�� ������ �����ϼ���", L"Ÿ�ϻ�������", MB_OK);
				return (INT_PTR)TRUE;
			}

			CLevel* pCurLevel = GETINSTANCE(CLevelManager)->GetCurLevel();
			pCurLevel->CreateTile(iTileXCount, iTileYCount);

			CTexture* pTex = GETINSTANCE(CResourceManager)->LoadTexture(L"TILE_EDIT", L"texture\\TILE.bmp");
			const vector<CGameObject*>& vecTile = pCurLevel->GetLayer(LAYER::TILE);

			for (size_t i = 0; i < vecTile.size(); i++)
			{
				((CTile*)vecTile[i])->SetAtlas(pTex);
				((CTile*)vecTile[i])->SetImgIdx(0);
			}

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


