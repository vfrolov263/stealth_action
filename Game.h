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
	CMainMenu *_pMainMenu;           // ��� ���� ������� ����.
	CRestartMenu *_pRestartMenu;
	�PauseMenu *_pPauseMenu;

	E_GAME_STATE _eState;
	CLevel *_pLevel;
	uint32 _uiLastTime;

	bool _bEndAction;
public:
	CGame(): _eState(GS_MENU), _pLevel(0), _bEndAction(false) {}
	virtual ~CGame();

    /*
    �������� ����� Draw ������ �� �������, � ������������ � ���������� ����.
    */
	virtual void CALLBACK Draw();

	/*
    �������������� �������� ���� (������� ������� ������� ���� � ������ SaveManager).
    ����� ��������� ���������� (�� SaveManager).
    param[in] pCore - ����.
    */
	virtual void CALLBACK Init(ICore *pCore);

	/*
    �������� ����� Update ������ �� �������, � ������������ � ���������� ����.
    ����� ����������� ������ ���������� �������� ������ � ������ ��������. ���� ������� �������� - ���������� ����� LoadLevel � ����� ����������� ��������� �������.
    param[in] uiGameTime - ����� � ������� ������� ���� � �������������.
    */
	virtual void CALLBACK Update(uint32 uiGameTime);

	 /*
    �������� ��������� (�����) ����.
    ��� �������� � ��������� GS_LEVELS_MENU ������������� � ������� LevelsMenu ����� ���������� ����������� ������.
    ��� �������� � ��������� GS_CARTOON ������������� ��������� GS_ACTION, ���� ����� ������� ��� �������������� �������������.
    ��� �������� � ��������� GS_ACTION ���������, �������� �� �������, ���� ��� - ��������� �� ��������.
    ��� �������� �� ��������� GS_ACTION � ��������� GS_MENU ������� ������� �� ������.
    ��� �������� �� ��������� GS_CARTOON ������� ������ �� ������.
    ��� �������� � ������ ��������� ������ �������� ���, ��� �������������� ��������.
    param[in] eState-  ��������� ����.
    */
	void CALLBACK SetState(E_GAME_STATE eState);
	
	/*
    ���������� ��������� ����
    */
	E_GAME_STATE CALLBACK GetState() const { return _eState; }

	/*
    ��������� ������� � �������� ������� (������ Level, ����� Load), � ����� ������ ��� ������� ������, ��� ��� �������.
    ���������� true, ���� �������� ������ �������.
    */
	bool LoadLevel(int number);
};