#pragma once
#include <Game.h>
#include "Level.h"
#include "Cartoon.h"

enum E_GAME_STATE
{
	GS_MENU,
	GS_RESTART,
	GS_PAUSE,
	GS_ACTION,
};

class CGame: public IGame
{
	CCartoon *_pRestartMenu;          

	E_GAME_STATE _eState;
	CLevel *_pLevel;
	uint32 _uiLastTime;
public:
	CGame(): _eState(GS_MENU), _pLevel(0) {}
	virtual ~CGame();

    /*
    ¬ызывает метод Draw одного из модулей, в соответствии с состо€нием игры.
    */
	virtual void CALLBACK Draw();

	/*
    »нициализирует элементы игры (создает объекты модулей меню и модул€ SaveManager).
    “акже загружает сохранение (см SaveManager).
    param[in] pCore - €дро.
    */
	virtual void CALLBACK Init(ICore *pCore);

	/*
    ¬ызывает метод Update одного из модулей, в соответствии с состо€нием игры.
    “акже провер€етс€ статус завершени€ текущего уровн€ в режиме действий. ≈сли уровень завершен - происходит вызов LoadLevel и далее запускаетс€ следующий уровень.
    param[in] uiGameTime - врем€ с момента запуска игры в миллисекундах.
    */
	virtual void CALLBACK Update(uint32 uiGameTime);

	 /*
    »змен€ет состо€ние (режим) игры.
    ѕри переходе в состо€ние GS_LEVELS_MENU устанавливает в объекте LevelsMenu номер последнего пройденного уровн€.
    ѕри переходе в состо€ние GS_CARTOON устанавливает состо€ние GS_ACTION, если перед уровнем нет вступительного повествовани€.
    ѕри переходе в состо€ние GS_ACTION провер€ет, загружен ли уровень, если нет - состо€ние не мен€етс€.
    ѕри переходе из состо€ни€ GS_ACTION в состо€ние GS_MENU удал€ет уровень из пам€ти.
    ѕри переходе из состо€ни€ GS_CARTOON удал€ет комикс из пам€ти.
    ѕри переходе в другие состо€ни€ просто измен€ет его, без дополнительных действий.
    param[in] eState-  состо€ние игры.
    */
	void CALLBACK SetState(E_GAME_STATE eState);
	
	/*
    ¬озвращает состо€ние игры
    */
	E_GAME_STATE CALLBACK GetState() const { return _eState; }

	/*
    «агружает уровень с заданным номером (модуль Level, метод Load), а также комикс дл€ данного уровн€, при его наличии.
    ¬озвращает true, если загрузка прошла успешно.
    */
	bool LoadLevel(int number);
};