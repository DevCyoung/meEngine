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
	//이미 만들어진 윈도우에서 제공해주는 매우편한 모달방식의 윈도우
	//해당창은 그냥 Path 문자열을 저장할뿐임

	OPENFILENAME ofn = {};

	wstring strTileFolderPath = GETINSTANCE(CPathManager)->GetMapPath();

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));														//
	ofn.lStructSize = sizeof(ofn);														//
	ofn.hwndOwner = NULL;																//
	ofn.lpstrFile = szFilePath;															//
	ofn.lpstrFile[0] = '\0';															//
	ofn.nMaxFile = 256;																	//
	ofn.lpstrFilter = L"MAP\0*.bmp";													//실습용 애니메이션
	ofn.nFilterIndex = 1;																//기본필터지정
	ofn.lpstrFileTitle = NULL;															//
	ofn.nMaxFileTitle = 0;																//
	ofn.lpstrInitialDir = strTileFolderPath.c_str();									//매번 필요없는경로를열면 비효율적이기때문에 그곳을보여줌
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;									//

	//다이어로그열기 ID값에따라 리턴
	if (false == GetOpenFileName(&ofn))
		return;
	//ofn.name
	
	//맵 고른후 한번클리어
	this->DeleteAllObject();
	GETINSTANCE(CLineColManager)->DeletCollider();
	AddMouseLineollider();


	m_backGround = new CMap();
	wstring temp = szFilePath;
	GETINSTANCE(CPathManager)->FulloRelativePath(temp);
	m_backGround->m_mapAtlas = GETINSTANCE(CResourceManager)->LoadTexture(temp.c_str(), temp.c_str());
	this->AddObject(m_backGround, LAYER::BACKGROUND);
}



//좀더 편하게 사용하기위해 UI를 만들어보자
//UI도 결국 오브젝트를 상속받는다.
void CEditorLevel::SaveLineCollider()
{
	assert(m_backGround);
	// open a file name
	//이미 만들어진 윈도우에서 제공해주는 매우편한 모달방식의 윈도우
	//해당창은 그냥 Path 문자열을 저장할뿐임
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = GETINSTANCE(CPathManager)->GetMapPath();


	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));														//
	ofn.lStructSize = sizeof(ofn);														//
	ofn.hwndOwner = NULL;																//
	ofn.lpstrFile = szFilePath;															//
	ofn.lpstrFile[0] = '\0';															//
	ofn.nMaxFile = 256;																	//
	ofn.lpstrFilter = L"MAP\0*.map";						//실습용 애니메이션
	ofn.nFilterIndex = 1;																//기본필터지정
	ofn.lpstrFileTitle = NULL;															//
	ofn.nMaxFileTitle = 0;																//
	ofn.lpstrInitialDir = strTileFolderPath.c_str();									//매번 필요없는경로를열면 비효율적이기때문에 그곳을보여줌
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;									//

	//다이어로그열기
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
	//이미 만들어진 윈도우에서 제공해주는 매우편한 모달방식의 윈도우
	//해당창은 그냥 Path 문자열을 저장할뿐임
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = GETINSTANCE(CPathManager)->GetMapPath();

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));														//
	ofn.lStructSize = sizeof(ofn);														//
	ofn.hwndOwner = NULL;																//
	ofn.lpstrFile = szFilePath;															//
	ofn.lpstrFile[0] = '\0';															//
	ofn.nMaxFile = 256;																	//
	ofn.lpstrFilter = L"MAP\0*.map";						//실습용 애니메이션
	ofn.nFilterIndex = 1;																//기본필터지정
	ofn.lpstrFileTitle = NULL;															//
	ofn.nMaxFileTitle = 0;																//
	ofn.lpstrInitialDir = strTileFolderPath.c_str();									//매번 필요없는경로를열면 비효율적이기때문에 그곳을보여줌
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;									//

	//다이어로그열기 ID값에따라 리턴
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

