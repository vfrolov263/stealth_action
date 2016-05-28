#include "MainMenu.h"
#include "Game.h"   

void CALLBACK CMainMenu::Init(){
	pComponentsManager->GetComponent((IComponent *&)_pBackSprite, GCT_SPRITE);            // Получаем спрайт и записываем его в указатель _pBackSprite
	pComponentsManager->GetComponent((IComponent *&)_pButtonAnim, GCT_ANIMATION);         // Получаем анимацию и записываем ее в указатель _pBackSprite
	pComponentsManager->GetComponent((IComponent *&)_pButtonСontinue, GCT_ANIMATION);    
	pComponentsManager->GetComponent((IComponent *&)_pButtonSettings, GCT_ANIMATION);     
	pComponentsManager->GetComponent((IComponent *&)_pButtonManagement, GCT_ANIMATION);   
	pComponentsManager->GetComponent((IComponent *&)_pButtonExit, GCT_ANIMATION); 

	_pBackSprite->SetTexture("data/background.png");             // Назначаем используемую спрайтом текстуру.
	
	_pButtonAnim->SetTexture("data/new_game.png");               // Назначаем используемую анимацией текстуру.
	_pButtonAnim->SetFrameSize(Vector2ui(363, 65));         // Назначаем размер одного кадра.
	_pButtonAnim->SetPosition(Vector2f(1095, 100));         // Устанавливаем позицию на экране.

	_pButtonСontinue->SetTexture("data/continue_the_game.png");  
	_pButtonСontinue->SetFrameSize(Vector2ui(363, 115));    
	_pButtonСontinue->SetPosition(Vector2f(1095, 210));     

	_pButtonSettings->SetTexture("data/settings.png");         
	_pButtonSettings->SetFrameSize(Vector2ui(363, 65));    
	_pButtonSettings->SetPosition(Vector2f(1095, 370));     

	_pButtonManagement->SetTexture("data/management.png");       
	_pButtonManagement->SetFrameSize(Vector2ui(363, 65));  
	_pButtonManagement->SetPosition(Vector2f(1095, 470));   

	_pButtonExit->SetTexture("data/exit.png");					
	_pButtonExit->SetFrameSize(Vector2ui(363, 65));        
	_pButtonExit->SetPosition(Vector2f(1095, 580));        

	pComponentsManager->GetComponent((IComponent *&)_pManagementSprite, GCT_SPRITE); 
	pComponentsManager->GetComponent((IComponent *&)_pButtonBack, GCT_ANIMATION); 

	_pManagementSprite->SetTexture("data/BackgroundOfManagement.png");

	_pButtonBack->SetTexture("data/back.png");						
	_pButtonBack->SetFrameSize(Vector2ui(327, 65));				
	_pButtonBack->SetPosition(Vector2f(1155, 750));		

	pComponentsManager->GetComponent((IComponent *&)_SettingsSprite, GCT_SPRITE);            
	pComponentsManager->GetComponent((IComponent *&)_pButtonSettingsBack, GCT_ANIMATION);        
	pComponentsManager->GetComponent((IComponent *&)_pButtonLouder, GCT_ANIMATION);    
	pComponentsManager->GetComponent((IComponent *&)_pButtonHush, GCT_ANIMATION);     
	pComponentsManager->GetComponent((IComponent *&)_pButtonFull_screen, GCT_ANIMATION);    
	pComponentsManager->GetComponent((IComponent *&)_pButtonWindow, GCT_ANIMATION);     

	_SettingsSprite->SetTexture("data/BackgroundOfSetting.png");

	_pButtonSettingsBack->SetTexture("data/back.png");						
	_pButtonSettingsBack->SetFrameSize(Vector2ui(327, 65));				
	_pButtonSettingsBack->SetPosition(Vector2f(900, 750));		

	_pButtonLouder->SetTexture("data/volume_minus.png");			
	_pButtonLouder->SetFrameSize(Vector2ui(327, 65));	
	_pButtonLouder->SetPosition(Vector2f(1200, 120));

	_pButtonHush->SetTexture("data/volume_plus.png");	
	_pButtonHush->SetFrameSize(Vector2ui(327, 65));	
	_pButtonHush->SetPosition(Vector2f(1200, 220));

	_pButtonFull_screen->SetTexture("data/full_screen.png");	
	_pButtonFull_screen->SetFrameSize(Vector2ui(360, 65));	
	_pButtonFull_screen->SetPosition(Vector2f(1190, 350));

	_pButtonWindow->SetTexture("data/window.png");	
	_pButtonWindow->SetFrameSize(Vector2ui(327, 65));	
	_pButtonWindow->SetPosition(Vector2f(1200, 450));

	_curMenu = 0;
}

CMainMenu::CMainMenu(CGame *pGame): _pGame(pGame){
	Init();								 
}

CMainMenu::~CMainMenu(){
	if (_pBackSprite)
		_pBackSprite->Release();			 //Очистка памяти от ненужного более компонента.

	if (_pButtonAnim)
		_pButtonAnim->Release();
	
	if (_pButtonСontinue)
		_pButtonСontinue->Release();

	if (_pButtonSettings)
		_pButtonSettings->Release();

	if (_pButtonManagement)
		_pButtonManagement->Release();

	if (_pButtonExit)
		_pButtonExit->Release();
}

void CALLBACK CMainMenu::Draw(){ 
	// Рисуем задний фон и кнопки.
	switch (_curMenu){
	case 0:
		_pBackSprite->Draw();
		_pButtonAnim->Draw();
		_pButtonСontinue->Draw();
		_pButtonSettings->Draw();
		_pButtonManagement->Draw();
		_pButtonExit->Draw();
		break;
	case 1:
		_SettingsSprite->Draw();	
		_pButtonSettingsBack->Draw();			
		_pButtonLouder->Draw();	
		_pButtonHush->Draw();
		_pButtonFull_screen->Draw();
		_pButtonWindow->Draw();
		break;
	case 2:
		_pManagementSprite->Draw();
		_pButtonBack->Draw();
		break;
	default:
		break;
	}
}

void CALLBACK CMainMenu::Update(){
	Vector2i mousePos = pInput->GetMousePosition();        // Позиция курсора.

	switch (_curMenu){
	case 0:
		// Проверяем пересечение курсора с кнопкой.
		if (_pButtonAnim->GetBox().IsContain(mousePos)){
			// Методу SetCurrentFrame в скобках передается номер кадра, который надо включить. (Отсчет идет с 0).
			// Если пересеклись - меняем кадр на 1.
			_pButtonAnim->SetCurrentFrame(1);

			if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON))       
				_pGame->SetState(GS_ACTION);
				//_pGame->SetState(GS_LEVELS_MENU);			  
		}
		else
			// Если нет пересечения с курсором - кадр 0.
			_pButtonAnim->SetCurrentFrame(0);
	
		if (_pButtonСontinue->GetBox().IsContain(mousePos)){
			_pButtonСontinue->SetCurrentFrame(1);
			if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON))      
				_pGame->SetState(GS_ACTION);					// Продолжаем игру		
				//_pGame->SetState(GS_LEVELS_MENU);		
		}
		else
			_pButtonСontinue->SetCurrentFrame(0);

		if (_pButtonSettings->GetBox().IsContain(mousePos)){
			_pButtonSettings->SetCurrentFrame(1);
			if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON)) 
				_curMenu = 1;									// Настройки
		}
		else
			_pButtonSettings->SetCurrentFrame(0);

		if (_pButtonManagement->GetBox().IsContain(mousePos)){
			_pButtonManagement->SetCurrentFrame(1);
			if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON))        // Управление
				_curMenu = 2;
		}
		else
			_pButtonManagement->SetCurrentFrame(0);

		if (_pButtonExit->GetBox().IsContain(mousePos)){
			_pButtonExit->SetCurrentFrame(1);
			if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON))      
				PostQuitMessage(0);								// Завершение игры	
		}
		else
			_pButtonExit->SetCurrentFrame(0);
		break;

	case 1:
		if (_pButtonSettingsBack->GetBox().IsContain(mousePos)){
			_pButtonSettingsBack->SetCurrentFrame(1);
			if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON))      
				_curMenu = 0;
		}
		else
			_pButtonSettingsBack->SetCurrentFrame(0);
		break;

	case 2:
		if (_pButtonBack->GetBox().IsContain(mousePos)){
			_pButtonBack->SetCurrentFrame(1);
			if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON))      
				_curMenu = 0;
		}
		else
			_pButtonBack->SetCurrentFrame(0);
		break;
	default:
		break;
	}
}