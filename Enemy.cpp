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
	for (map<int,Vector2i>::iterator it = visibilityZone.begin(); it != visibilityZone.end(); it++)
	{
		pVisibSpr->SetPosition(it->second);
		pVisibSpr->Draw();
	}
}

map<int,Vector2i> CALLBACK CEnemy::GetDefaultVisibilityZone()
{
	map<int,Vector2i> vZone;

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

void CALLBACK CEnemy::UpdateVisibilityZone(multiset<Vector2f> &objects)
{
	visibilityZone = GetDefaultVisibilityZone();
	map<int,Vector2i> vz = GetDefaultVisibilityZone();

	for (map<int,Vector2i>::iterator it1 = vz.begin(); it1 != vz.end(); it1++)
		for (multiset<Vector2f>::iterator it2 = objects.begin(); it2 != objects.end(); it2++)
			if ((it1->second.x == it2->x) && (it1->second.y == it2->y))
				switch (it1->first)
				{
				case 0:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 0:
						case 2:
						case 3:
						case 7:
						case 8:
						case 14:
						case 15:
						case 16:
						case 23:
						case 24:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 1:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 1:
						case 5:
						case 6:
						case 12:
						case 13:
						case 20:
						case 21:
						case 22:
						case 28:
						case 29:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 2:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 2:
						case 7:
						case 8:
						case 14:
						case 15:
						case 23:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 3:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 2:
						case 3:
						case 7:
						case 8:
						case 9:
						case 14:
						case 15:
						case 16:
						case 17:
						case 23:
						case 24:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 4:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 4:
						case 9:
						case 10:
						case 11:
						case 17:
						case 18:
						case 19:
						case 24:
						case 25:
						case 26:
						case 27:
						case 28:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 5:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 5:
						case 6:
						case 11:
						case 12:
						case 13:
						case 19:
						case 20:
						case 21:
						case 22:
						case 28:
						case 29:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 6:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 6:
						case 12:
						case 13:
						case 21:
						case 22:
						case 29:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 7:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 7:
						case 14:
						case 15:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 8:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 7:
						case 8:
						case 14:
						case 15:
						case 16:
						case 23:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 9:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 9:
						case 16:
						case 17:
						case 23:
						case 24:
						case 25:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 10:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 10:
						case 18:
						case 25:
						case 26:
						case 27:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 11:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 11:
						case 19:
						case 20:
						case 27:
						case 28:
						case 29:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 12:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 12:
						case 13:
						case 20:
						case 21:
						case 22:
						case 29:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 13:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 13:
						case 21:
						case 22:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 14:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 14:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 15:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 14:
						case 15:
						case 23:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 16:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 16:
						case 23:
						case 24:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 17:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 17:
						case 24:
						case 25:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 18:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 18:
						case 26:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 19:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 19:
						case 27:
						case 28:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 20:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 20:
						case 28:
						case 29:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 21:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 21:
						case 22:
						case 29:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 22:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 22:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 23:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 23:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 24:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 24:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 25:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 25:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 26:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 26:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 27:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 27:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 28:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 28:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				case 29:
					for (map<int,Vector2i>::iterator it3 = visibilityZone.begin(); it3 != visibilityZone.end(); it3++)
						switch (it3->first)
						{
						case 29:
							visibilityZone.erase(it3->first);
							it3 = visibilityZone.begin();
							break;
						}
					break;
				}
}

bool CALLBACK CEnemy::IsInVisibilityZone(Vector2f objectPosition)
{
	for (map<int,Vector2i>::iterator it = visibilityZone.begin(); it != visibilityZone.end(); it++)
		if ((it->second.x == objectPosition.x) && (it->second.y == objectPosition.y))
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