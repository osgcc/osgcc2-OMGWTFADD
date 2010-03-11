

#ifndef BREAKOUT_INCLUDED
#define BREAKOUT_INCLUDED

#include "game.h"

class BreakOut : public Game
{
public:

	// conventions:
	void InitGame(game_info* gi);

	void Update(game_info* gi, float deltatime);
	void Draw(game_info* gi);
	void DrawOrtho(game_info* gi);

	void KeyDown(game_info* gi, Uint32 key);
	void KeyUp(game_info* gi, Uint32 key);
	void KeyRepeat(game_info* gi);

	void MouseMovement(game_info* gi, Uint32 x, Uint32 y);
	void MouseDown(game_info* gi);

	void Attack(game_info* gi, int severity);

	// ---
	
	float GetLeftBounds(game_info* gi);
	float GetRightBounds(game_info* gi);

	void DrawBall(game_info* gi);
	void MoveBall(game_info* gi, float t, int last_type);

	float CheckBallAgainst(game_info* gi, float t, float x1, float y1, float x2, float y2);
	bool CheckBallAgainstBlock(game_info* gi, float t, float &cur_t, int &type_t, int last_type, float x, float y, int isPaddle);

};

#endif //BREAKOUT_INCLUDED
