#include "pch.h"

//Sound
#include <mmsystem.h>
#include <Windows.h>
#include "CPlayer.h"
#include "CAnimator.h"

void CPlayer::EventAttack1(void)
{
	PlaySoundA((LPCSTR)"C:\\Users\\tkdlq\\Desktop\\Sounds\\saver", NULL, SND_FILENAME | SND_ASYNC);
	this->attackCount = 1;
	isAtkkAvailable = false;
	//isMoveReay = false;
	//PlaySoundA((LPCSTR)"C:\\Users\\tkdlq\\Desktop\\Sounds\\hu", NULL, SND_FILENAME | SND_ASYNC);
}

void CPlayer::EventAttack2(void)
{
	PlaySoundA((LPCSTR)"C:\\Users\\tkdlq\\Desktop\\Sounds\\saver", NULL, SND_FILENAME | SND_ASYNC);
	this->attackCount = 2;
	isAtkkAvailable = false;
	//isMoveReay = false;
	//PlaySoundA((LPCSTR)"C:\\Users\\tkdlq\\Desktop\\Sounds\\ha", NULL, SND_FILENAME | SND_ASYNC);
}

void CPlayer::EventAttack3(void)
{
	PlaySoundA((LPCSTR)"C:\\Users\\tkdlq\\Desktop\\Sounds\\saver", NULL, SND_FILENAME | SND_ASYNC);
	this->attackCount = 0;
	isAtkkAvailable = false;
	//isMoveReay = false;
	//PlaySoundA((LPCSTR)"C:\\Users\\tkdlq\\Desktop\\Sounds\\huo", NULL, SND_FILENAME | SND_ASYNC);
}

void CPlayer::EventSCABBARD(void)
{	
	EventAtkkAvailable();
	attackCount = 0;
	GetAnimator()->Play(L"SCABBARD", false);
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
	PlaySoundA((LPCSTR)"C:\\Users\\tkdlq\\Desktop\\Sounds\\startvim", NULL, SND_FILENAME | SND_ASYNC);
}

void CPlayer::EventReturnHome(void)
{
	PlaySoundA((LPCSTR)"C:\\Users\\tkdlq\\Desktop\\Sounds\\Finish_form", NULL, SND_FILENAME | SND_ASYNC);
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
