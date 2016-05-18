#pragma once
#include "Modules.h"

class CGame;

class CCartoon
{
	ISprite *_pBackSprite;           // Задний фон.
	IAnimation *_pButtonNext;        // Кнопка
	CGame *_pGame;                   // Указатель на игру, для вызова метода _pGame->SetState
	OPM::cstr fileName[10];
	int countFrame;
	int frameNumber;

	void CALLBACK Init(OPM::cstr);
public:
	CCartoon(int levelNumber);
	~CCartoon();

	// Здесь вся отрисовка
	void CALLBACK Draw();

	// Здесь все обновление
	void CALLBACK Update();
};