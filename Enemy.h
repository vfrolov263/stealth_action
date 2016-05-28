#pragma once
#include "AnimatedObject.h"
#include <vector>
#include <set>
#include <iterator>
using std::vector;
using std::multiset;

// id всех анимаций (по две дл€ каждого направлени€ перемещени€ - анимаци€ когда игрок не движетс€ и когда двидетс€).
enum E_ENEMY_ANIMS_IDS
{
	EAI_WALK_UP,
	EAI_WALK_DOWN,
	EAI_WALK_RIGHT,
	EAI_WALK_LEFT,
	EAI_STAND_UP,
	EAI_STAND_DOWN,
	EAI_STAND_RIGHT,
	EAI_STAND_LEFT,
};

// ѕараметры анимаций.
enum E_ENEMY_ANIMS_PARAMS
{
	EAP_FRAME_WIDTH			= 32,
	EAP_FRAME_HEIGHT		= 42,
	EAP_WALK_UP_FIRST		= 12,
	EAP_WALK_UP_LAST		= 15,
	EAP_WALK_DOWN_FIRST		= 0,
	EAP_WALK_DOWN_LAST		= 3,
	EAP_WALK_RIGHT_FIRST	= 8,
	EAP_WALK_RIGHT_LAST		= 11,
	EAP_WALK_LEFT_FIRST		= 4,
	EAP_WALK_LEFT_LAST		= 7,
	EAP_STAND_UP_FIRST		= 13,
	EAP_STAND_UP_LAST		= 13,
	EAP_STAND_DOWN_FIRST	= 1,
	EAP_STAND_DOWN_LAST		= 1,
	EAP_STAND_RIGHT_FIRST	= 9,
	EAP_STAND_RIGHT_LAST	= 9,
	EAP_STAND_LEFT_FIRST	= 5,
	EAP_STAND_LEFT_LAST		= 5,
	EAP_DELAY				= 50
};

// —осто€ние игрока - куда он дижетс€ и ли смотрит.
enum E_ENEMY_STATE
{
	ES_WALK_UP,
	ES_WALK_DOWN,
	ES_WALK_RIGHT,
	ES_WALK_LEFT,
	ES_STAND_UP,
	ES_STAND_DOWN,
	ES_STAND_RIGHT,
	ES_STAND_LEFT,

};

#define ENEMY_SPEED			60.0f;						// —корость перемещени€ игрока.
#define ENEMY_START_POSITION	Vector2f(32 * 10, 32 * 5)	// ƒл€ теста - потом будет считыватьс€ из файла. 

extern ISprite *pVisibSpr;

class CEnemy: public CAnimatedObject
{
	float _fSpeed;
	Vector2f _position, _nextPosition; // “екуща€ позици€ и та, в которую надо переместитьс€.
	E_ENEMY_STATE _eState;
	vector<char> trajectory;
	vector<char>::iterator it;
	map<int,Vector2i> visibilityZone;
	Vector2i *_visibilityZoneCoords;
	bool *_visibilityZone;
	bool killed;

	/*
	ќстанавливает игрока.
	*/
	void CALLBACK Stand();

	/*
	ѕеремещает игрока в заданную позицию (_nextPosition).
	*/
	void CALLBACK Move(float fTime);

	/*
	ќбрабатывает нажати€ клавиш.
	*/
	void CALLBACK MoveCommand();
public:
	CEnemy(const Vector2f &position);
	~CEnemy();

	/*
	ќбновл€ет игрока.
	param1[in] dt - врем€ с последнего обновлени€ (в секундах).
    */
	void CALLBACK Update(float fTime);

	/*
	–исует игрока.
	*/
	void CALLBACK Draw();

	void CALLBACK DrawVisibility();

	Vector2i * CALLBACK GetDefaultVisibilityZone(Vector2i *_visibilityZone);
	
	void CALLBACK UpdateVisibilityZone(bool **_collMap, Vector2i _levSize);//multiset<Vector2i> &objects);

	bool CALLBACK IsInVisibilityZone(Vector2f objectPosition);

	Vector2f CALLBACK GetPosition();

	void CALLBACK AddToTrajectory(char t);

	void CALLBACK Kill() { killed = true; }

	bool CALLBACK IsKilled() { return killed; }

	void CALLBACK ClearVisibilityZone() { for (int i = 0; i < 30; i++) _visibilityZone[i] = 0; }
};