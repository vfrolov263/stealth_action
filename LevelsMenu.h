#pragma once
#include "Modules.h"

class CGame;

const int levels_number = 7;

class CMainMenu
{
	ISprite *_pBackSprite;           // ������ ���.
	IAnimation *buttons[levels_number]; //!!!������ ������ ����
	int _lastLevel; //��������� �������

	CGame *_pGame;                   // ��������� �� ����, ��� ������ ������ _pGame->SetState

	void CALLBACK Init();
public:
	CMainMenu(CGame *pGame);
	~CMainMenu();

	// ����� ��� ���������
	void CALLBACK Draw();

	// ����� ��� ����������
	void CALLBACK Update();

	void CALLBACK SetProgress(int number) { _lastLevel = number; }
};