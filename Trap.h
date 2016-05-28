#pragma once
#include "AnimatedObject.h"

// id ���� �������� (�� ��� ��� ������� ����������� ����������� - �������� ����� ����� �� �������� � ����� ��������).
enum E_TRAP_ANIMS_IDS
{
	TAI_WALK_UP,
	TAI_WALK_DOWN,
	TAI_WALK_RIGHT,
	TAI_WALK_LEFT,
	TAI_STAND_UP,
	TAI_STAND_DOWN,
	TAI_STAND_RIGHT,
	TAI_STAND_LEFT,
};

// ��������� ��������.
enum E_TRAP_ANIMS_PARAMS
{
	TAP_FRAME_WIDTH			= 32,
	TAP_FRAME_HEIGHT		= 42,
	TAP_WALK_UP_FIRST		= 12,
	TAP_WALK_UP_LAST		= 15,
	TAP_WALK_DOWN_FIRST		= 0,
	TAP_WALK_DOWN_LAST		= 3,
	TAP_WALK_RIGHT_FIRST	= 8,
	TAP_WALK_RIGHT_LAST		= 11,
	TAP_WALK_LEFT_FIRST		= 4,
	TAP_WALK_LEFT_LAST		= 7,
	TAP_STAND_UP_FIRST		= 13,
	TAP_STAND_UP_LAST		= 13,
	TAP_STAND_DOWN_FIRST	= 1,
	TAP_STAND_DOWN_LAST		= 1,
	TAP_STAND_RIGHT_FIRST	= 9,
	TAP_STAND_RIGHT_LAST	= 9,
	TAP_STAND_LEFT_FIRST	= 5,
	TAP_STAND_LEFT_LAST		= 5,
	TAP_DELAY				= 50
};

// ��������� ������ - ���� �� ������� � �� �������.
enum E_TRAP_STATE
{
	TS_WALK_UP,
	TS_WALK_DOWN,
	TS_WALK_RIGHT,
	TS_WALK_LEFT,
	TS_STAND_UP,
	TS_STAND_DOWN,
	TS_STAND_RIGHT,
	TS_STAND_LEFT,

};

#define TRAP_SPEED			120.0f;						// �������� ����������� ������.
#define TRAP_START_POSITION	Vector2f(32 * 5, 32 * 5)	// ��� ����� - ����� ����� ����������� �� �����. 

class CLevel;

class CTrap: public CAnimatedObject
{
	float _fSpeed;
	Vector2f _position, _nextPosition; // ������� ������� � ��, � ������� ���� �������������.
	E_TRAP_STATE _eState;
	CLevel *_pLevel;

	/*
	������������� ������.
	*/
	void CALLBACK Stand();

	/*
	���������� ������ � �������� ������� (_nextPosition).
	*/
	void CALLBACK Move(float fTime);

	/*
	������������ �������� ������.
	*/
	void CALLBACK MoveNext();
public:
	CTrap(const Vector2f &position, CLevel *pLevel);
	virtual ~CTrap() {}

	/*
	��������� ������.
	param1[in] dt - ����� � ���������� ���������� (� ��������).
    */
	void CALLBACK Update(float fTime);

	void CALLBACK ActiveTrap(Vector2f playerNextPosition, Vector2f playerPosition);

	void CALLBACK SetPosition(Vector2f &position);

	const Vector2f &CALLBACK GetPosition() const { return _position; }

	const Vector2f &CALLBACK GetNextPosition() const { return _nextPosition; }

	/*
	������ ������.
	*/
	void CALLBACK Draw();
};