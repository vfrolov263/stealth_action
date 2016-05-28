#include "Enemy.h"
#include "GameFiles.h"
#include "GameSettings.h"
#include "GameKeys.h"
#include <gl/gl.h>

CEnemy::CEnemy(const Vector2f &position): _position(position), _nextPosition(_position)
{
	IAnimation *pAnim = 0;
	AddAnimation(pAnim, EAI_WALK_UP);
	pAnim->SetTexture(TEXTURE_ENEMY_NAME);
	pAnim->SetFrameSize(Vector2ui(EAP_FRAME_WIDTH, EAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(EAP_WALK_UP_FIRST);
	pAnim->SetLastFrame(EAP_WALK_UP_LAST);
	pAnim->SetDelayTime(EAP_DELAY);

	AddAnimation(pAnim, EAI_STAND_UP);
	pAnim->SetTexture(TEXTURE_ENEMY_NAME);
	pAnim->SetFrameSize(Vector2ui(EAP_FRAME_WIDTH, EAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(EAP_STAND_UP_FIRST);
	pAnim->SetLastFrame(EAP_STAND_UP_LAST);
	pAnim->SetDelayTime(EAP_DELAY);

	AddAnimation(pAnim, EAI_WALK_DOWN);
	pAnim->SetTexture(TEXTURE_ENEMY_NAME);
	pAnim->SetFrameSize(Vector2ui(EAP_FRAME_WIDTH, EAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(EAP_WALK_DOWN_FIRST);
	pAnim->SetLastFrame(EAP_WALK_DOWN_LAST);
	pAnim->SetDelayTime(EAP_DELAY);

	AddAnimation(pAnim, EAI_STAND_DOWN);
	pAnim->SetTexture(TEXTURE_ENEMY_NAME);
	pAnim->SetFrameSize(Vector2ui(EAP_FRAME_WIDTH, EAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(EAP_STAND_DOWN_FIRST);
	pAnim->SetLastFrame(EAP_STAND_DOWN_LAST);
	pAnim->SetDelayTime(EAP_DELAY);

	AddAnimation(pAnim, EAI_WALK_RIGHT);
	pAnim->SetTexture(TEXTURE_ENEMY_NAME);
	pAnim->SetFrameSize(Vector2ui(EAP_FRAME_WIDTH, EAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(EAP_WALK_RIGHT_FIRST);
	pAnim->SetLastFrame(EAP_WALK_RIGHT_LAST);
	pAnim->SetDelayTime(EAP_DELAY);

	AddAnimation(pAnim, EAI_STAND_RIGHT);
	pAnim->SetTexture(TEXTURE_ENEMY_NAME);
	pAnim->SetFrameSize(Vector2ui(EAP_FRAME_WIDTH, EAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(EAP_STAND_RIGHT_FIRST);
	pAnim->SetLastFrame(EAP_STAND_RIGHT_LAST);
	pAnim->SetDelayTime(EAP_DELAY);

	AddAnimation(pAnim, EAI_WALK_LEFT);
	pAnim->SetTexture(TEXTURE_ENEMY_NAME);
	pAnim->SetFrameSize(Vector2ui(EAP_FRAME_WIDTH, EAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(EAP_WALK_LEFT_FIRST);
	pAnim->SetLastFrame(EAP_WALK_LEFT_LAST);
	pAnim->SetDelayTime(EAP_DELAY);

	AddAnimation(pAnim, EAI_STAND_LEFT);
	pAnim->SetTexture(TEXTURE_ENEMY_NAME);
	pAnim->SetFrameSize(Vector2ui(EAP_FRAME_WIDTH, EAP_FRAME_HEIGHT));
	pAnim->SetFirstFrame(EAP_STAND_LEFT_FIRST);
	pAnim->SetLastFrame(EAP_STAND_LEFT_LAST);
	pAnim->SetDelayTime(EAP_DELAY);

	_pCurrAnim = _animationsMap.at(EAI_STAND_RIGHT);
	_eState = ES_STAND_RIGHT;

	_nextPosition = _position;

	_visibilityZoneCoords = new Vector2i[30];
	_visibilityZone = new bool[30];

	killed = false;
}

CEnemy::~CEnemy()
{
	delete [] _visibilityZoneCoords;
	delete [] _visibilityZone;
}

void CALLBACK CEnemy::Stand()
{
	_position = _nextPosition;
	_eState = (E_ENEMY_STATE)(_eState + ES_STAND_UP);
	_pCurrAnim = _animationsMap.at(EAI_STAND_UP + (_eState - ES_STAND_UP));
	it++;
}

void CALLBACK CEnemy::Move(float fTime)
{
	float fDist = fTime * ENEMY_SPEED;

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

void CALLBACK CEnemy::MoveCommand()
{
	if (it != trajectory.end())
	{
		if (*it == 'u')
		{
			_pCurrAnim = _animationsMap.at(EAI_WALK_UP);
			_eState = ES_WALK_UP;
			_nextPosition.y = _position.y - TILE_SIZE;
		}
		else if (*it == 'd')
		{
			_pCurrAnim = _animationsMap.at(EAI_WALK_DOWN);
			_eState = ES_WALK_DOWN;
			_nextPosition.y = _position.y + TILE_SIZE;
		}
		else if (*it == 'r')
		{
			_pCurrAnim = _animationsMap.at(EAI_WALK_RIGHT);
			_eState = ES_WALK_RIGHT;
			_nextPosition.x = _position.x + TILE_SIZE;
		}
		else if (*it == 'l')
		{
			_pCurrAnim = _animationsMap.at(EAI_WALK_LEFT);
			_eState = ES_WALK_LEFT;
			_nextPosition.x = _position.x - TILE_SIZE;
		}
	}
	else
		it = trajectory.begin();
}

void CALLBACK CEnemy::Update(float fTime)
{
	// Если игрок уже отдал команду на перемещение.
	if (_eState < ES_STAND_UP)
		Move(fTime);
	
	// Если игрок стоит на месте - проверяем нажатие клавиш для начала движения.
	if (_eState >= ES_STAND_UP)
		MoveCommand();

	_pCurrAnim->SetPosition(Vector2f(_position.x + 4, _position.y - 8));
	_pCurrAnim->Play(fTime);
}

void CALLBACK CEnemy::Draw()
{
	_pCurrAnim->Draw();
}

void CALLBACK CEnemy::DrawVisibility()
{
	for (int i = 0; i < 30; i++)
	{
		if (_visibilityZone[i]) {
			pVisibSpr->SetPosition(_visibilityZoneCoords[i]);
			pVisibSpr->Draw();
		}
	}
}

Vector2i * CALLBACK CEnemy::GetDefaultVisibilityZone(Vector2i *vZone)
{
	//map<int,Vector2i> vZone;

	switch (_eState) {
	case ES_WALK_UP:
	case ES_STAND_UP:
		{
			vZone[0] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 0);
			vZone[1] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 0);
			vZone[2] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 1);
			vZone[3] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 1);
			vZone[4] = Vector2i(_nextPosition.x + TILE_SIZE * 0, _nextPosition.y - TILE_SIZE * 1);
			vZone[5] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 1);
			vZone[6] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 1);
			vZone[7] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 2);
			vZone[8] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 2);
			vZone[9] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 2);
			vZone[10] = Vector2i(_nextPosition.x + TILE_SIZE * 0, _nextPosition.y - TILE_SIZE * 2);
			vZone[11] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 2);
			vZone[12] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 2);
			vZone[13] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 2);
			vZone[14] = Vector2i(_nextPosition.x + TILE_SIZE * 4, _nextPosition.y - TILE_SIZE * 3);
			vZone[15] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 3);
			vZone[16] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 3);
			vZone[17] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 3);
			vZone[18] = Vector2i(_nextPosition.x + TILE_SIZE * 0, _nextPosition.y - TILE_SIZE * 3);
			vZone[19] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 3);
			vZone[20] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 3);
			vZone[21] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 3);
			vZone[22] = Vector2i(_nextPosition.x - TILE_SIZE * 4, _nextPosition.y - TILE_SIZE * 3);
			vZone[23] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 4);
			vZone[24] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 4);
			vZone[25] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 4);
			vZone[26] = Vector2i(_nextPosition.x + TILE_SIZE * 0, _nextPosition.y - TILE_SIZE * 4);
			vZone[27] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 4);
			vZone[28] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 4);
			vZone[29] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 4);
			break;
		}
	case ES_WALK_DOWN:
	case ES_STAND_DOWN:
		{
			vZone[0] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 0);
			vZone[1] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 0);
			vZone[2] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 1);
			vZone[3] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 1);
			vZone[4] = Vector2i(_nextPosition.x - TILE_SIZE * 0, _nextPosition.y + TILE_SIZE * 1);
			vZone[5] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 1);
			vZone[6] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 1);
			vZone[7] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 2);
			vZone[8] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 2);
			vZone[9] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 2);
			vZone[10] = Vector2i(_nextPosition.x - TILE_SIZE * 0, _nextPosition.y + TILE_SIZE * 2);
			vZone[11] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 2);
			vZone[12] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 2);
			vZone[13] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 2);
			vZone[14] = Vector2i(_nextPosition.x - TILE_SIZE * 4, _nextPosition.y + TILE_SIZE * 3);
			vZone[15] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 3);
			vZone[16] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 3);
			vZone[17] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 3);
			vZone[18] = Vector2i(_nextPosition.x - TILE_SIZE * 0, _nextPosition.y + TILE_SIZE * 3);
			vZone[19] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 3);
			vZone[20] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 3);
			vZone[21] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 3);
			vZone[22] = Vector2i(_nextPosition.x + TILE_SIZE * 4, _nextPosition.y + TILE_SIZE * 3);
			vZone[23] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 4);
			vZone[24] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 4);
			vZone[25] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 4);
			vZone[26] = Vector2i(_nextPosition.x - TILE_SIZE * 0, _nextPosition.y + TILE_SIZE * 4);
			vZone[27] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 4);
			vZone[28] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 4);
			vZone[29] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 4);
			break;
		}
	case ES_WALK_RIGHT:
	case ES_STAND_RIGHT:
		{
			vZone[0] = Vector2i(_nextPosition.x + TILE_SIZE * 0, _nextPosition.y + TILE_SIZE * 1);
			vZone[1] = Vector2i(_nextPosition.x + TILE_SIZE * 0, _nextPosition.y - TILE_SIZE * 1);
			vZone[2] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 2);
			vZone[3] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 1);
			vZone[4] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 0);
			vZone[5] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 1);
			vZone[6] = Vector2i(_nextPosition.x + TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 2);
			vZone[7] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 3);
			vZone[8] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 2);
			vZone[9] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 1);
			vZone[10] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 0);
			vZone[11] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 1);
			vZone[12] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 2);
			vZone[13] = Vector2i(_nextPosition.x + TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 3);
			vZone[14] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 4);
			vZone[15] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 3);
			vZone[16] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 2);
			vZone[17] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 1);
			vZone[18] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 0);
			vZone[19] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 1);
			vZone[20] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 2);
			vZone[21] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 3);
			vZone[22] = Vector2i(_nextPosition.x + TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 4);
			vZone[23] = Vector2i(_nextPosition.x + TILE_SIZE * 4, _nextPosition.y + TILE_SIZE * 3);
			vZone[24] = Vector2i(_nextPosition.x + TILE_SIZE * 4, _nextPosition.y + TILE_SIZE * 2);
			vZone[25] = Vector2i(_nextPosition.x + TILE_SIZE * 4, _nextPosition.y + TILE_SIZE * 1);
			vZone[26] = Vector2i(_nextPosition.x + TILE_SIZE * 4, _nextPosition.y + TILE_SIZE * 0);
			vZone[27] = Vector2i(_nextPosition.x + TILE_SIZE * 4, _nextPosition.y - TILE_SIZE * 1);
			vZone[28] = Vector2i(_nextPosition.x + TILE_SIZE * 4, _nextPosition.y - TILE_SIZE * 2);
			vZone[29] = Vector2i(_nextPosition.x + TILE_SIZE * 4, _nextPosition.y - TILE_SIZE * 3);
			break;
		}
	case ES_WALK_LEFT:
	case ES_STAND_LEFT:
		{
			vZone[0] = Vector2i(_nextPosition.x - TILE_SIZE * 0, _nextPosition.y - TILE_SIZE * 1);
			vZone[1] = Vector2i(_nextPosition.x - TILE_SIZE * 0, _nextPosition.y + TILE_SIZE * 1);
			vZone[2] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 2);
			vZone[3] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 1);
			vZone[4] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y - TILE_SIZE * 0);
			vZone[5] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 1);
			vZone[6] = Vector2i(_nextPosition.x - TILE_SIZE * 1, _nextPosition.y + TILE_SIZE * 2);
			vZone[7] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 3);
			vZone[8] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 2);
			vZone[9] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 1);
			vZone[10] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y - TILE_SIZE * 0);
			vZone[11] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 1);
			vZone[12] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 2);
			vZone[13] = Vector2i(_nextPosition.x - TILE_SIZE * 2, _nextPosition.y + TILE_SIZE * 3);
			vZone[14] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 4);
			vZone[15] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 3);
			vZone[16] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 2);
			vZone[17] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 1);
			vZone[18] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y - TILE_SIZE * 0);
			vZone[19] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 1);
			vZone[20] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 2);
			vZone[21] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 3);
			vZone[22] = Vector2i(_nextPosition.x - TILE_SIZE * 3, _nextPosition.y + TILE_SIZE * 4);
			vZone[23] = Vector2i(_nextPosition.x - TILE_SIZE * 4, _nextPosition.y - TILE_SIZE * 3);
			vZone[24] = Vector2i(_nextPosition.x - TILE_SIZE * 4, _nextPosition.y - TILE_SIZE * 2);
			vZone[25] = Vector2i(_nextPosition.x - TILE_SIZE * 4, _nextPosition.y - TILE_SIZE * 1);
			vZone[26] = Vector2i(_nextPosition.x - TILE_SIZE * 4, _nextPosition.y - TILE_SIZE * 0);
			vZone[27] = Vector2i(_nextPosition.x - TILE_SIZE * 4, _nextPosition.y + TILE_SIZE * 1);
			vZone[28] = Vector2i(_nextPosition.x - TILE_SIZE * 4, _nextPosition.y + TILE_SIZE * 2);
			vZone[29] = Vector2i(_nextPosition.x - TILE_SIZE * 4, _nextPosition.y + TILE_SIZE * 3);
			break;
		}
	}
	return vZone;
}

void CALLBACK CEnemy::UpdateVisibilityZone(bool **_collMap, Vector2i _levSize)
{
	_visibilityZoneCoords = GetDefaultVisibilityZone(&*_visibilityZoneCoords);

	for (int i = 0; i < 30; i++)
		_visibilityZone[i] = 1;
	
	for (int k = 0; k < 30; k++)
		for (int i = 0; i < _levSize.x; i++)
			for (int j = 0; j < _levSize.y; j++)
				if ((_visibilityZoneCoords[k].x == i * TILE_SIZE) && (_visibilityZoneCoords[k].y == j * TILE_SIZE) && _collMap[i][j])
					switch (k)
					{
					case 0:
						_visibilityZone[0] = 0;
						_visibilityZone[2] = 0;
						_visibilityZone[3] = 0;
						_visibilityZone[7] = 0;
						_visibilityZone[8] = 0;
						_visibilityZone[14] = 0;
						_visibilityZone[15] = 0;
						_visibilityZone[16] = 0;
						_visibilityZone[23] = 0;
						_visibilityZone[24] = 0;
						break;
					case 1:
						_visibilityZone[1] = 0;
						_visibilityZone[5] = 0;
						_visibilityZone[6] = 0;
						_visibilityZone[12] = 0;
						_visibilityZone[13] = 0;
						_visibilityZone[20] = 0;
						_visibilityZone[21] = 0;
						_visibilityZone[22] = 0;
						_visibilityZone[28] = 0;
						_visibilityZone[29] = 0;
						break;
					case 2:
						_visibilityZone[2] = 0;
						_visibilityZone[7] = 0;
						_visibilityZone[8] = 0;
						_visibilityZone[14] = 0;
						_visibilityZone[15] = 0;
						_visibilityZone[23] = 0;
						break;
					case 3:
						_visibilityZone[2] = 0;
						_visibilityZone[3] = 0;
						_visibilityZone[7] = 0;
						_visibilityZone[8] = 0;
						_visibilityZone[9] = 0;
						_visibilityZone[14] = 0;
						_visibilityZone[15] = 0;
						_visibilityZone[16] = 0;
						_visibilityZone[17] = 0;
						_visibilityZone[23] = 0;
						_visibilityZone[24] = 0;
						break;
					case 4:
						_visibilityZone[4] = 0;
						_visibilityZone[9] = 0;
						_visibilityZone[10] = 0;
						_visibilityZone[11] = 0;
						_visibilityZone[17] = 0;
						_visibilityZone[18] = 0;
						_visibilityZone[19] = 0;
						_visibilityZone[24] = 0;
						_visibilityZone[25] = 0;
						_visibilityZone[26] = 0;
						_visibilityZone[27] = 0;
						_visibilityZone[28] = 0;
						break;
					case 5:
						_visibilityZone[5] = 0;
						_visibilityZone[6] = 0;
						_visibilityZone[11] = 0;
						_visibilityZone[12] = 0;
						_visibilityZone[13] = 0;
						_visibilityZone[19] = 0;
						_visibilityZone[20] = 0;
						_visibilityZone[21] = 0;
						_visibilityZone[22] = 0;
						_visibilityZone[28] = 0;
						_visibilityZone[29] = 0;
						break;
					case 6:
						_visibilityZone[6] = 0;
						_visibilityZone[12] = 0;
						_visibilityZone[13] = 0;
						_visibilityZone[21] = 0;
						_visibilityZone[22] = 0;
						_visibilityZone[29] = 0;
						break;
					case 7:
						_visibilityZone[7] = 0;
						_visibilityZone[14] = 0;
						_visibilityZone[15] = 0;
						break;
					case 8:
						_visibilityZone[7] = 0;
						_visibilityZone[8] = 0;
						_visibilityZone[14] = 0;
						_visibilityZone[15] = 0;
						_visibilityZone[16] = 0;
						_visibilityZone[23] = 0;
						break;
					case 9:
						_visibilityZone[9] = 0;
						_visibilityZone[16] = 0;
						_visibilityZone[17] = 0;
						_visibilityZone[23] = 0;
						_visibilityZone[24] = 0;
						_visibilityZone[25] = 0;
						break;
					case 10:
						_visibilityZone[10] = 0;
						_visibilityZone[18] = 0;
						_visibilityZone[25] = 0;
						_visibilityZone[26] = 0;
						_visibilityZone[27] = 0;
						break;
					case 11:
						_visibilityZone[11] = 0;
						_visibilityZone[19] = 0;
						_visibilityZone[20] = 0;
						_visibilityZone[27] = 0;
						_visibilityZone[28] = 0;
						_visibilityZone[29] = 0;
						break;
					case 12:
						_visibilityZone[12] = 0;
						_visibilityZone[13] = 0;
						_visibilityZone[20] = 0;
						_visibilityZone[21] = 0;
						_visibilityZone[22] = 0;
						_visibilityZone[29] = 0;
						break;
					case 13:
						_visibilityZone[13] = 0;
						_visibilityZone[21] = 0;
						_visibilityZone[22] = 0;
						break;
					case 14:
						_visibilityZone[14] = 0;
						break;
					case 15:
						_visibilityZone[14] = 0;
						_visibilityZone[15] = 0;
						_visibilityZone[23] = 0;
						break;
					case 16:
						_visibilityZone[16] = 0;
						_visibilityZone[23] = 0;
						_visibilityZone[24] = 0;
						break;
					case 17:
						_visibilityZone[17] = 0;
						_visibilityZone[24] = 0;
						_visibilityZone[25] = 0;
						break;
					case 18:
						_visibilityZone[18] = 0;
						_visibilityZone[26] = 0;
						break;
					case 19:
						_visibilityZone[19] = 0;
						_visibilityZone[27] = 0;
						_visibilityZone[28] = 0;
						break;
					case 20:
						_visibilityZone[20] = 0;
						_visibilityZone[28] = 0;
						_visibilityZone[29] = 0;
						break;
					case 21:
						_visibilityZone[21] = 0;
						_visibilityZone[22] = 0;
						_visibilityZone[29] = 0;
						break;
					case 22:
						_visibilityZone[22] = 0;
						break;
					case 23:
						_visibilityZone[23] = 0;
						break;
					case 24:
						_visibilityZone[24] = 0;
						break;
					case 25:
						_visibilityZone[25] = 0;
						break;
					case 26:
						_visibilityZone[26] = 0;
						break;
					case 27:
						_visibilityZone[27] = 0;
						break;
					case 28:
						_visibilityZone[28] = 0;
						break;
					case 29:
						_visibilityZone[29] = 0;
						break;
					}
}

bool CALLBACK CEnemy::IsInVisibilityZone(Vector2f objectPosition)
{
	for (int i = 0; i < 30; i++)
		if ((_visibilityZoneCoords[i].x == objectPosition.x) && (_visibilityZoneCoords[i].y == objectPosition.y) && (_visibilityZone[i]))
			return true;

	return false;
}

Vector2f CALLBACK CEnemy::GetPosition()
{
	return _nextPosition;
}

void CALLBACK CEnemy::AddToTrajectory(char t)
{
	trajectory.push_back(t);
	it = trajectory.begin();
}