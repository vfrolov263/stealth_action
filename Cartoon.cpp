#include "Cartoon.h"
#include "Game.h"

void CALLBACK CCartoon::Init(OPM::cstr fileName)
{
	pComponentsManager->GetComponent((IComponent *&)_pBackSprite, GCT_SPRITE);        // �������� ������ � ���������� ��� � ��������� _pBackSprite
	pComponentsManager->GetComponent((IComponent *&)_pButtonNext, GCT_ANIMATION);      // �������� �������� � ���������� �� � ��������� _pBackEnd

	_pBackSprite->SetTexture(fileName);   // ��������� ������������ �������� ��������.
	
	_pButtonNext->SetTexture("end.png");             // ��������� ������������ ��������� ��������.
	_pButtonNext->SetFrameSize(Vector2ui(468, 70));  // ��������� ������ ������ �����.
	//_pButtonEnd->Rotate(15);
	_pButtonNext->SetPosition(Vector2f(100, 300));   // ������������� ������� �� ������.
}

CCartoon::CCartoon(int levelNumber)
{
	frameNumber = 0;

	switch(levelNumber) {
	case 0:
		fileName[0] = "back.png";
		fileName[1] = "new.png";
		fileName[2] = "back.png";
		countFrame = 3;
		break;
	case 1:
		fileName[0] = "back.png";
		fileName[1] = "new.png";
		countFrame = 2;
		break;
	case 2:
		fileName[0] = "back.png";
		countFrame = 1;
		break;
	default:
		break;
	}

	Init(fileName[frameNumber]);
}

CCartoon::~CCartoon()
{
	if (_pBackSprite)
		_pBackSprite->Release();

	if (_pButtonNext)
		_pButtonNext->Release();
}

void CALLBACK CCartoon::Draw()
{ 
	_pBackSprite->Draw();
	_pButtonNext->Draw();
}

void CALLBACK CCartoon::Update()
{
	Vector2i mousePos = pInput->GetMousePosition();

	if (_pButtonNext->GetBox().IsContain(mousePos))       
	{
		_pButtonNext->SetCurrentFrame(1);

		if (pInput->IsKeyHit(KEY_LEFT_MOUSE_BUTTON))
			if(countFrame - 1 == frameNumber) {
				_pGame->SetState(GS_ACTION);
			} else {
				frameNumber++;
				Init(fileName[frameNumber]);
				Draw();
			}
	}
	else
		_pButtonNext->SetCurrentFrame(0);
}