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