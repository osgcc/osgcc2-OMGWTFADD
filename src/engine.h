
#ifndef ENGINE_INCLUDED
#define ENGINE_INCLUDED

#include "main.h"
#include "tetris.h"
#include "breakout.h"

#include "audio.h"

class Engine
{
public:

	Engine();
	~Engine();

	// init, uninit

	void Init();
	void Quit();

	// network

	void RunServer(int port);
	void RunClient(char* ip, int port);

	void ProcessMessage(unsigned char msg[4]);
	void PassMessage(unsigned char msgID, unsigned char p1, unsigned char p2, unsigned char p3);

	// game loop

	void GameLoop();

	void GameOver();
 
	// frame stuffs

	int IntLength(int i);
	int DrawInt(int i, int color, float x, float y);
	int _DrawString(const char* str, int color, float x, float y, int tx);
	int DrawString(const char* str, int color, float x, float y);
	int DrawStringWhite(const char* str, int color, float x, float y);

	void Update(float deltatime);
	void Draw();

	// key processing
	
	void KeyDown(Uint32 key);
	void KeyUp(Uint32 key);

	// mouse

	void MouseMovement(Uint32 x, Uint32 y);
	void MouseDown();

	// graphics

	void DrawCube();
	void DrawQuadXY(float x, float y, float z, float w, float h);
	void DrawQuad(int a, int b, int c, int d);

	// state

	int state;

	void ChangeState(game_info* gi, int newState);
	void InitState(game_info* gi);
	void UninitState(game_info* gi);

	// common game logic

	void ClearGameData(game_info* player);

	// textures

	void UseTexture(int textureIndex, int startx, int starty, int width, int height);
	void UseTextureUpsideDown(int textureIndex, int startx, int starty, int width, int height);
	void EnableTextures();
	void DisableTextures();
	int AddTexture(const char* fname);

	void SendAttack(int severity);
	void PerformAttack(int severity);

	void DisplayMessage(int stringIndex);







	// vars

	static GLfloat cubecoords[8][4];
	static GLfloat cubenorms[8][4];
	
	static int gamecount;
	static Game* games[];

	static Tetris tetris;
	static BreakOut breakout;
	static Audio audio;

	static game_info player1;
	static game_info player2;

	static int quit;

	static int inplay;

	static float space_penguinx;
	static float space_penguiny;
	static float space_penguindx;
	static float space_penguindy;

	static float space_penguinrot;

	static GLuint* textures;
	static int* texture_widths;
	static int* texture_heights;
	static int texture_count;
	static int texture_capacity;

	static GLfloat tu[2];
	static GLfloat tv[2];

	static double repeatTime;
	static double titleChangeTime;
	static double time;

	static int keys[0xffff];

	// background
	static float bg1x;
	static float bg1y;
	
	static float bg2x;
	static float bg2y;

	// networking
	
	static IPaddress ip;
	static TCPsocket tcpsock;
	static TCPsocket client_tcpsock;
	static SDL_Thread *network_thread;
};


#endif //ENGINE_INCLUDED
