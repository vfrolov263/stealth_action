#pragma once
#include "Modules.h"

class CGame;

class �PauseMenu
{
	CGame *_pGame;

	ISprite *_pBackPauseSprite;      // ������ ��� �������� ����
	
	IAnimation *_pButtonReturn;      // ������ ����� ����
	IAnimation *_pButtonUnknow;		 // ������ ... ���... ������ ������

	void CALLBACK Init();
public:
	�PauseMenu(CGame *pGame);
	~�PauseMenu();

	// ���������
	void CALLBACK Draw();

	// ����������
	void CALLBACK Update();
};