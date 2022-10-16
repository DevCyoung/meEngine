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


CEditorLevel::CEditorLevel()
	: m_hMenu(nullptr)
	, m_eMode(EDITOR_MODE::NONE)
{

}

CEditorLevel::~CEditorLevel()
{	
	//DeleteMenu 는 파일 도움말 등 파일하나를 지우는
	//DestroyMenu 메뉴단위가 없어져야할때
	if (nullptr != m_hMenu)
		DestroyMenu(m_hMenu);
}




void CEditorLevel::init()
{
	Vector2 vResolution = GETINSTANCE(CEngine)->GetWndScreenSize();
	vResolution /= 2.f;
	GETINSTANCE(CCamera)->SetLook(vResolution);

	CTexture* pTex  = GETINSTANCE(CResourceManager)->LoadTexture(L"TILE_EDIT", L"texture\\TILE.bmp");	
	CreateTile(8, 6);		
	const vector<CGameObject*>& vecTile = GetLayer(LAYER::TILE);
	
	for (int i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->SetAtlas(pTex);
		((CTile*)vecTile[i])->SetImgIdx(i);
	}
	

	m_eMode = EDITOR_MODE::TILE;
}



void CEditorLevel::tick()
{
	//직접구현했으면 틱돌게햐아함
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
		//마우스 좌표를 실제좌표로 변환
		Vector2 vMousePos = GETINSTANCE(CKeyManager)->GetMousePos();
		//실제좌표로변환
		vMousePos = GETINSTANCE(CCamera)->GetRealPos(vMousePos);

		
		//-32도 64로 나누면 0이다.
		int x = vMousePos.x / TILE_SIZE;
		int y = vMousePos.y / TILE_SIZE;
		int idx = y * GetTIleXCount() + x;

		if (0.f <= vMousePos.x && x < GetTIleXCount() && 0.f <= vMousePos.y && y < GetTIleYCount())
		{
			const std::vector<CGameObject*>& tiles = GetLayer(LAYER::TILE);		
			idx %= tiles.size();;
			((CTile*)tiles[idx])->AddImgIdx();		
		}

	}


	//모달 방식으로 해도상관업슨데 일단 이렇게해보아여ㅛ
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

void CEditorLevel::SaveTIle()
{
	wstring strFilePath = GETINSTANCE(CPathManager)->GetContentPath();
	strFilePath += L"tile\\test.tile";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");



	// 타일 가로 세로 개수저장
	UINT iTileXCount = GetTIleXCount();
	UINT iTileYCount = GetTIleYCount();

	fwrite(&iTileXCount, sizeof(UINT), 1, pFile);
	fwrite(&iTileYCount, sizeof(UINT), 1, pFile);

	const vector<CGameObject*>& vecTile = GetLayer(LAYER::TILE);
	//무엇을 저장해야하는지는 확정지을수가없다.

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CEditorLevel::LoadTIle()
{
	wstring strFilePath = GETINSTANCE(CPathManager)->GetContentPath();
	strFilePath += L"tile\\test.tile";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
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
	//메뉴바생성
	if (nullptr == m_hMenu)
	{
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_GAMEENGINE));
	}

	HWND hWnd = GETINSTANCE(CEngine)->GetMainWnd();
	SetMenu(hWnd, m_hMenu);
	
	POINT ptWndScreenSize = GETINSTANCE(CEngine)->GetWndScreenSize();
	GETINSTANCE(CEngine)->WindowReSize(ptWndScreenSize.x, ptWndScreenSize.y);



	//초기 오브젝트 설정
	init();
}

void CEditorLevel::Exit()
{
	//메뉴바뽑기
	HWND hWnd = GETINSTANCE(CEngine)->GetMainWnd();
	SetMenu(hWnd, nullptr);

	POINT ptWndScreenSize = GETINSTANCE(CEngine)->GetWndScreenSize();
	GETINSTANCE(CEngine)->WindowReSize(ptWndScreenSize.x, ptWndScreenSize.y);
}




// 정보 대화 상자의 메시지 처리기입니다.
// this prc my engine important
INT_PTR CALLBACK TileCount(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		//왠만하면 OK CANCLE ID를 그대로 쓸것
		if (LOWORD(wParam) == IDOK)
		{
			// Editor COntrol 에입력된숫자 받아오기.
			// 엔터를 눌러도 OK로 맵핑이되있음
			// ESC는 CANCLE 로맵핑되어있음
			// 확인 취소버튼은 자체 ID로 할것 키입력으로 했을때 문제가 발생할수있다. 연동이안됨
			int iTileXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int iTileYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);

			//메세지박스는 이미 완성된 윈도우
			if (iTileXCount == 0 || iTileYCount == 0)
			{
				MessageBox(nullptr, L"타일 개수를 지정하세요", L"타일생성오류", MB_OK);
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


