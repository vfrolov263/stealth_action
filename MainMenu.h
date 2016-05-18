#pragma once
#include "Modules.h"

class CGame;

class CMainMenu
{
	ISprite *_pBackSprite;				// ������ ��� �������� ����
	
	IAnimation *_pButtonAnim;			// ������ ����� ��p�
	IAnimation *_pButton�ontinue;		// ������ ���������� ����
	IAnimation *_pButtonSettings;		// ������ ���������	
	IAnimation *_pButtonManagement;		// ������ ���������
 	IAnimation *_pButtonExit;			// ������ ������	
	
	ISprite *_pManagementSprite;		// ������ ��� ���� ����������
	IAnimation *_pButtonBack;			// ������ �����

	ISprite *_SettingsSprite;
	IAnimation *_pButtonSettingsBack;
	IAnimation *_pButtonLouder;
	IAnimation *_pButtonHush;
	IAnimation *_pButtonFull_screen;
	IAnimation *_pButtonWindow;

	CGame *_pGame;						// ��������� �� ����

	int _curMenu;

	void CALLBACK Init();
	
public:
	CMainMenu(CGame *pGame);
	~CMainMenu();

	// ���������
	void CALLBACK Draw();

	// ����������
	void CALLBACK Update();
};