#pragma once
#include "Modules.h"

class CGame;

class СPauseMenu
{
	CGame *_pGame;

	ISprite *_pBackPauseSprite;      // Задний фон главного меню
	
	IAnimation *_pButtonReturn;      // Кнопка новая игпа
	IAnimation *_pButtonUnknow;		 // Кнопка ... эээ... просто кнопка

	void CALLBACK Init();
public:
	СPauseMenu(CGame *pGame);
	~СPauseMenu();

	// Отрисовка
	void CALLBACK Draw();

	// Обновления
	void CALLBACK Update();
};