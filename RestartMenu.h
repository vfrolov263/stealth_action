#pragma once
#include "Modules.h"

class CGame;

class CRestartMenu
{
	ISprite *_pBackSprite;           // Задний фон.
	IAnimation *_pButtonEnd;        // Кнопка
	IAnimation *_pButtonNew;
	CGame *_pGame;                   // Указатель на игру, для вызова метода _pGame->SetState

	void CALLBACK Init();
public:
	CRestartMenu(CGame *pGame);
	~CRestartMenu();

	// Здесь вся отрисовка
	void CALLBACK Draw();

	// Здесь все обновление
	void CALLBACK Update();
};