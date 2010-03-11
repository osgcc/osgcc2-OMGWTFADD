
#ifndef TETRIS_INCLUDED
#define TETRIS_INCLUDED

#include "game.h"

class Tetris : public Game
{
public:

	// conventions:
	void Update(game_info* gi, float deltatime);
	void Draw(game_info* gi);
	void DrawOrtho(game_info* gi);

	void KeyDown(game_info* gi, Uint32 key);
	void KeyUp(game_info* gi, Uint32 key);
	void KeyRepeat(game_info* gi);

	void Attack(game_info* gi, int severity);

	void MouseMovement(game_info* gi, Uint32 x, Uint32 y);
	void MouseDown(game_info* gi);

	void InitGame(game_info* gi);


	// stuffs:

	void GetNewPiece(game_info* gi);

	void DrawBoard(game_info* gi);
	void DrawPiece(game_info* gi, double x, double y);
	void DrawBlock(int type, game_info* gi, double x, double y);

	void AddPiece(game_info* gi);
	void AddPiece(game_info* gi, int start_x, int start_y);
	void AddBlock(game_info* gi, int i, int j, int type);

	void DropPiece(game_info* gi);

	int ClearLines(game_info* gi);

	void PushUp(game_info* gi, int num);
	void DropLine(game_info* gi, int lineIndex);

	bool TestGameOver(game_info* gi);

	bool TestCollisionBlock(game_info* gi, double x, double y);
	bool TestCollision(game_info* gi);
	bool TestCollision(game_info* gi, double x, double y);

	double TestSideCollision(game_info* gi, double x, double y);

	// materials:

	// board posts:
	static GLfloat board_piece_amb[4];
	static GLfloat board_piece_diff[4];
	static GLfloat board_piece_spec[4];
	static GLfloat board_piece_shine;
	static GLfloat board_piece_emi[4];

	// block materials		
	static GLfloat tet_piece_amb[4];
	static GLfloat tet_piece_diff[6][4];
	static GLfloat tet_piece_spec[4];
	static GLfloat tet_piece_emi[4];
	static GLfloat tet_piece_shine;

};

#endif
