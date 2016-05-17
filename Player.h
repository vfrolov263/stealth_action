#pragma once
#include "AnimatedObject.h"

// id всех анимаций (по две дл€ каждого направлени€ перемещени€ - анимаци€ когда игрок не движетс€ и когда двидетс€).
enum E_PLAYER_ANIMS_IDS
{
	PAI_WALK_UP,
	PAI_WALK_DOWN,
	PAI_WALK_RIGHT,
	PAI_WALK_LEFT,
	PAI_STAND_UP,
	PAI_STAND_DOWN,
	PAI_STAND_RIGHT,
	PAI_STAND_LEFT,
};

// ѕараметры анимаций.
enum E_PLAYER_ANIMS_PARAMS
{
	PAP_FRAME_WIDTH			= 32,
	PAP_FRAME_HEIGHT		= 42,
	PAP_WALK_UP_FIRST		= 12,
	PAP_WALK_UP_LAST		= 15,
	PAP_WALK_DOWN_FIRST		= 0,
	PAP_WALK_DOWN_LAST		= 3,
	PAP_WALK_RIGHT_FIRST	= 8,
	PAP_WALK_RIGHT_LAST		= 11,
	PAP_WALK_LEFT_FIRST		= 4,
	PAP_WALK_LEFT_LAST		= 7,
	PAP_STAND_UP_FIRST		= 13,
	PAP_STAND_UP_LAST		= 13,
	PAP_STAND_DOWN_FIRST	= 1,
	PAP_STAND_DOWN_LAST		= 1,
	PAP_STAND_RIGHT_FIRST	= 9,
	PAP_STAND_RIGHT_LAST	= 9,
	PAP_STAND_LEFT_FIRST	= 5,
	PAP_STAND_LEFT_LAST		= 5,
	PAP_DELAY				= 50
};

// —осто€ние игрока - куда он дижетс€ и ли смотрит.
enum E_PLAYER_STATE
{
	PS_WALK_UP,
	PS_WALK_DOWN,
	PS_WALK_RIGHT,
	PS_WALK_LEFT,
	PS_STAND_UP,
	PS_STAND_DOWN,
	PS_STAND_RIGHT,
	PS_STAND_LEFT,

};

#define PLAYER_SPEED			120.0f;						// —корость перемещени€ игрока.
#define PLAYER_START_POSITION	Vector2f(32 * 5, 32 * 5)	// ƒл€ теста - потом будет считыватьс€ из файла. 

class CLevel;

class CPlayer: public CAnimatedObject
{
	float _fSpeed;
	Vector2f _position, _nextPosition; // “екуща€ позици€ и та, в которую надо переместитьс€.
	E_PLAYER_STATE _eState;
	CLevel *_pLevel;

	/*
	ќстанавливает игрока.
	*/
	void CALLBACK Stand();

	/*
	ѕеремещает игрока в заданную позицию (_nextPosition).
	*/
	void CALLBACK Move(float fTime);

	/*
	ќбрабатывает нажатис€ клавиш.
	*/
	void CALLBACK MoveCommand();
public:
	CPlayer(CLevel *pLevel);
	virtual ~CPlayer() {}

	/*
	ќбновл€ет игрока.
	param1[in] dt - врем€ с последнего обновлени€ (в секундах).
    */
	void CALLBACK Update(float fTime);


	void CALLBACK SetPosition(Vector2f &position);

	const Vector2f &CALLBACK GetPosition() const { return _position; }

	/*
	–исует игрока.
	*/
	void CALLBACK Draw();
};