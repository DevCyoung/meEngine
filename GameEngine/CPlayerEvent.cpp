#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
//Sound
#include <mmsystem.h>
#include <Windows.h>
#include "CPlayer.h"
#include "CAnimator.h"
#include "CPathManager.h"

void CPlayer::EventAttack1(void)
{		
	std::wstring str = GETINSTANCE(CPathManager)->GetContentPath();
	char* buff = new char[255];
	sprintf_s(buff, 255, "%ls", str.c_str());
	std::string path = buff;
	path += "\\Sounds\\saver";



	PlaySoundA((LPCSTR)path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
	this->attackCount = 1;
	isAtkkAvailable = false;
	free(buff);
	//isMoveReay = false;
	//PlaySoundA((LPCSTR)"C:\\Users\\tkdlq\\Desktop\\Sounds\\hu", NULL, SND_FILENAME | SND_ASYNC);
}

void CPlayer::EventAttack2(void)
{
	std::wstring str = GETINSTANCE(CPathManager)->GetContentPath();
	char* buff = new char[256];
	sprintf_s(buff, 255, "%ls", str.c_str());
	std::string path = buff;
	path += "\\Sounds\\saver";

	PlaySoundA((LPCSTR)path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
	this->attackCount = 2;
	isAtkkAvailable = false;
	free(buff);
	//isMoveReay = false;
	//PlaySoundA((LPCSTR)"C:\\Users\\tkdlq\\Desktop\\Sounds\\ha", NULL, SND_FILENAME | SND_ASYNC);
}

void CPlayer::EventAttack3(void)
{
	std::wstring str = GETINSTANCE(CPathManager)->GetContentPath();
	char* buff = new char[255];
	sprintf_s(buff,255, "%ls", str.c_str());
	std::string path = buff;
	path += "\\Sounds\\saver";

	PlaySoundA((LPCSTR)path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
	this->attackCount = 0;
	isAtkkAvailable = false;
	free(buff);
	//isMoveReay = false;
	//PlaySoundA((LPCSTR)"C:\\Users\\tkdlq\\Desktop\\Sounds\\huo", NULL, SND_FILENAME | SND_ASYNC);
}

void CPlayer::EventSCABBARD(void)
{	
	std::wstring str = GETINSTANCE(CPathManager)->GetContentPath();
	char* buff = new char[255];
	sprintf_s(buff, 255, "%ls", str.c_str());
	std::string path = buff;
	path += "\\Sounds\\saver";

	EventAtkkAvailable();
	attackCount = 0;
	GetAnimator()->Play(L"SCABBARD", false);
	free(buff);
}

void CPlayer::EventWalkReady(void)
{
	
	//isMoveReay = true;
	//EventAtkkAvailable();
	canWalk = true;
	GetAnimator()->Play(L"WALK", true);
}

void CPlayer::EventIdle(void)
{

	attackCount = 0;
	canWalk = false;
	canWalkReady = true;
	GetAnimator()->Play(L"IDLE", true);
}

void CPlayer::EventAtkkAvailable(void)
{	
	isAtkkAvailable = true;	
}


void CPlayer::EventStartVim(void)
{
	std::wstring str = GETINSTANCE(CPathManager)->GetContentPath();
	char* buff = new char[255];
	sprintf_s(buff, 255, "%ls", str.c_str());
	std::string path = buff;
	path += "\\Sounds\\startvim";

	PlaySoundA((LPCSTR)path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
	free(buff);
}

void CPlayer::EventReturnHome(void)
{
	std::wstring str = GETINSTANCE(CPathManager)->GetContentPath();
	char* buff = new char[255];
	sprintf_s(buff, 255, "%ls", str.c_str());
	std::string path = buff;
	path += "\\Sounds\\Finish_form";

	PlaySoundA((LPCSTR)path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
	free(buff);
}














void CPlayer::EventJumpReady(void)
{

}
void CPlayer::EventJump(void)
{
	GetAnimator()->Play(L"JUMP", false);
}

void CPlayer::EVENtDownReady(void)
{
	GetAnimator()->Play(L"DOWN_READY", false);
}
void CPlayer::EventDown(void)
{
	GetAnimator()->Play(L"DOWN", false);
}
void CPlayer::EventDownFinish(void)
{
	//GetAnimator()->Play(L"DOWN", false);
}
