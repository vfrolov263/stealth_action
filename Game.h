#pragma once
#include <Game.h>
#include "Level.h"
#include "MainMenu.h"
#include "RestartMenu.h"
#include "PauseMenu.h"

enum E_GAME_STATE
{
	GS_MENU,
	GS_PAUSE,
	GS_ACTION,
	GS_RESTART
};

class CGame: public IGame
{
	CMainMenu *_pMainMenu;           // Это наше главное меню.
	CRestartMenu *_pRestartMenu;
	СPauseMenu *_pPauseMenu;

	E_GAME_STATE _eState;
	CLevel *_pLevel;
	uint32 _uiLastTime;

	bool _bEndAction;
public:
	CGame(): _eState(GS_MENU), _pLevel(0), _bEndAction(false) {}
	virtual ~CGame();

    /*
    Вызывает метод Draw одного из модулей, в соответствии с состоянием игры.
    */
	virtual void CALLBACK Draw();

	/*
    Инициализирует элементы игры (создает объекты модулей меню и модуля SaveManager).
    Также загружает сохранение (см SaveManager).
    param[in] pCore - ядро.
    */
	virtual void CALLBACK Init(ICore *pCore);

	/*
    Вызывает метод Update одного из модулей, в соответствии с состоянием игры.
    Также проверяется статус завершения текущего уровня в режиме действий. Если уровень завершен - происходит вызов LoadLevel и далее запускается следующий уровень.
    param[in] uiGameTime - время с момента запуска игры в миллисекундах.
    */
	virtual void CALLBACK Update(uint32 uiGameTime);

	 /*
    Изменяет состояние (режим) игры.
    При переходе в состояние GS_LEVELS_MENU устанавливает в объекте LevelsMenu номер последнего пройденного уровня.
    При переходе в состояние GS_CARTOON устанавливает состояние GS_ACTION, если перед уровнем нет вступительного повествования.
    При переходе в состояние GS_ACTION проверяет, загружен ли уровень, если нет - состояние не меняется.
    При переходе из состояния GS_ACTION в состояние GS_MENU удаляет уровень из памяти.
    При переходе из состояния GS_CARTOON удаляет комикс из памяти.
    При переходе в другие состояния просто изменяет его, без дополнительных действий.
    param[in] eState-  состояние игры.
    */
	void CALLBACK SetState(E_GAME_STATE eState);
	
	/*
    Возвращает состояние игры
    */
	E_GAME_STATE CALLBACK GetState() const { return _eState; }

	/*
    Загружает уровень с заданным номером (модуль Level, метод Load), а также комикс для данного уровня, при его наличии.
    Возвращает true, если загрузка прошла успешно.
    */
	bool LoadLevel(int number);
};