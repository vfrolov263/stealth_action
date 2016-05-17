#include "Player.h"
#include "GameFiles.h"
#include "GameSettings.h"
#include "GameKeys.h"
#include "Level.h"

CPlayer::CPlayer(CLevel *pLevel): _position(PLAYER_START_POSITION), _nextPosition(_position), _pLevel(pLevel)
{
	IAnimation *pAnim = 0;
	AddAnimation(pAnim, PAI_WALK_UP);
	pAnim->SetTexture(TEXTURE_PLAYER_NAME);
	pAnim->SetFrameSize(Vector2ui(PAP_FRAME_WIDTH, PAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(PAP_WALK_UP_FIRST);
	pAnim->SetLastFrame(PAP_WALK_UP_LAST);
	pAnim->SetDelayTime(PAP_DELAY);

	AddAnimation(pAnim, PAI_STAND_UP);
	pAnim->SetTexture(TEXTURE_PLAYER_NAME);
	pAnim->SetFrameSize(Vector2ui(PAP_FRAME_WIDTH, PAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(PAP_STAND_UP_FIRST);
	pAnim->SetLastFrame(PAP_STAND_UP_LAST);
	pAnim->SetDelayTime(PAP_DELAY);

	AddAnimation(pAnim, PAI_WALK_DOWN);
	pAnim->SetTexture(TEXTURE_PLAYER_NAME);
	pAnim->SetFrameSize(Vector2ui(PAP_FRAME_WIDTH, PAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(PAP_WALK_DOWN_FIRST);
	pAnim->SetLastFrame(PAP_WALK_DOWN_LAST);
	pAnim->SetDelayTime(PAP_DELAY);

	AddAnimation(pAnim, PAI_STAND_DOWN);
	pAnim->SetTexture(TEXTURE_PLAYER_NAME);
	pAnim->SetFrameSize(Vector2ui(PAP_FRAME_WIDTH, PAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(PAP_STAND_DOWN_FIRST);
	pAnim->SetLastFrame(PAP_STAND_DOWN_LAST);
	pAnim->SetDelayTime(PAP_DELAY);

	AddAnimation(pAnim, PAI_WALK_RIGHT);
	pAnim->SetTexture(TEXTURE_PLAYER_NAME);
	pAnim->SetFrameSize(Vector2ui(PAP_FRAME_WIDTH, PAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(PAP_WALK_RIGHT_FIRST);
	pAnim->SetLastFrame(PAP_WALK_RIGHT_LAST);
	pAnim->SetDelayTime(PAP_DELAY);

	AddAnimation(pAnim, PAI_STAND_RIGHT);
	pAnim->SetTexture(TEXTURE_PLAYER_NAME);
	pAnim->SetFrameSize(Vector2ui(PAP_FRAME_WIDTH, PAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(PAP_STAND_RIGHT_FIRST);
	pAnim->SetLastFrame(PAP_STAND_RIGHT_LAST);
	pAnim->SetDelayTime(PAP_DELAY);

	AddAnimation(pAnim, PAI_WALK_LEFT);
	pAnim->SetTexture(TEXTURE_PLAYER_NAME);
	pAnim->SetFrameSize(Vector2ui(PAP_FRAME_WIDTH, PAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(PAP_WALK_LEFT_FIRST);
	pAnim->SetLastFrame(PAP_WALK_LEFT_LAST);
	pAnim->SetDelayTime(PAP_DELAY);

	AddAnimation(pAnim, PAI_STAND_LEFT);
	pAnim->SetTexture(TEXTURE_PLAYER_NAME);
	pAnim->SetFrameSize(Vector2ui(PAP_FRAME_WIDTH, PAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(PAP_STAND_LEFT_FIRST);
	pAnim->SetLastFrame(PAP_STAND_LEFT_LAST);
	pAnim->SetDelayTime(PAP_DELAY);

	_pCurrAnim = _animationsMap.at(PAI_STAND_RIGHT);
	_eState = PS_STAND_RIGHT;

	_nextPosition = _position;

	//_pCurrAnim->SetFrameSize(Vector2f(128.0f, 256.0f));
}

void CALLBACK CPlayer::Stand()
{
	_position = _nextPosition;
	_eState = (E_PLAYER_STATE)(_eState + PS_STAND_UP);
	_pCurrAnim = _animationsMap.at(PAI_STAND_UP + (_eState - PS_STAND_UP));
}

void CALLBACK CPlayer::Move(float fTime)
{
	float fDist = fTime * PLAYER_SPEED;

	if (_position.x < _nextPosition.x)
	{
		_position.x += fDist;

		if (_position.x >= _nextPosition.x)
			Stand();
	}
	else if (_position.x > _nextPosition.x)
	{
		_position.x -= fDist;

		if (_position.x <= _nextPosition.x)
			Stand();
	}
	else if (_position.y < _nextPosition.y)
	{
		_position.y += fDist;

		if (_position.y >= _nextPosition.y)
			Stand();
	}
	else if (_position.y > _nextPosition.y)
	{
		_position.y -= fDist;

		if (_position.y <= _nextPosition.y)
			Stand();
	}
}

void CALLBACK CPlayer::MoveCommand()
{
	if (pInput->IsKeyDown(GK_UP))
	{
		_nextPosition.y = _position.y - TILE_SIZE;

		if (_pLevel->IsFreeCell(_nextPosition))
		{
			_eState = PS_WALK_UP;
			_pCurrAnim = _animationsMap.at(PAI_WALK_UP);
		}
		else
		{
			_nextPosition.y = _position.y;
			_pCurrAnim = _animationsMap.at(PAI_STAND_UP);
		}

	}
	else if (pInput->IsKeyDown(GK_DOWN))
	{
		_nextPosition.y = _position.y + TILE_SIZE;

		if (_pLevel->IsFreeCell(_nextPosition))
		{
			_eState = PS_WALK_DOWN;
			_pCurrAnim = _animationsMap.at(PAI_WALK_DOWN);
		}
		else
		{
			_nextPosition.y = _position.y;
			_pCurrAnim = _animationsMap.at(PAI_STAND_DOWN);
		}
	}
	else if (pInput->IsKeyDown(GK_RIGHT))
	{
		_nextPosition.x = _position.x + TILE_SIZE;

		if (_pLevel->IsFreeCell(_nextPosition))
		{
			_pCurrAnim = _animationsMap.at(PAI_WALK_RIGHT);
			_eState = PS_WALK_RIGHT;
		}
		else
		{
			_nextPosition.x = _position.x;
			_pCurrAnim = _animationsMap.at(PAI_STAND_RIGHT);
		}
	}
	else if (pInput->IsKeyDown(GK_LEFT))
	{
		_nextPosition.x = _position.x - TILE_SIZE;

		if (_pLevel->IsFreeCell(_nextPosition))
		{
			_pCurrAnim = _animationsMap.at(PAI_WALK_LEFT);
			_eState = PS_WALK_LEFT;
		}
		else
		{
			_nextPosition.x = _position.x;
			_pCurrAnim = _animationsMap.at(PAI_STAND_LEFT);
		}
	}
}

void CALLBACK CPlayer::Update(float fTime)
{
	// Если игрок уже отдал команду на перемещение.
	if (_eState < PS_STAND_UP)
		Move(fTime);
	
	// Если игрок стоит на месте - проверяем нажатие клавиш для начала движения.
	if (_eState >= PS_STAND_UP)
		MoveCommand();

	_pCurrAnim->SetPosition(Vector2f(_position.x + 4, _position.y - 16));
	_pCurrAnim->Play(fTime);

	//if (pInput->Is
}

void CALLBACK CPlayer::SetPosition(Vector2f &position)
{
	_position = position;
	_nextPosition = position;
}

void CALLBACK CPlayer::Draw()
{
	_pCurrAnim->Draw();
}