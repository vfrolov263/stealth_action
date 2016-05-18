#include "Game.h"
#include "Modules.h"
#include "GameKeys.h"
#include "Level.h"
#include "GameFiles.h"

IComponentsManager *pComponentsManager = 0;
IInput *pInput = 0;
ISprite *pVisibSpr = 0;
ISprite *pFinishSpr = 0;

CGame::~CGame()
{
	if (_pLevel)
		delete _pLevel;

	if (_pMainMenu)
		delete _pMainMenu;

	if (_pRestartMenu)
		delete _pRestartMenu;

	if (_pPauseMenu)
		delete _pPauseMenu;
}

void CALLBACK CGame::Init(ICore *pCore)
{
	pCore->GetCurrentModule((IModule *&)pComponentsManager, EMT_COMPONENTS_MANAGER);
	pCore->GetCurrentModule((IModule *&)pInput, EMT_INPUT);

	pComponentsManager->GetComponent((IComponent *&)pVisibSpr, GCT_SPRITE);
	pVisibSpr->SetTexture(TEXTURE_VISIBILITY);
	
	pComponentsManager->GetComponent((IComponent *&)pFinishSpr, GCT_SPRITE);
	pFinishSpr->SetTexture(TEXTURE_FINISH);

	SetState(GS_MENU);
	/*
	Здесь будет загрузка менюшек
	*/

	_pMainMenu = new CMainMenu(this);       // Создание главного меню при запуске игры.
	_pRestartMenu = new CRestartMenu(this);
	_pPauseMenu = new СPauseMenu(this);
}

void CALLBACK CGame::Update(uint32 uiGameTime)
{
	float fTime = uiGameTime / 1000.0f;
	//_uiLastTime = uiGameTime;

	// fTime - время с последнего обновления в секундах.

	if (_bEndAction)
	{
		if (_pLevel)
			delete _pLevel;

		_eState = GS_RESTART; 
		_bEndAction = false;
	}

	switch (_eState)
	{
	case GS_MENU:
		_pMainMenu->Update();             // Обновление меню.
		break;
	case GS_PAUSE:
		_pPauseMenu->Update();
		break;
	case GS_RESTART:
		_pRestartMenu->Update();
		break;
	case GS_ACTION:
		_pLevel->Update(fTime);
		break;

		/*
		Здесь будут остальные состояния.
		*/

	default:
		break;
	}
}

void CALLBACK CGame::Draw()
{
	switch (_eState)
	{
	case GS_MENU:
		_pMainMenu->Draw();               // Прорисовка меню.
		break;
	case GS_PAUSE:
		_pPauseMenu->Draw();
		break;
	case GS_RESTART:
		_pRestartMenu->Draw();
		break;
	case GS_ACTION:
		_pLevel->Draw();

		/*
		Здесь будут остальные состояния.
		*/

	default:
		break;
	}
}

void CALLBACK CGame::SetState(E_GAME_STATE eState)
{
	/*
	Здесь будут проверки (например, при выходе из состояния GS_ACTION необходимо удалить _pLevel из памяти).
	*/

	if (eState == GS_ACTION && (_eState != GS_PAUSE && _eState != eState))
		LoadLevel(0);

	else if (_eState == GS_ACTION && eState != GS_PAUSE)
		_bEndAction = true;

	_eState = eState;
}

bool CGame::LoadLevel(int number)
{
	_pLevel = new CLevel(this);
	_pLevel->Load(number);

	/*
	Здесь будет загрузка комикса для данного уровня.
	*/

	return true;
}