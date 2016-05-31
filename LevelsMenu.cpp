#include <string>
#include "MainMenu.h"
#include "Game.h"

void CALLBACK CMainMenu::Init()
{
	pComponentsManager->GetComponent((IComponent *&)_pBackSprite, GCT_SPRITE);        // �������� ������ � ���������� ��� � ��������� _pBackSprite
	for (int i = 0; i < levels_number; i++)
		pComponentsManager->GetComponent((IComponent *&)buttons[i], GCT_ANIMATION);

	_pBackSprite->SetTexture("background.png");             // ��������� ������������ �������� �������� (��� ��������� � ����� Game, ���� �� ������ ������ ���� ��������, ���� ������� ��� ��������, ��� ���� �������).

	buttons[0]->SetTexture("derevnya.png");
	buttons[0]->SetFrameSize(Vector2ui(364, 337));
	buttons[0]->SetPosition(Vector2f(700, 200));

	buttons[1]->SetTexture("les.png");
	buttons[1]->SetFrameSize(Vector2ui(364, 337));
	buttons[1]->SetPosition(Vector2f(450, 500));

	buttons[2]->SetTexture("mini-boss.png");
	buttons[2]->SetFrameSize(Vector2ui(364, 337));
	buttons[2]->SetPosition(Vector2f(100, 350));

	buttons[3]->SetTexture("pezchera.png");
	buttons[3]->SetFrameSize(Vector2ui(364, 337));
	buttons[3]->SetPosition(Vector2f(280, 50));

	buttons[4]->SetTexture("reka.png");
	buttons[4]->SetFrameSize(Vector2ui(364, 337));
	buttons[4]->SetPosition(Vector2f(1100, 350));

	buttons[5]->SetTexture("super-boss.png");
	buttons[5]->SetFrameSize(Vector2ui(364, 337));
	buttons[5]->SetPosition(Vector2f(850, 550));

	buttons[6]->SetTexture("uzchel'e.png");
	buttons[6]->SetFrameSize(Vector2ui(364, 337));
	buttons[6]->SetPosition(Vector2f(1100, 40));
}

CMainMenu::CMainMenu(CGame *pGame): _pGame(pGame), _lastLevel(0)
{
	Init(); // ��� �������� ������� ���� �������� ����� Init, � ������� ����������� �������� � ��������.
}

CMainMenu::~CMainMenu()
{
	if (_pBackSprite)
		_pBackSprite->Release();     // ��� ��������� ������ �� ��������� ����� ���������� (�� � ���� ������ ������ ������ ��� ������� delete _pBackSprite!!!).

	
}

void CALLBACK CMainMenu::Draw()
{ 
	// ������ ������ ��� � ������.
	_pBackSprite->Draw();
	for (int i = 0; i < levels_number; i++)
		buttons[i]->Draw();

}

void CALLBACK CMainMenu::Update()
{
	Vector2i mousePos = pInput->GetMousePosition(); // ������� �������.

	// ��������� ����������� ������� � �������.
	if (buttons[0]->GetBox().IsContain(mousePos))       
	{
		// ������ SetCurrentFrame � ������� ���������� ����� �����, ������� ���� ��������. (������ ���� � 0).
		// ���� ����������� - ������ ���� �� 1.
		buttons[0]->SetCurrentFrame(1);

		if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON))       // ���� ��������
		{
			_pGame->LoadLevel(0); //!!!����� ������ - � ����������� �� ������
			_pGame->SetState(GS_ACTION);				// ��������� � �����-������ ��������� (����� ����� ��������, ����� ����� ����� ������ ���� ������ ������� �� � ����� ������ ������ ��������).
			//!!!��� �� ����������� ��� ������ ������ �������
		}
	}
	else
		// ���� ��� ����������� � �������� - ���� 0.
		buttons[0]->SetCurrentFrame(0);

	// ����� ����� ������������ ��������� ���������� - pInput->IsKeyHit(KEY_D) - �������� ������� ������� D � �. �. ������ ������ � ����� include/Input.h
}