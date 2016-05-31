#pragma once
#include "Modules.h"

class CGame;

const int levels_number = 7;

class CMainMenu
{
	ISprite *_pBackSprite;           // Задний фон.
	IAnimation *buttons[levels_number]; //!!!массив кнопок меню
	int _lastLevel; //последний уровень

	CGame *_pGame;                   // Указатель на игру, для вызова метода _pGame->SetState

	void CALLBACK Init();
public:
	CMainMenu(CGame *pGame);
	~CMainMenu();

	// Здесь вся отрисовка
	void CALLBACK Draw();

	// Здесь все обновление
	void CALLBACK Update();

	void CALLBACK SetProgress(int number) { _lastLevel = number; }
};