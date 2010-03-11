
#include "components.h"
#include "breakout.h"

// conventions:
void BreakOut::InitGame(game_info* gi)
{
	gi->fine = 2.5;

	gi->ball_x = 0;
	gi->ball_y = 0;

	gi->ball_dx = (BREAKOUT_BALL_SPEED_X + (LEVEL * 0.2));
	gi->ball_dy = (BREAKOUT_BALL_SPEED_Y + (LEVEL * 0.2));

	gi->break_out_time = BREAK_OUT_SECONDS;

	gi->break_out_consecutives = 0;
}

float BreakOut::CheckBallAgainst(game_info* gi, float t, float x1, float y1, float x2, float y2)
{
	// OK !!!
	// COLLISION DETECTION
	// RAYBASED?!

	float n_t;

	float b_x;
	float b_y;

#define SPHERE 0.125

	float sp;

	if (x1 == x2)
	{
		// VERTICAL LINE

		if (gi->ball_dx > 0)
		{
			sp = -SPHERE;
		}
		else
		{
			sp = SPHERE;
		}

		n_t = (x1 - (gi->ball_x + sp)) / gi->ball_dx;

		b_y = (gi->ball_y + sp) + (n_t * gi->ball_dy);

 		if ((b_y <= y1) && (b_y >= y2)){
			//printf("%f %f %f %f %f\n", n_t, t, b_y, y1,y2);

			if ((n_t < t) && (n_t >= 0))
			{
				return n_t;
			}
		}
/*
		if ((b_y < y1) && (b_y > y2) && (n_t < t) && (n_t >= 0))
		{
			// YEP!
			return n_t;
		}*/
	}
	else if (y1 == y2)
	{
		// HORIZONTAL LINE

		if (gi->ball_dy < 0)
		{
			sp = -SPHERE;
		}
		else
		{
			sp = SPHERE;
		}


		n_t = (y1 - (gi->ball_y + sp)) / gi->ball_dy;

		b_x = (gi->ball_x + sp) + (n_t * gi->ball_dx);

		if (b_x > x1 && b_x < x2 && (n_t < t) && (n_t >= 0))
		{
			// YEP!
			return n_t;
		}
	}
	else
	{
		// GENERAL

		// do we have any???
		// no? 
		// no!
		// YAY!
		printf("collision detection error... i'm lazy\n");
	}

	return 1000.0;
}

bool BreakOut::CheckBallAgainstBlock(game_info* gi, float t, float &cur_t, int &type_t, int last_type, float x, float y, int isPaddle)
{
	float chk;

	if (isPaddle)
	{
		y += 0.5;
	}

	// check left edge
	chk = CheckBallAgainst(gi, t, (float)(x - 0.5), (float)(y - 0.25), (float)(x - 0.5), (float)(y-0.5) - 0.25);
	if (chk <= cur_t && !(1 << (3 + (isPaddle * 4)) != last_type) && gi->ball_dx > 0)
	{
		cur_t = chk;
		type_t |= 1 << (3 + (isPaddle * 4));
	}

	// check top edge
	chk = CheckBallAgainst(gi, t, (float)(x - 0.5), (float)(y - 0.25), (float)(x + 0.5), (float)(y - 0.25));
	if (chk <= cur_t && !(4 + (isPaddle * 4)) != last_type && gi->ball_dy < 0)
	{
		cur_t = chk;
		type_t = 1 << (4 + (isPaddle * 4));
	}

	// check right edge
	chk = CheckBallAgainst(gi, t, (float)(x + 0.5), (float)(y - 0.25), (float)(x + 0.5), (float)(y-0.5) - 0.25);
	if (chk <= cur_t && !(1 << (5 + (isPaddle * 4)) != last_type) && gi->ball_dx < 0)
	{
		cur_t = chk;
		type_t = 1 << (5 + (isPaddle * 4));
	}

	// check bottom edge
	chk = CheckBallAgainst(gi, t, (float)(x - 0.5), (float)(y-0.5) - 0.25, (float)(x + 0.5), (float)(y-0.5) - 0.25);
	if (chk <= cur_t && 6 != last_type && gi->ball_dy > 0)
	{
		cur_t = chk;
		type_t = 1 << (6 + (isPaddle * 4));
	}

	if (type_t & (15 << (3 + (isPaddle * 4))))
	{
		return true;
	}

	return false;
}

void BreakOut::MoveBall(game_info* gi, float t, int last_type)
{
	float cur_t = 1000.0;
	int type_t = 0;
	int board_i = -1;
	int board_j = -1;

	float up_t = CheckBallAgainst(gi, t, -5, 11.75, 10, 11.75);
	float left_t = CheckBallAgainst(gi, t, 0, 13, 0, 0);
	float right_t = CheckBallAgainst(gi, t, 4.5, 13, 4.5, 0);




	// check against borders

	if (gi->ball_dy > 0 && up_t < cur_t && !(1 != last_type))
	{
		cur_t = up_t;
		type_t |= 1;
	}

	if (gi->ball_dx > 0 && right_t < cur_t && !(2 & last_type))
	{
		cur_t = right_t;
		type_t |= 2;
	}

	if (gi->ball_dx < 0 && left_t < cur_t && !(4 & last_type))
	{
		cur_t = left_t;
		type_t |= 4;
	}






	int i,j;


	// check against the blocks

	for (i=0; i<10; i++)
	{
		for (j=0; j<24; j++)
		{
			if (gi->board[i][j] != -1)
			{
				if (CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, (float)(i * 0.5f), (float)(j+1) * 0.5f, 0))
				{
					board_i = i;
					board_j = j;

					j = 24;
					i = 10;
				}
			}
		}
	}





	// collision against paddle

	// for all of the blocks that make up the paddle... check against their edges

	float x,y;

	x = gi->fine;
	y = 0;
	
	switch (gi->curpiece)
	{
	case 0:
		if (gi->curdir % 2)
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-1.0, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y, 1);
		}
		else
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y+0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y+1.0, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y-0.5, 1);
		}
		break;
	case 1:
		if (gi->curdir % 2)
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y+0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y-0.5, 1);
		}
		else
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y-0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y-0.5, 1);
		}
		break;
	case 2:
		if (gi->curdir % 2)
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y+0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y-0.5, 1);
		}
		else
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y-0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y-0.5, 1);
		}
		break;
	case 3:
		CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y, 1);
		CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y+0.5, 1);
		CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
		CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y+0.5, 1);
		break;
	case 4:
		if (gi->curdir == 0)
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y+0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y-0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y+0.5, 1);
		}
		else if (gi->curdir == 1)
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y+0.5, 1);
		}
		else if (gi->curdir == 2)
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y+0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y-0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y-0.5, 1);
		}
		else
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y-0.5, 1);
		}
		break;
	case 5:
		if (gi->curdir == 0)
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y+0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y-0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y+0.5, 1);
		}
		else if (gi->curdir == 1)
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y-0.5, 1);
		}
		else if (gi->curdir == 2)
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y+0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y-0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y-0.5, 1);
		}
		else
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y+0.5, 1);
		}
		break;
	case 6:
		if (gi->curdir == 0)
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y-0.5, 1);
		}
		else if (gi->curdir == 1)
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y+0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y-0.5, 1);
		}
		else if (gi->curdir == 2)
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x+0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y+0.5, 1);
		}
		else
		{
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x-0.5, y, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y+0.5, 1);
			CheckBallAgainstBlock(gi, t, cur_t, type_t, last_type, x, y-0.5, 1);
		}
		break;
	}



	// adjust ball, call again if required

	// no collisions?
	if (type_t == 0)
	{
		// use up all t!
		gi->ball_x += t * gi->ball_dx;
		gi->ball_y += t * gi->ball_dy;
		return;
	}

	// we have a collision, move as far as we can
	gi->ball_x += cur_t * gi->ball_dx;
	gi->ball_y += cur_t * gi->ball_dy;

	engine.audio.PlaySound(SND_BOUNCE);

	// then, change direction, and move the rest of the way

	t -= cur_t;

	if (type_t & ~0x7)
	{
		gi->break_out_consecutives++;
	}

	if (type_t & 1)
	{ // top
		gi->ball_dy = -gi->ball_dy;
	} 
	else if (type_t & 2)
	{ // right
		gi->ball_dx = -gi->ball_dx;
	}
	else if (type_t & 4)
	{ // left
		gi->ball_dx = -gi->ball_dx;
	}

	else if (type_t & 8)
	{ // left side block
		gi->ball_dx = -gi->ball_dx;

		// get rid of block???
		gi->board[board_i][board_j] = -1;

		engine.PassMessage(MSG_REMOVEBLOCK, board_i, board_j, 0);

		gi->score += (2 * 100);
		engine.PassMessage(MSG_APPENDSCORE, 100, 2, 0);
	}
	else if (type_t & 16)
	{ // top side block
		gi->ball_dy = -gi->ball_dy;

		// get rid of block???
		gi->board[board_i][board_j] = -1;

		engine.PassMessage(MSG_REMOVEBLOCK, board_i, board_j, 0);

		gi->score += (2 * 100);
		engine.PassMessage(MSG_APPENDSCORE, 100, 2, 0);
	}
	else if (type_t & 32)
	{ // right side block
		gi->ball_dx = -gi->ball_dx;

		// get rid of block???
		gi->board[board_i][board_j] = -1;

		engine.PassMessage(MSG_REMOVEBLOCK, board_i, board_j, 0);

		gi->score += (2 * 100);
		engine.PassMessage(MSG_APPENDSCORE, 100, 2, 0);
	}
	else if (type_t & 64)
	{ // bottom side block
		gi->ball_dy = -gi->ball_dy;

		// get rid of block???
		gi->board[board_i][board_j] = -1;

		engine.PassMessage(MSG_REMOVEBLOCK, board_i, board_j, 0);

		gi->score += (2 * 100);
		engine.PassMessage(MSG_APPENDSCORE, 100, 2, 0);
	}


		// paddle
	else if (type_t & 128)
	{ 
		if (gi->break_out_consecutives >= 7)
		{
			engine.SendAttack(3);
		}
		else if (gi->break_out_consecutives >= 5)
		{
			engine.SendAttack(2);
		}
		else if (gi->break_out_consecutives >= 4)
		{
			engine.SendAttack(1);
		}

		gi->break_out_consecutives = 0;

		gi->ball_dx = -gi->ball_dx;
	}

	else if (type_t & 256)
	{
		if (gi->break_out_consecutives >= 7)
		{
			engine.SendAttack(3);
		}
		else if (gi->break_out_consecutives >= 5)
		{
			engine.SendAttack(2);
		}
		else if (gi->break_out_consecutives >= 4)
		{
			engine.SendAttack(1);
		}

		gi->break_out_consecutives = 0;

		gi->ball_dy = -gi->ball_dy;
	}

	else if (type_t & 512)
	{
		if (gi->break_out_consecutives >= 7)
		{
			engine.SendAttack(3);
		}
		else if (gi->break_out_consecutives >= 5)
		{
			engine.SendAttack(2);
		}
		else if (gi->break_out_consecutives >= 4)
		{
			engine.SendAttack(1);
		}

		gi->break_out_consecutives = 0;

		gi->ball_dx = -gi->ball_dx;
	}

	else if (type_t & 1024)
	{
		if (gi->break_out_consecutives >= 7)
		{
			engine.SendAttack(3);
		}
		else if (gi->break_out_consecutives >= 5)
		{
			engine.SendAttack(2);
		}
		else if (gi->break_out_consecutives >= 4)
		{
			engine.SendAttack(1);
		}

		gi->break_out_consecutives = 0;

		gi->ball_dy = -gi->ball_dy;		
	}

	// call this again
	MoveBall(gi, t, type_t);
}

void BreakOut::Update(game_info* gi, float deltatime)
{
	bool move = false;

	if (gi->state == STATE_BREAKOUT_TRANS)
	{
		gi->rot2 -= TRANSITION_SPEED * deltatime;

		if (gi->rot2 <= 0)
		{
			gi->rot2 = 0;
			engine.ChangeState(gi, STATE_TETRIS);
		}

		engine.PassMessage(MSG_ROT_BOARD2, (gi->rot2 / 180.0f) * 255.0f, 0,0);
		return;
	}

	if (engine.keys[SDLK_LEFT])
	{
		gi->fine -= BREAKOUT_PADDLE_SPEED * deltatime;

		float amt = GetLeftBounds(gi);

		if (gi->fine < amt)
		{
			gi->fine = amt;
		}

		move = true;
	}
	
	if (engine.keys[SDLK_RIGHT])
	{
		gi->fine += BREAKOUT_PADDLE_SPEED * deltatime;

		float amt = GetRightBounds(gi);

		if (gi->fine > amt)
		{
			gi->fine = amt;
		}

		move = true;
	}

	gi->break_out_time -= deltatime;

	if (gi->break_out_time <= 0)
	{
		gi->break_out_time = 0;

		engine.DisplayMessage(STR_YOUSURVIVED);
		engine.audio.PlaySound(SND_CHANGEVIEW);
		engine.ChangeState(gi, STATE_BREAKOUT_TRANS);

		gi->pos = (int)(gi->fine / 0.5f);
		gi->fine = 0;
		return;
	}

	if (gi->ball_fast > 0)
	{
		gi->ball_fast -= deltatime;

		if (gi->ball_fast < 0)
		{
			gi->ball_fast = 0;
			if (gi->ball_dx < 0)
			{
				gi->ball_dx = -BREAKOUT_BALL_SPEED_X;
			}
			else
			{
				gi->ball_dx = BREAKOUT_BALL_SPEED_X;
			}
			if (gi->ball_dy < 0)
			{
				gi->ball_dy = -BREAKOUT_BALL_SPEED_Y;
			}
			else
			{
				gi->ball_dy = BREAKOUT_BALL_SPEED_Y;
			}
		}
	}

	if (move)
	{
		engine.PassMessage(MSG_UPDATEPADDLE, (unsigned char)((gi->fine / 11.0f) * 255.0f), 0, 0);
	}

	// move ball

	// solve for all collisions!

	// wall collisions!

	if (!engine.network_thread)
	{
			if (gi->ball_dx < 0)
			{
				gi->ball_dx = -(BREAKOUT_BALL_SPEED_X + (LEVEL * 0.2));
			}
			else
			{
				gi->ball_dx = (BREAKOUT_BALL_SPEED_X + (LEVEL * 0.2));
			}
			if (gi->ball_dy < 0)
			{
				gi->ball_dy = -(BREAKOUT_BALL_SPEED_Y + (LEVEL * 0.2));
			}
			else
			{
				gi->ball_dy = (BREAKOUT_BALL_SPEED_Y + (LEVEL * 0.2));
			}
	}

	MoveBall(gi,deltatime,-1);

	engine.PassMessage(MSG_UPDATEBALL, ((float)(gi->ball_x) / 20.0f) * 255.0f, ((float)(gi->ball_y) / 20.0f) * 255.0f, 0);

	if (gi->ball_y < -1.5)
	{
		engine.GameOver();
	}
}

void BreakOut::DrawBall(game_info* gi)
{	

	float aspect = (600.0f/800.0f);

	glPushMatrix();

	// translate to world
	glTranslatef(gi->side * 3.75f,0,0);

	// rotate
	glRotatef(gi->side * gi->rot,0,1,0);
	glRotatef(-gi->rot2,1,0,0);

	// translate
	glTranslatef(-2.25 + (gi->ball_x), 5.875 - (gi->ball_y),0);

	// scale
	glScalef(aspect,1,1);

	glutSolidSphere(SPHERE_SIZE,30,30);

	glPopMatrix();
}

void BreakOut::Draw(game_info* gi)
{
	engine.tetris.DrawBoard(gi);

	if (gi->state == STATE_BREAKOUT_TRANS)
	{
		engine.tetris.DrawPiece(gi, (0.5) * (double)gi->pos, gi->fine);
	}
	else
	{
		engine.tetris.DrawPiece(gi, gi->fine, 0);
	}

	DrawBall(gi);
}

void BreakOut::DrawOrtho(game_info* gi)
{
	if (gi->side == -1)
	{
		engine.DrawString(":CONS", 0,(400.0f - 32.0f) - (6 * 16),25.0f);

		int x  = engine.IntLength(gi->break_out_consecutives);

		engine.DrawInt(gi->break_out_consecutives, 1, (400.0f - 32.0f) - ((6 + x) * 16), 25.0f);

		int x2;

		x2 = (400 - (14 * 16)) / 2;

		engine.DrawString("SURVIVE:", 2, x2, 600.0f - 25.0f);
		x2 += (8 * 16);
		engine.DrawInt(gi->break_out_time, 3, x2, 600.0f - 25.0f);
		x2 += (engine.IntLength(gi->break_out_time + 0.5) * 16);
		engine.DrawString(" SEC", 2, x2, 600.0f - 25.0f);

	}
}

void BreakOut::KeyRepeat(game_info* gi)
{
	if (engine.keys[SDLK_UP])
	{
		gi->curdir++;
		gi->curdir %= 4;

		double amt = GetRightBounds(gi);

		if (gi->fine > amt)
		{
			gi->curdir--;
			gi->curdir %= 4;
		}

		amt = GetLeftBounds(gi);

		if (gi->fine < amt)
		{
			gi->curdir--;
			gi->curdir %= 4;
		}
		
		engine.PassMessage(MSG_UPDATEPIECE, gi->pos, gi->curdir, gi->curpiece);
	}
}

void BreakOut::KeyDown(game_info* gi, Uint32 key)
{
}

void BreakOut::KeyUp(game_info* gi, Uint32 key)
{
}

void BreakOut::MouseDown(game_info* gi)
{
}

void BreakOut::MouseMovement(game_info* gi, Uint32 x, Uint32 y)
{
}

float BreakOut::GetLeftBounds(game_info* gi)
{
	int sx;
	sx = (int)(gi->fine / 0.5);

	switch (gi->curpiece)
	{
	case 0:
		if (gi->curdir % 2)
		{
			if (sx < 2) { return 1.0; }
		}
		else
		{
			if (sx < 0) { return 0; }
		}
		break;
	case 1:
		if (gi->curdir % 2)
		{
			if (sx < 0) { return 0; }
		}
		else
		{
			if (sx < 1) { return 0.5; }
		}
		break;
	case 2:
		if (sx < 1) { return 0.5; }		
		break;
	case 3:
		if (sx < 0) { return 0; }
		break;
	case 4:
		if (gi->curdir == 0)
		{
			if (sx < 0) { return 0; }
		}
		else 
		{
			if (sx < 1) { return 0.5; }
		}
		break;
	case 5:
		if (gi->curdir == 2)
		{
			if (sx < 0) { return 0; }
		}
		else
		{
			if (sx < 1) { return 0.5; }
		}
		break;
	case 6:
		if (gi->curdir == 1)
		{
			return 0;
		}
		else
		{
			return 0.5;
		}
		break;
	}

	return 0;
}

float BreakOut::GetRightBounds(game_info* gi)
{
	
	int sx;
	sx = (int)(gi->fine / 0.5);

	switch (gi->curpiece)
	{
	case 0:
		if (gi->curdir % 2)
		{
			return 4.0;
		}
		else
		{
			return 4.5;
		}
		break;
	case 1:
		return 4.0;
		break;
	case 2:
		if (gi->curdir % 2)
		{
			return 4.5;
		}
		else
		{
			return 4.0;
		}
		break;
	case 3:
		return 4.0;
		break;
	case 4:
		if (gi->curdir == 2)
		{
			return 4.5;
		}
		else 
		{
			return 4.0;
		}
		break;
	case 5:
		if (gi->curdir == 0)
		{
			return 4.5;
		}
		else
		{
			return 4.0;
		}
		break;
	case 6:
		if (gi->curdir == 3)
		{
			return 4.5;
		}
		else
		{
			return 4.0;
		}
		break;
	}

	return 10;
}


void BreakOut::Attack(game_info* gi, int severity)
{
	if (severity == 1)
	{
		int pos = gi->pos;
		float fine = gi->fine;

		engine.tetris.GetNewPiece(gi);

		gi->pos = pos;
		gi->fine = fine;

		float amt = GetLeftBounds(gi);

		if (gi->fine < amt)
		{
			gi->fine = amt;
		}

		amt = GetRightBounds(gi);

		if (gi->fine > amt)
		{
			gi->fine = amt;
		}

		engine.PassMessage(MSG_UPDATEPADDLE, (unsigned char)((gi->fine / 11.0f) * 255.0f), 0, 0);
	}
	else if (severity == 2)
	{
		engine.tetris.Attack(gi, 1);
	}
	else if (severity == 3)
	{
		gi->ball_fast = 7;
		if (gi->ball_dx < 0)
		{
			gi->ball_dx = -BREAKOUT_BALL_SPEEDY_X;
		}
		else
		{
			gi->ball_dx = BREAKOUT_BALL_SPEEDY_X;
		}
		if (gi->ball_dy < 0)
		{
			gi->ball_dy = -BREAKOUT_BALL_SPEEDY_Y;
		}
		else
		{
			gi->ball_dy = BREAKOUT_BALL_SPEEDY_Y;
		}
	}
}
