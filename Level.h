#pragma once
#include "Modules.h"
#include "Player.h"
#include "Enemy.h"
#include "Trap.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using std::string;
using std::ifstream;
using std::vector;

#define MAX_LINE			255
#define MAX_PARAM_LENGTH	128

class CGame;

extern ISprite *pFinishSpr;

class CLevel
{
	CPlayer *_pPlayer;
	vector <CEnemy *> _enemiesVect;
	multiset<Vector2f> _objects;
	vector <CTrap *> _trapsVect;
	Vector2i _finish;
	CGame *_pGame;
	
	Vector2i _levSize;
	vector<IAnimation *> _animsVect;
	vector<ISprite *> _tilesZeroVect, _tilesOneVect, _tilesTwoVect;
	bool **_collMap;
	void CALLBACK GetLevelParam(string &stringLevLine, cstr cstrParamName, str strParam);
	void CALLBACK AddTile(int iLayerNum, uint uiFrameNum, Vector2f &position);
	void CALLBACK InitVisibility();

public:
	CLevel(CGame *pGame);
	~CLevel();

	/*
    Перемещает все объекты. Проверяет попадание игрока в поле видимости противников.
    Проверяет пересечение ловушки с игроком и противниками. При попадании противника в ловушку - он погибает.
    При попадании игрока в поле видимости или ловушку - переводит игру в состояние GS_RESTART.
    param1[in] dt - время с последнего обновления (в секундах).
    */
	void CALLBACK Update(float fTime);

	/* 
    Рисует все объекты.
    */
	void CALLBACK Draw();

	/*
    Загружает уровень с заданным номером. 
    param1[in] number - номер уровня.
    Возвращает true при успешной загрузке.
    */
	bool CALLBACK Load(int iNumber);

	bool CALLBACK IsFreeCell(const Vector2f &position);
};