


#ifndef MAIN_INCLUDED
#define MAIN_INCLUDED

// libraries (if in visual studio!)
#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "opengl32.lib")  // link with Microsoft OpenGL lib
#pragma comment(lib, "glu32.lib")     // link with Microsoft OpenGL Utility lib
#pragma comment(lib, "glut32.lib")    // link with Win32 GLUT lib
#pragma comment(lib, "SDL_image.lib")
#pragma comment(lib, "SDL_net.lib")
#pragma comment(lib, "SDL_mixer.lib")
#endif

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_net.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "GL/glut.h"

extern const char* strings[7];

// Strings

#define STR_ATTACK 0
#define STR_TRANSITION 1
#define STR_SUPER 2
#define STR_TETRIS 3
#define STR_YOULOSE 4
#define STR_YOUWIN 5
#define STR_YOUSURVIVED 6

// States

#define STATE_TETRIS 0
#define STATE_TETRIS_TRANS 1
#define STATE_BREAKOUT 2
#define STATE_BREAKOUT_TRANS 3

// Textures
#define TEXTURE_BLOCK1 0
#define TEXTURE_BLOCK2 1
#define TEXTURE_BLOCK3 2
#define TEXTURE_BLOCK4 3
#define TEXTURE_BLOCK5 4
#define TEXTURE_BLOCK6 5
#define TEXTURE_BLOCK7 6

#define TEXTURE_BG1 7
#define TEXTURE_BG2 8

#define TEXTURE_BALL 9

#define TEXTURE_SPACEPENGUIN 10

#define TEXTURE_NUMBERS 11
#define TEXTURE_LETTERS 12

#define TEXTURE_PENGUIN 13
#define TEXTURE_SPEECH 14

#define TEXTURE_LETTERS_WHITE 15

// BG

#define BG1_SPEED_X 0.13f
#define BG1_SPEED_Y 0.15f

#define BG2_SPEED_X 0.53f
#define BG2_SPEED_Y -0.48f

// Other
 
#define BOARD_NORMAL_ROT 0.0f
#define SCROLL_CONSTRAINT 30 

#define SPHERE_SIZE 0.125f

#define TETRIS_LINES_NEEDED 10
#define BREAK_OUT_SECONDS 45

#define SCORE_TO_LEVEL 5000
#define LEVEL (engine.player1.score / SCORE_TO_LEVEL)

// Velocities (units per second)

#define TETRIS_SPEED 2.5f
#define TETRIS_ATTACK_ROT_SPEED 30.0f
#define TRANSITION_SPEED 70.0f

#define BREAKOUT_BALL_SPEED_X 4.3f
#define BREAKOUT_BALL_SPEED_Y 4.3f

#define BREAKOUT_BALL_SPEEDY_X 5.9f
#define BREAKOUT_BALL_SPEEDY_Y 5.9f

#define BREAKOUT_PADDLE_SPEED 4.0f

// messages
#define MSG_ADDPIECE 0
#define MSG_DROPLINE 1
#define MSG_ATTACK 2
#define MSG_PUSHUP 3
#define MSG_ADDBLOCKS_A 4
#define MSG_ADDBLOCKS_B 5
#define MSG_ADDBLOCKS_C 6
#define MSG_ADDBLOCKS_D 7
#define MSG_ADDBLOCKS2_A 8
#define MSG_ADDBLOCKS2_B 9
#define MSG_ADDBLOCKS2_C 10
#define MSG_ADDBLOCKS2_D 11
#define MSG_UPDATEPIECE 12
#define MSG_UPDATEPIECEY 13
#define MSG_ROT_BOARD 14
#define MSG_CHANGE_STATE 15
#define MSG_ROT_BOARD2 16

#define MSG_UPDATEBALL 17
#define MSG_UPDATEPADDLE 18
#define MSG_REMOVEBLOCK 19

#define MSG_GAMEOVER 20

#define MSG_APPENDSCORE 21

// sounds
#define SND_ADDLINE 0
#define SND_TINK 1
#define SND_PENGUIN 2
#define SND_BOUNCE 3
#define SND_CHANGEVIEW 4
#define SND_MUSIC 5

	struct game_info
	{
		// board
		char board[10][24];

		int pos; // column/row position
		float fine; // a floating position

		// side, tells whether to move left, or move right
		float side;

		int attacking;
		float attack_rot;

		float rot;
		float rot2;

		int curpiece;
		int curdir;

		int curgame;

		int state;

		int score;

		float message_uptime;
		const char* message;

		float ball_fast;
		float break_out_time;

		int break_out_consecutives;



		int total_lines;
		int state_lines;



		// oops

		float ball_x;
		float ball_y;

		float ball_dx;
		float ball_dy;
	};
#endif //MAIN_INCLUDED
