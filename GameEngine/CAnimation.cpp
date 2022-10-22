#include "pch.h"
#include "CAnimation.h"

#include "CGameObject.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CCamera.h"


#include "CTimeManager.h"
#include "CPathManager.h"
#include "CResourceManager.h"
#include "CEventManager.h"
#include "CAnimEnvManager.h"


#include "CEngine.h"

CAnimation::CAnimation(CAnimator* _pAnimator)
	: m_pAnimator(_pAnimator)
	, m_pAtlas(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::init(const wstring& _strName, CTexture* _pAtlas, Vector2 _vLeftTop, Vector2 _vSize, Vector2 _vOffset, int _iMaxFrmCount, float _fDuration)
{
	SetName(_strName);	// Animation 이름
	m_pAtlas = _pAtlas;	// Animation 의 아틀라스 이미지

	for (int i = 0; i < _iMaxFrmCount; ++i)
	{
		tAnimFrm frm = {};

		frm.vLeftTop = Vector2(_vLeftTop.x + (float)i * _vSize.x, _vLeftTop.y);
		frm.vSize = _vSize;
		frm.vOffset = _vOffset;
		frm.fDuration = _fDuration;
		m_vecFrm.push_back(frm);
	}
}


void CAnimation::tick()
{
	if (m_bFinish)
		return;

	m_fAccTime += DELTATIME;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{

		//만약 현재프레임이 이벤트를 등록했다면
		//이벤트를 신청한다.		
		if (nullptr != m_vecFrm[m_iCurFrm].action.instance)
		{
			tAnimEvent env = {};
			env.func = m_vecFrm[m_iCurFrm].action.func;
			env.instance = m_vecFrm[m_iCurFrm].action.instance;
			GETINSTANCE(CEventManager)->AddEvent(env);
		}

		++m_iCurFrm;
		m_fAccTime = 0.f;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = (int)m_vecFrm.size() - 1;
			m_bFinish = true;
		}
	}
}

void CAnimation::render(HDC _dc)
{
	CGameObject* pOwnerObj = m_pAnimator->GetOwner();
	Vector2 vPos =GETINSTANCE(CCamera)->GetRenderPos(pOwnerObj->GetPos());

	tAnimFrm frame = m_vecFrm[m_iCurFrm];



	HDC		hdc = CreateCompatibleDC(_dc);
	HBITMAP bitmap	= CreateCompatibleBitmap(_dc, frame.vSize.x * 3, frame.vSize.y * 3);

	HBITMAP hPrebit = (HBITMAP)SelectObject(hdc, bitmap);
	DeleteObject(hPrebit);


	if (pOwnerObj->GetFilpX())
	{
		StretchBlt
		(
			hdc
			, frame.vSize.x * 3 - 1
			, 0
			, (int)(-frame.vSize.x * 3)
			, (int)( frame.vSize.y * 3)
			, m_pAtlas->GetDC()
			, (int)(frame.vLeftTop.x)
			, (int)(frame.vLeftTop.y)
			, (int)(frame.vSize.x)
			, (int)(frame.vSize.y)
			, SRCCOPY
		);

		TransparentBlt
		(
			_dc
			, int((int)vPos.x - (int)(frame.vSize.x * 3 + frame.vOffset.x * 3) / 2)
			, int((int)vPos.y - (int)(frame.vSize.y * 3 - frame.vOffset.y * 3) / 2)
			, int(frame.vSize.x * 3)
			, int(frame.vSize.y * 3)
			, hdc
			, 0
			, 0
			, int(frame.vSize.x * 3)
			, int(frame.vSize.y * 3)
			, RGB(255, 0, 255)
		);
	}
	else
	{
		StretchBlt
		(
			hdc
			, 0
			, 0
			, (int)(frame.vSize.x * 3)
			, (int)(frame.vSize.y * 3)
			, m_pAtlas->GetDC()
			, (int)(frame.vLeftTop.x)
			, (int)(frame.vLeftTop.y)
			, (int)(frame.vSize.x)
			, (int)(frame.vSize.y)
			, SRCCOPY
		);

		TransparentBlt
		(
			_dc
			, int((int)vPos.x - (int)(frame.vSize.x * 3  - frame.vOffset.x * 3) / 2)
			, int((int)vPos.y - (int)(frame.vSize.y * 3  - frame.vOffset.y * 3) / 2)
			, int(frame.vSize.x * 3)
			, int(frame.vSize.y * 3)
			, hdc
			, 0
			, 0
			, int(frame.vSize.x * 3)
			, int(frame.vSize.y * 3)
			, RGB(255, 0, 255)
		);
	}

	//Rectangle(m_pRealBuffer->GetDC(), -1, -1, m_pRealBuffer->Width() + 1, m_pRealBuffer->Height() + 1);

	//GETINSTANCE(CLevelManager)->render(m_pRealBuffer->GetDC());

	//내가짬
	//GETINSTANCE(CLineColManager)->render(m_pRealBuffer->GetDC());

	//StretchBlt
	//(
	//	_dc, 0, 0, m_ptWndScreenSize.x, m_ptWndScreenSize.y, m_pRealBuffer->GetDC(), 0, 0, m_pRealBuffer->Width(), m_pRealBuffer->Height(), SRCCOPY
	//);



	HPEN hPen = nullptr;
	hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::GREEN);

	HBRUSH	hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HPEN	hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH	hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);



	tColInfo colInfo = frame.colInfo;

	if (colInfo.vScale.x > 0.000001f || (colInfo.vScale.y > 0.000001f))
	{
		Vector2 vLPos = vPos - ((colInfo.vOffset * 3  - colInfo.vScale   * 3))   / 2;

		if (pOwnerObj->GetFilpX() == false)
		{
			vLPos.x = vPos.x - (colInfo.vScale.x  /  2  + colInfo.vOffset.x ) * 3;
			vLPos.y = vPos.y - (colInfo.vScale.y  / 2  + colInfo.vOffset.y ) * 3;
		}
		else
		{
			vLPos.x = vPos.x + (colInfo.vOffset.x - colInfo.vScale.x / 2)  *  3  ;
			vLPos.y = vPos.y - (colInfo.vOffset.y + colInfo.vScale.y / 2 ) *  3   ;
		}




		Rectangle(
			_dc
			, vLPos.x
			, vLPos.y
			, vLPos.x + colInfo.vScale.x *3
			, vLPos.y + colInfo.vScale.y *3
		);
	
	}

	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);

	DeleteDC(hdc);
	DeleteObject(bitmap);
}


void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilepath = GETINSTANCE(CPathManager)->GetContentPath();
	strFilepath += _strRelativePath;

	// 파일 입출력
	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strFilepath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Animation Save 실패, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"파일 저장 실패", MB_OK);
		return;
	}

	// Animation 이름 저장
	fwprintf_s(pFile, L"\n");

	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");
	fwprintf_s(pFile, GetName().c_str());
	fwprintf_s(pFile, L"\n\n");

	// 아틀라스 텍스쳐 키값 저장	
	fwprintf_s(pFile, L"[ATLAS_KEY]\n");
	fwprintf_s(pFile, m_pAtlas->GetKey().c_str());
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[ATLAS_PATH]\n");
	fwprintf_s(pFile, m_pAtlas->GetRelativePath().c_str());
	fwprintf_s(pFile, L"\n\n");


	// 프레임 정보 저장
	wchar_t szNum[50] = {};

	fwprintf_s(pFile, L"[FRAME_COUNT]\n");

	size_t iFrmCount = m_vecFrm.size();
	_itow_s((int)iFrmCount, szNum, 50, 10);

	fwprintf_s(pFile, szNum);
	fwprintf_s(pFile, L"\n\n");

	for (size_t i = 0; i < iFrmCount; ++i)
	{
		fwprintf_s(pFile, L"[%zd_FRAME]\n", i);

		// LEFT_TOP
		fwprintf_s(pFile, L"[LEFT_TOP]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].vLeftTop.x, m_vecFrm[i].vLeftTop.y);

		// SIZE
		fwprintf_s(pFile, L"[SIZE]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].vSize.x, m_vecFrm[i].vSize.y);

		// OFFSET
		fwprintf_s(pFile, L"[OFFSET]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].vOffset.x, m_vecFrm[i].vOffset.y);

		// DURATION
		fwprintf_s(pFile, L"[DURATION]\n");
		fwprintf_s(pFile, L"%.2f\n", m_vecFrm[i].fDuration);

		fwprintf_s(pFile, L"\n");
	}

	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilepath = GETINSTANCE(CPathManager)->GetContentPath();
	strFilepath += _strRelativePath;

	// 파일 입출력
	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strFilepath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Animation Save 실패, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"파일 저장 실패", MB_OK);
		return;
	}

	size_t iFrameCount = 0;
	wstring strAtlasKey;
	wstring strAltasRelativePath;

	while (true)
	{
		wchar_t szBuffer[256] = {};
		fwscanf_s(pFile, L"%s", szBuffer, 256);

		if (!wcscmp(szBuffer, L"[ANIMATION_NAME]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);		
			SetName(szBuffer);
		}

		else if (!wcscmp(szBuffer, L"[ATLAS_KEY]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			strAtlasKey = szBuffer;
		}

		else if (!wcscmp(szBuffer, L"[ATLAS_PATH]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			strAltasRelativePath = szBuffer;
		}

		else if (!wcscmp(szBuffer, L"[FRAME_COUNT]"))
		{
			fwscanf_s(pFile, L"%zd", &iFrameCount);

			for (size_t i = 0; i < iFrameCount; ++i)
			{
				tAnimFrm frm = {};

				while (true)
				{
					wchar_t szBuffer[256] = {};
					fwscanf_s(pFile, L"%s", szBuffer, 256);

					if (!wcscmp(szBuffer, L"[LEFT_TOP]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vLeftTop.x, &frm.vLeftTop.y);
					}

					else if (!wcscmp(szBuffer, L"[SIZE]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vSize.x, &frm.vSize.y);
					}

					else if (!wcscmp(szBuffer, L"[OFFSET]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vOffset.x, &frm.vOffset.y);
					}

					else if (!wcscmp(szBuffer, L"[DURATION]"))
					{
						fwscanf_s(pFile, L"%f", &frm.fDuration);
						break;
					}				
				}

				while (true)
				{
					wchar_t szBuffer[256] = {};
					fwscanf_s(pFile, L"%s", szBuffer, 256);



					if (!wcscmp(szBuffer, L"[COLLIDER]"))
					{						
					}

					else if (!wcscmp(szBuffer, L"[LEFT_TOP]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.colInfo.vLeftTop.x, &frm.colInfo.vLeftTop.y);					
					}

					else if (!wcscmp(szBuffer, L"[SIZE]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.colInfo.vScale.x, &frm.colInfo.vScale.y);
					}

					else if (!wcscmp(szBuffer, L"[OFFSET]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.colInfo.vOffset.x, &frm.colInfo.vOffset.y);
						break;
					}					
				}

				m_vecFrm.push_back(frm);
			}

			break;
		}
	}

	m_pAtlas = GETINSTANCE(CResourceManager)->LoadTexture(strAtlasKey, strAltasRelativePath);

	fclose(pFile);
}

