#include "PauseMenu.h"
#include "Game.h"   
void CALLBACK СPauseMenu::Init(){
	pComponentsManager->GetComponent((IComponent *&)_pBackPauseSprite, GCT_SPRITE); 
	pComponentsManager->GetComponent((IComponent *&)_pButtonReturn, GCT_ANIMATION); 
	pComponentsManager->GetComponent((IComponent *&)_pButtonUnknow, GCT_ANIMATION); 

	_pBackPauseSprite->SetTexture("data/BackgroundOfPause.png");             // Назначаем используемую спрайтом текстуру.
	_pButtonReturn->SetTexture("data/return_to_the_game.png");               // Назначаем используемую анимацией текстуру.
	_pButtonReturn->SetFrameSize(Vector2ui(410, 65));         // Назначаем размер одного кадра.
	_pButtonReturn->SetPosition(Vector2f(1095, 90));         // Устанавливаем позицию на экране.

	_pButtonUnknow->SetTexture("data/to_finish_the_game.png");  
	_pButtonUnknow->SetFrameSize(Vector2ui(410, 65));    
	_pButtonUnknow->SetPosition(Vector2f(1109, 210));     
}

СPauseMenu::СPauseMenu(CGame *pGame): _pGame(pGame){
	Init();								 
}

СPauseMenu::~СPauseMenu(){
	if (_pBackPauseSprite)						//Очистка памяти от ненужного более компонента.
		_pBackPauseSprite->Release();

	if (_pButtonReturn)
		_pButtonReturn->Release();	

	if (_pButtonUnknow)
		_pButtonUnknow->Release();
}

void CALLBACK СPauseMenu::Draw(){
	_pBackPauseSprite->Draw();
	_pButtonReturn->Draw();
	_pButtonUnknow->Draw();
}

void CALLBACK СPauseMenu::Update(){
	Vector2i mousePos = pInput->GetMousePosition();        // Позиция курсора.

	// Проверяем пересечение курсора с кнопкой.
	if (_pButtonReturn->GetBox().IsContain(mousePos)){
		// Методу SetCurrentFrame в скобках передается номер кадра, который надо включить. (Отсчет идет с 0).
		// Если пересеклись - меняем кадр на 1.
		_pButtonReturn->SetCurrentFrame(1);

		if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON))       
			_pGame->SetState(GS_ACTION);							// Продолжение игры
	}
	else
		// Если нет пересечения с курсором - кадр 0.
		_pButtonReturn->SetCurrentFrame(0);

	if (_pButtonUnknow->GetBox().IsContain(mousePos)){
		_pButtonUnknow->SetCurrentFrame(1);
		if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON))      
			_pGame->SetState(GS_MENU);								// Возвращение в главное меню
	}
	else
		_pButtonUnknow->SetCurrentFrame(0);
}