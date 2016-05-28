#include "RestartMenu.h"
#include "Game.h"

void CALLBACK CRestartMenu::Init()
{
	pComponentsManager->GetComponent((IComponent *&)_pBackSprite, GCT_SPRITE);        // �������� ������ � ���������� ��� � ��������� _pBackSprite
	pComponentsManager->GetComponent((IComponent *&)_pButtonEnd, GCT_ANIMATION);      // �������� �������� � ���������� �� � ��������� _pBackEnd
	pComponentsManager->GetComponent((IComponent *&)_pButtonNew, GCT_ANIMATION);	  // �������� �������� � ���������� �� � ��������� _pBackNew

	_pBackSprite->SetTexture("data/rest_back.png");   // ��������� ������������ �������� ��������.
	
	_pButtonEnd->SetTexture("data/rest_end.png");             // ��������� ������������ ��������� ��������.
	_pButtonEnd->SetFrameSize(Vector2ui(468, 70));  // ��������� ������ ������ �����.
	//_pButtonEnd->Rotate(15);
	_pButtonEnd->SetPosition(Vector2f(30, 300));   // ������������� ������� �� ������.

	_pButtonNew->SetTexture("data/rest_new.png");             // ��������� ������������ ��������� ��������.
	_pButtonNew->SetFrameSize(Vector2ui(425, 80));  // ��������� ������ ������ �����.
	//_pButtonNew->Rotate(15);
	_pButtonNew->SetPosition(Vector2f(30, 500));   // ������������� ������� �� ������.
}

CRestartMenu::CRestartMenu(CGame *pGame): _pGame(pGame)
{
	Init();
}

CRestartMenu::~CRestartMenu()
{
	if (_pBackSprite)
		_pBackSprite->Release();

	if (_pButtonEnd)
		_pButtonEnd->Release();

	if (_pButtonNew)
		_pButtonNew->Release();
}

void CALLBACK CRestartMenu::Draw()
{ 
	_pBackSprite->Draw();
	_pButtonEnd->Draw();
	_pButtonNew->Draw();
}

void CALLBACK CRestartMenu::Update()
{
	Vector2i mousePos = pInput->GetMousePosition();

	if (_pButtonEnd->GetBox().IsContain(mousePos))       
	{
		_pButtonEnd->SetCurrentFrame(1);

		if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON))
			_pGame->SetState(GS_MENU);
	}
	else
		_pButtonEnd->SetCurrentFrame(0);


	if (_pButtonNew->GetBox().IsContain(mousePos))       
	{
		_pButtonNew->SetCurrentFrame(1);

		if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON))
			_pGame->SetState(GS_ACTION);
	}
	else
		_pButtonNew->SetCurrentFrame(0);
	
}