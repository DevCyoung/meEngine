#include "pch.h"
#include "CEditorLevel.h"
#include "CResourceManager.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CTexture.h"

#include "CTile.h"

CEditorLevel::CEditorLevel()
{

}

CEditorLevel::~CEditorLevel()
{

}


void CEditorLevel::init()
{
	Vector2 vResolution = GETINSTANCE(CEngine)->GetWndScreenSize();
	vResolution /= 2.f;
	GETINSTANCE(CCamera)->SetLook(vResolution);
	CTexture* pTex  = GETINSTANCE(CResourceManager)->LoadTexture(L"TILE_EDIT", L"texture\\TILE.bmp");

	/*pTex->Width()  / TILE_SIZE;
	pTex->Height() / TILE_SIZE;*/

	//Ÿ�ϻ���
	CreateTile(8, 6);
		
	const vector<CGameObject*>& vecTile = GetLayer(LAYER::TILE);
	
	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->SetAtlas(pTex);
		((CTile*)vecTile[i])->SetImgIdx(i);
	}
	

}



void CEditorLevel::tick()
{
	//�������������� ƽ���������
	CLevel::tick();

}

void CEditorLevel::Enter()
{
	CEditorLevel::init();

}

void CEditorLevel::Exit()
{
}
















// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK TileCount(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
