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

#include "CLineColManager.h"
#include "CMap.h"
#include "CLineCollider.h"

void CEditorLevel::StartMapEditMode()
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
	ofn.lpstrFilter = L"MAP\0*.bmp";													//�ǽ��� �ִϸ��̼�
	ofn.nFilterIndex = 1;																//�⺻��������
	ofn.lpstrFileTitle = NULL;															//
	ofn.nMaxFileTitle = 0;																//
	ofn.lpstrInitialDir = strTileFolderPath.c_str();									//�Ź� �ʿ���°�θ����� ��ȿ�����̱⶧���� �װ���������
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;									//

	//���̾�α׿��� ID�������� ����
	if (false == GetOpenFileName(&ofn))
		return;
	//ofn.name
	
	//�� ���� �ѹ�Ŭ����
	this->DeleteAllObject();
	GETINSTANCE(CLineColManager)->DeletCollider();
	AddMouseLineollider();


	m_backGround = new CMap();
	wstring temp = szFilePath;
	GETINSTANCE(CPathManager)->FulloRelativePath(temp);
	m_backGround->m_mapAtlas = GETINSTANCE(CResourceManager)->LoadTexture(temp.c_str(), temp.c_str());
	this->AddObject(m_backGround, LAYER::BACKGROUND);
}



//���� ���ϰ� ����ϱ����� UI�� ������
//UI�� �ᱹ ������Ʈ�� ��ӹ޴´�.
void CEditorLevel::SaveLineCollider()
{
	assert(m_backGround);
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
	ofn.lpstrFilter = L"MAP\0*.map";						//�ǽ��� �ִϸ��̼�
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

	DeleteMouse();

	size_t strCount = m_backGround->m_mapAtlas->GetRelativePath().length();
	fwrite(&strCount, sizeof(size_t), 1, pFile);
	fwrite(m_backGround->m_mapAtlas->GetRelativePath().c_str(), sizeof(wchar_t), strCount, pFile);

	GETINSTANCE(CLineColManager)->Save(pFile);

	fclose(pFile);
}

void CEditorLevel::LoadLineCollider()
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
	ofn.lpstrFilter = L"MAP\0*.map";						//�ǽ��� �ִϸ��̼�
	ofn.nFilterIndex = 1;																//�⺻��������
	ofn.lpstrFileTitle = NULL;															//
	ofn.nMaxFileTitle = 0;																//
	ofn.lpstrInitialDir = strTileFolderPath.c_str();									//�Ź� �ʿ���°�θ����� ��ȿ�����̱⶧���� �װ���������
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;									//

	//���̾�α׿��� ID�������� ����
	if (false == GetOpenFileName(&ofn))
		return;


	this->DeleteAllObject();
	

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");
	assert(pFile);

	CMap* m = new CMap();
	 
	size_t strCount = 1;
	wchar_t buffer[256] = {};

	GETINSTANCE(CLineColManager)->DeletCollider();
	this->DeleteAllObject();

	fread(&strCount, sizeof(size_t), 1, pFile);
	fread(buffer, sizeof(wchar_t), strCount, pFile);
	m->m_mapAtlas = GETINSTANCE(CResourceManager)->LoadTexture(buffer, buffer);
	GETINSTANCE(CLevelManager)->GetCurLevel()->AddObject(m, LAYER::BACKGROUND);



	GETINSTANCE(CLineColManager)->Load(pFile);

	AddMouseLineollider();


	fclose(pFile);
}

