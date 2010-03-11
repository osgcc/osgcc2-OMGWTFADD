
#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "main.h"

class Game
{
public:
	virtual void Update(game_info* gi, float deltatime) = 0;
	virtual void Draw(game_info* gi) = 0;
	virtual void DrawOrtho(game_info* gi) = 0;

	virtual void KeyDown(game_info* gi, Uint32 key)=0;
	virtual void KeyUp(game_info* gi, Uint32 key)=0;

	virtual void MouseMovement(game_info* gi, Uint32 x, Uint32 y)=0;
	virtual void MouseDown(game_info* gi)=0;

	virtual void KeyRepeat(game_info* gi)=0;

	virtual void Attack(game_info* gi, int severity)=0;

	virtual void InitGame(game_info* gi)=0;
};

#endif //GAME_INCLUDED