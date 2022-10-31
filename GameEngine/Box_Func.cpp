#include "pch.h"
#include "CEditorLevel.h"
#include "CResourceManager.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CTexture.h"

#include "CTile.h"
#include "resource.h"


#include "CUI.h"
#include "CButton.h"

#include "CWall.h"
#include "CGameObject.h"

//Manager
#include "CLevelManager.h"
#include "CKeyManager.h"
#include "CPathManager.h"
#include "CLineColManager.h"
#include "CCollisionManager.h"
#include "CCollider.h"

#include "CZero.h"

void CEditorLevel::CreateBoxMode()
{
	//�ڽ��� ���콺�� ����ٴѴ�.

	//Ŭ�����Ѵ�.
	if (IS_INPUT_TAB(KEY::LBTN) && m_BoxMosueMode == MOUSE_MODE::NONE)
	{
		//DRAW MODE
		m_BoxMosueMode = MOUSE_MODE::ONEDOWN;
		m_bottom = Vector2(0.f, 0.f);
		m_leftTop = Vector2(0.f, 0.f);
		m_leftTop = GETINSTANCE(CCamera)->GetRealMousePos();
		m_curObj = new CWall();
		AddObject(m_curObj, LAYER::WALL);		
	}
	else if (IS_INPUT_TAB(KEY::LBTN) && m_BoxMosueMode == MOUSE_MODE::ONEDOWN)
	{		
		m_BoxMosueMode = MOUSE_MODE::NONE;		
	}

	if (m_BoxMosueMode == MOUSE_MODE::ONEDOWN)
	{
		m_bottom = GETINSTANCE(CCamera)->GetRealMousePos();
		m_curObj->ResizeCollider(m_leftTop, m_bottom);
	}
	if (IS_INPUT_TAB(KEY::RBTN))
	{
		CZero* zero = new CZero();
		Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();
		pos = GETINSTANCE(CCamera)->GetRealPos(pos);
		/*zero->SetPos(pos);
		this->AddObject(zero, LAYER::PLAYER);*/
		CGameObject::Instantiate(zero, pos, LAYER::PLAYER);
	}
	if (IS_INPUT_TAB(KEY::_8))
	{
		SaveBoxCollider();
	}
	if (IS_INPUT_TAB(KEY::_9))
	{
		LoadBoxCollider();
	}
}

void CEditorLevel::SaveBoxCollider()
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
	ofn.lpstrFilter = L"MAP\0*.map";													//�ǽ��� �ִϸ��̼�
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

	const vector<CGameObject*>& vecTile = GetLayer(LAYER::WALL);
	//������ �����ؾ��ϴ����� Ȯ��������������.

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CEditorLevel::LoadBoxCollider()
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
	ofn.lpstrFilter = L"MAP\0*.map";													//�ǽ��� �ִϸ��̼�
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

	const vector<CGameObject*>& vecTile = GetLayer(LAYER::WALL);


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

