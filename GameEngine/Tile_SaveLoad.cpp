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

//좀더 편하게 사용하기위해 UI를 만들어보자
//UI도 결국 오브젝트를 상속받는다.
//void CEditorLevel::SaveTIle()
//{
//	// open a file name
//	//이미 만들어진 윈도우에서 제공해주는 매우편한 모달방식의 윈도우
//	//해당창은 그냥 Path 문자열을 저장할뿐임
//	OPENFILENAME ofn = {};
//
//	wstring strTileFolderPath = GETINSTANCE(CPathManager)->GetContentPath();
//	strTileFolderPath += L"tile\\";
//
//
//	wchar_t szFilePath[256] = {};
//
//	ZeroMemory(&ofn, sizeof(ofn));														//
//	ofn.lStructSize = sizeof(ofn);														//
//	ofn.hwndOwner = NULL;																//
//	ofn.lpstrFile = szFilePath;															//
//	ofn.lpstrFile[0] = '\0';															//
//	ofn.nMaxFile = 256;																	//
//	ofn.lpstrFilter = L"Tile\0*.tile\0Animation\0*.anim\0ALL\0*.*";						//실습용 애니메이션
//	ofn.nFilterIndex = 1;																//기본필터지정
//	ofn.lpstrFileTitle = NULL;															//
//	ofn.nMaxFileTitle = 0;																//
//	ofn.lpstrInitialDir = strTileFolderPath.c_str();									//매번 필요없는경로를열면 비효율적이기때문에 그곳을보여줌
//	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;									//
//
//	//다이어로그열기
//	if (false == GetSaveFileName(&ofn))
//		return;
//
//	FILE* pFile = nullptr;
//	_wfopen_s(&pFile, szFilePath, L"wb");
//	assert(pFile);
//
//
//
//	// 타일 가로 세로 개수저장
//	UINT iTileXCount = GetTIleXCount();
//	UINT iTileYCount = GetTIleYCount();
//
//	fwrite(&iTileXCount, sizeof(UINT), 1, pFile);
//	fwrite(&iTileYCount, sizeof(UINT), 1, pFile);
//
//	const vector<CGameObject*>& vecTile = GetLayer(LAYER::TILE);
//	//무엇을 저장해야하는지는 확정지을수가없다.
//
//	for (size_t i = 0; i < vecTile.size(); i++)
//	{
//		((CTile*)vecTile[i])->Save(pFile);
//	}
//
//	fclose(pFile);
//}
//
//void CEditorLevel::LoadTIle()
//{
//	// open a file name
//	//이미 만들어진 윈도우에서 제공해주는 매우편한 모달방식의 윈도우
//	//해당창은 그냥 Path 문자열을 저장할뿐임
//	OPENFILENAME ofn = {};
//
//	wstring strTileFolderPath = GETINSTANCE(CPathManager)->GetContentPath();
//	strTileFolderPath += L"tile\\";
//
//
//	wchar_t szFilePath[256] = {};
//
//	ZeroMemory(&ofn, sizeof(ofn));														//
//	ofn.lStructSize = sizeof(ofn);														//
//	ofn.hwndOwner = NULL;																//
//	ofn.lpstrFile = szFilePath;															//
//	ofn.lpstrFile[0] = '\0';															//
//	ofn.nMaxFile = 256;																	//
//	ofn.lpstrFilter = L"Tile\0*.tile\0Animation\0*.anim\0ALL\0*.*";						//실습용 애니메이션
//	ofn.nFilterIndex = 1;																//기본필터지정
//	ofn.lpstrFileTitle = NULL;															//
//	ofn.nMaxFileTitle = 0;																//
//	ofn.lpstrInitialDir = strTileFolderPath.c_str();									//매번 필요없는경로를열면 비효율적이기때문에 그곳을보여줌
//	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;									//
//
//	//다이어로그열기 ID값에따라 리턴
//	if (false == GetOpenFileName(&ofn))
//		return;
//
//	FILE* pFile = nullptr;
//	_wfopen_s(&pFile, szFilePath, L"rb");
//	assert(pFile);
//
//	const vector<CGameObject*>& vecTile = GetLayer(LAYER::TILE);
//
//
//	UINT iTileXCount = 0;
//	UINT iTileYCount = 0;
//
//	fread(&iTileXCount, sizeof(UINT), 1, pFile);
//	fread(&iTileYCount, sizeof(UINT), 1, pFile);
//
//	CreateTile(iTileXCount, iTileYCount);
//
//	for (size_t i = 0; i < vecTile.size(); i++)
//	{
//		((CTile*)vecTile[i])->Load(pFile);
//	}
//
//	fclose(pFile);
//}