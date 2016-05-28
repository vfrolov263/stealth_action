#include "PauseMenu.h"
#include "Game.h"   
void CALLBACK �PauseMenu::Init(){
	pComponentsManager->GetComponent((IComponent *&)_pBackPauseSprite, GCT_SPRITE); 
	pComponentsManager->GetComponent((IComponent *&)_pButtonReturn, GCT_ANIMATION); 
	pComponentsManager->GetComponent((IComponent *&)_pButtonUnknow, GCT_ANIMATION); 

	_pBackPauseSprite->SetTexture("data/BackgroundOfPause.png");             // ��������� ������������ �������� ��������.
	_pButtonReturn->SetTexture("data/return_to_the_game.png");               // ��������� ������������ ��������� ��������.
	_pButtonReturn->SetFrameSize(Vector2ui(410, 65));         // ��������� ������ ������ �����.
	_pButtonReturn->SetPosition(Vector2f(1095, 90));         // ������������� ������� �� ������.

	_pButtonUnknow->SetTexture("data/to_finish_the_game.png");  
	_pButtonUnknow->SetFrameSize(Vector2ui(410, 65));    
	_pButtonUnknow->SetPosition(Vector2f(1109, 210));     
}

�PauseMenu::�PauseMenu(CGame *pGame): _pGame(pGame){
	Init();								 
}

�PauseMenu::~�PauseMenu(){
	if (_pBackPauseSprite)						//������� ������ �� ��������� ����� ����������.
		_pBackPauseSprite->Release();

	if (_pButtonReturn)
		_pButtonReturn->Release();	

	if (_pButtonUnknow)
		_pButtonUnknow->Release();
}

void CALLBACK �PauseMenu::Draw(){
	_pBackPauseSprite->Draw();
	_pButtonReturn->Draw();
	_pButtonUnknow->Draw();
}

void CALLBACK �PauseMenu::Update(){
	Vector2i mousePos = pInput->GetMousePosition();        // ������� �������.

	// ��������� ����������� ������� � �������.
	if (_pButtonReturn->GetBox().IsContain(mousePos)){
		// ������ SetCurrentFrame � ������� ���������� ����� �����, ������� ���� ��������. (������ ���� � 0).
		// ���� ����������� - ������ ���� �� 1.
		_pButtonReturn->SetCurrentFrame(1);

		if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON))       
			_pGame->SetState(GS_ACTION);							// ����������� ����
	}
	else
		// ���� ��� ����������� � �������� - ���� 0.
		_pButtonReturn->SetCurrentFrame(0);

	if (_pButtonUnknow->GetBox().IsContain(mousePos)){
		_pButtonUnknow->SetCurrentFrame(1);
		if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON))      
			_pGame->SetState(GS_MENU);								// ����������� � ������� ����
	}
	else
		_pButtonUnknow->SetCurrentFrame(0);
}