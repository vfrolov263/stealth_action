#include "Trap.h"
#include "GameFiles.h"
#include "GameSettings.h"
#include "GameKeys.h"
#include "Level.h"

CTrap::CTrap(const Vector2f &position, CLevel *pLevel): _position(position), _nextPosition(_position), _pLevel(pLevel)
{
	IAnimation *pAnim = 0;
	AddAnimation(pAnim, TAI_WALK_UP);
	pAnim->SetTexture(TEXTURE_TRAP_NAME);
	pAnim->SetFrameSize(Vector2ui(TAP_FRAME_WIDTH, TAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(TAP_WALK_UP_FIRST);
	pAnim->SetLastFrame(TAP_WALK_UP_LAST);
	pAnim->SetDelayTime(TAP_DELAY);

	AddAnimation(pAnim, TAI_STAND_UP);
	pAnim->SetTexture(TEXTURE_TRAP_NAME);
	pAnim->SetFrameSize(Vector2ui(TAP_FRAME_WIDTH, TAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(TAP_STAND_UP_FIRST);
	pAnim->SetLastFrame(TAP_STAND_UP_LAST);
	pAnim->SetDelayTime(TAP_DELAY);

	AddAnimation(pAnim, TAI_WALK_DOWN);
	pAnim->SetTexture(TEXTURE_TRAP_NAME);
	pAnim->SetFrameSize(Vector2ui(TAP_FRAME_WIDTH, TAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(TAP_WALK_DOWN_FIRST);
	pAnim->SetLastFrame(TAP_WALK_DOWN_LAST);
	pAnim->SetDelayTime(TAP_DELAY);

	AddAnimation(pAnim, TAI_STAND_DOWN);
	pAnim->SetTexture(TEXTURE_TRAP_NAME);
	pAnim->SetFrameSize(Vector2ui(TAP_FRAME_WIDTH, TAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(TAP_STAND_DOWN_FIRST);
	pAnim->SetLastFrame(TAP_STAND_DOWN_LAST);
	pAnim->SetDelayTime(TAP_DELAY);

	AddAnimation(pAnim, TAI_WALK_RIGHT);
	pAnim->SetTexture(TEXTURE_TRAP_NAME);
	pAnim->SetFrameSize(Vector2ui(TAP_FRAME_WIDTH, TAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(TAP_WALK_RIGHT_FIRST);
	pAnim->SetLastFrame(TAP_WALK_RIGHT_LAST);
	pAnim->SetDelayTime(TAP_DELAY);

	AddAnimation(pAnim, TAI_STAND_RIGHT);
	pAnim->SetTexture(TEXTURE_TRAP_NAME);
	pAnim->SetFrameSize(Vector2ui(TAP_FRAME_WIDTH, TAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(TAP_STAND_RIGHT_FIRST);
	pAnim->SetLastFrame(TAP_STAND_RIGHT_LAST);
	pAnim->SetDelayTime(TAP_DELAY);

	AddAnimation(pAnim, TAI_WALK_LEFT);
	pAnim->SetTexture(TEXTURE_TRAP_NAME);
	pAnim->SetFrameSize(Vector2ui(TAP_FRAME_WIDTH, TAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(TAP_WALK_LEFT_FIRST);
	pAnim->SetLastFrame(TAP_WALK_LEFT_LAST);
	pAnim->SetDelayTime(TAP_DELAY);

	AddAnimation(pAnim, TAI_STAND_LEFT);
	pAnim->SetTexture(TEXTURE_TRAP_NAME);
	pAnim->SetFrameSize(Vector2ui(TAP_FRAME_WIDTH, TAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(TAP_STAND_LEFT_FIRST);
	pAnim->SetLastFrame(TAP_STAND_LEFT_LAST);
	pAnim->SetDelayTime(TAP_DELAY);

	_pCurrAnim = _animationsMap.at(TAI_STAND_RIGHT);
	_eState = TS_STAND_RIGHT;

	_nextPosition = _position;

	//_pCurrAnim->SetFrameSize(Vector2f(128.0f, 256.0f));
}

void CALLBACK CTrap::Stand()
{
	_position = _nextPosition;
	_eState = (E_TRAP_STATE)(_eState + TS_STAND_UP);
	_pCurrAnim = _animationsMap.at(TAI_STAND_UP + (_eState - TS_STAND_UP));
}

void CALLBACK CTrap::Move(float fTime)
{
	float fDist = fTime * TRAP_SPEED;

	if (_position.x < _nextPosition.x)
	{
		_position.x += fDist;

		if (_position.x >= _nextPosition.x)
			MoveNext();
	}
	else if (_position.x > _nextPosition.x)
	{
		_position.x -= fDist;

		if (_position.x <= _nextPosition.x)
			MoveNext();
	}
	else if (_position.y < _nextPosition.y)
	{
		_position.y += fDist;

		if (_position.y >= _nextPosition.y)
			MoveNext();
	}
	else if (_position.y > _nextPosition.y)
	{
		_position.y -= fDist;

		if (_position.y <= _nextPosition.y)
			MoveNext();
	}
}

void CALLBACK CTrap::MoveNext()
{
	_position = _nextPosition;

	if (_eState == TS_WALK_UP)
	{
		_nextPosition.y = _position.y - TILE_SIZE;

		if (_pLevel->IsFreeCell(_nextPosition))
		{
			return;
		}
		else
		{
			_nextPosition.y = _position.y;
			Stand();
		}

	}
	else if (_eState == TS_WALK_DOWN)
	{
		_nextPosition.y = _position.y + TILE_SIZE;

		if (_pLevel->IsFreeCell(_nextPosition))
		{
			return;
		}
		else
		{
			_nextPosition.y = _position.y;
			Stand();
		}
	}
	else if (_eState == TS_WALK_RIGHT)
	{
		_nextPosition.x = _position.x + TILE_SIZE;

		if (_pLevel->IsFreeCell(_nextPosition))
		{
			return;
		}
		else
		{
			_nextPosition.x = _position.x;
			Stand();
		}
	}
	else if (_eState == TS_WALK_LEFT)
	{
		_nextPosition.x = _position.x - TILE_SIZE;

		if (_pLevel->IsFreeCell(_nextPosition))
		{
			return;
		}
		else
		{
			_nextPosition.x = _position.x;
			Stand();
		}
	}
}

void CALLBACK CTrap::ActiveTrap(Vector2f playerNextPosition, Vector2f playerPosition)
{
	if (_eState >= ES_STAND_UP && playerNextPosition == _nextPosition)
		if (playerPosition.x < _nextPosition.x)
		{
			_nextPosition.x = _position.x + TILE_SIZE;

			if (_pLevel->IsFreeCell(_nextPosition))
			{
				_pCurrAnim = _animationsMap.at(TAI_WALK_RIGHT);
				_eState = TS_WALK_RIGHT;
			}
			else
			{
				_nextPosition.x = _position.x;
				_pCurrAnim = _animationsMap.at(TAI_STAND_RIGHT);
			}
		}
		else if (playerPosition.x > _nextPosition.x)
		{
			_nextPosition.x = _position.x - TILE_SIZE;

			if (_pLevel->IsFreeCell(_nextPosition))
			{
				_pCurrAnim = _animationsMap.at(TAI_WALK_LEFT);
				_eState = TS_WALK_LEFT;
			}
			else
			{
				_nextPosition.x = _position.x;
				_pCurrAnim = _animationsMap.at(TAI_STAND_LEFT);
			}
		}
		else if (playerPosition.y < _nextPosition.y)
		{
			_nextPosition.y = _position.y + TILE_SIZE;

			if (_pLevel->IsFreeCell(_nextPosition))
			{
				_eState = TS_WALK_DOWN;
				_pCurrAnim = _animationsMap.at(TAI_WALK_DOWN);
			}
			else
			{
				_nextPosition.y = _position.y;
				_pCurrAnim = _animationsMap.at(TAI_STAND_DOWN);
			}
		}
		else if (playerPosition.y > _nextPosition.y)
		{
			_nextPosition.y = _position.y - TILE_SIZE;

			if (_pLevel->IsFreeCell(_nextPosition))
			{
				_eState = TS_WALK_UP;
				_pCurrAnim = _animationsMap.at(TAI_WALK_UP);
			}
			else
			{
				_nextPosition.y = _position.y;
				_pCurrAnim = _animationsMap.at(TAI_STAND_UP);
			}
		}
}

void CALLBACK CTrap::Update(float fTime)
{
	// Если игрок уже отдал команду на перемещение.
	if (_eState < TS_STAND_UP)
		Move(fTime);
	
	// Если игрок стоит на месте - проверяем нажатие клавиш для начала движения.
/*	if (_eState >= ES_STAND_UP)
		MoveCommand();
*/

	_pCurrAnim->SetPosition(Vector2f(_position.x + 4, _position.y - 16));
	_pCurrAnim->Play(fTime);

	//if (pInput->Is
}

void CALLBACK CTrap::SetPosition(Vector2f &position)
{
	_position = position;
	_nextPosition = position;
}

void CALLBACK CTrap::Draw()
{
	_pCurrAnim->Draw();
}