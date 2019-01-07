#pragma once


#define DATA_EVENT_TYPE_START		1

struct DATA_EVENT
{
	short Type;
};


struct DATA_POSITION
{
	float x, y, z;
};


struct DATA_ROTATION
{
	float x, y, z;
};


#define DATA_TYPE_EVENT		1
#define DATA_TYPE_POSITION	2
#define DATA_TYPE_ROTATION	3
#define DATA_TYPE_GAMESTART	4

struct DATA
{
	int		ID;
	int		Type;

	union
	{
		DATA_EVENT		Event;
		DATA_POSITION	Position;
		DATA_ROTATION	Rotation;
	};
};
