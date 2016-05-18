#pragma once
#include "Modules.h"

class CGame;

class CCartoon
{
	ISprite *_pBackSprite;           // ������ ���.
	IAnimation *_pButtonNext;        // ������
	CGame *_pGame;                   // ��������� �� ����, ��� ������ ������ _pGame->SetState
	OPM::cstr fileName[10];
	int countFrame;
	int frameNumber;

	void CALLBACK Init(OPM::cstr);
public:
	CCartoon(int levelNumber);
	~CCartoon();

	// ����� ��� ���������
	void CALLBACK Draw();

	// ����� ��� ����������
	void CALLBACK Update();
};