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



void CEditorLevel::UpdateTile()
{
	if (IS_INPUT_TAB(KEY::LBTN))
	{
		//마우스 좌표를 실제좌표로 변환
		Vector2 vMousePos = GETINSTANCE(CKeyManager)->GetMousePos();
		//실제좌표로변환
		vMousePos = GETINSTANCE(CCamera)->GetRealPos(vMousePos);


		//-32도 64로 나누면 0이다.
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