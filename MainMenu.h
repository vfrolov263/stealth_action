#pragma once
#include "Modules.h"

class CGame;

class CMainMenu
{
	ISprite *_pBackSprite;				// Задний фон главного меню
	
	IAnimation *_pButtonAnim;			// Кнопка новая игpа
	IAnimation *_pButtonСontinue;		// Кнопка продолжить игру
	IAnimation *_pButtonSettings;		// Кнопка настройки	
	IAnimation *_pButtonManagement;		// Кнопка упавления
 	IAnimation *_pButtonExit;			// Кнопка выхода	
	
	ISprite *_pManagementSprite;		// Задний фон меню управления
	IAnimation *_pButtonBack;			// Кнопка назад

	ISprite *_SettingsSprite;
	IAnimation *_pButtonSettingsBack;
	IAnimation *_pButtonLouder;
	IAnimation *_pButtonHush;
	IAnimation *_pButtonFull_screen;
	IAnimation *_pButtonWindow;

	CGame *_pGame;						// Указатель на игру

	int _curMenu;

	void CALLBACK Init();
	
public:
	CMainMenu(CGame *pGame);
	~CMainMenu();

	// Отрисовка
	void CALLBACK Draw();

	// Обновления
	void CALLBACK Update();
};