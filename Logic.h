/*

    Copyright 2006 Daniele Faggi (Delta6)

    This file is part of Invaders.

    Invaders is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Invaders is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Invaders.  If not, see <http://www.gnu.org/licenses/>.

*/

// Defines the game logic


#define SCREEN_WIDTH	 640
#define SCREEN_HEIGHT    400

#define TANK_STARTUP_X    32
#define TANK_STARTUP_Y   350
#define TANK_MIN_X        32
#define TANK_MAX_X       639 - 64
#define TANK_SHOOT_MIN_Y   0

#define ALIEN_MIN_X		      6
#define ALIEN_MAX_X	        (640 - 32) - 6
#define ALIEN_X_SPACE   5
#define ALIEN_Y_SPACE   5

#define ALIEN_TYPE_0    0
#define ALIEN_TYPE_1	1
#define ALIEN_TYPE_2	2

#define ALIEN_SHOOT_NORMAL 0
#define ALIEN_SHOOT_BOMB   1

#define ALIEN_SHOOT_Y_MAX	370

#define EXPLOSION_FRAMES   3

#define BARRIER_Y_POSITION 300
#define BARRIER_WIDTH       64
#define BARRIER_HEIGHT	    32

#define EXPLOSION_TYPE_FULL		0
#define EXPLOSION_TYPE_HALF		1

#define BEGIN_LEVEL_TIME_WAIT	90

typedef struct shoot_s {

	int position_x;			// Shoot X position
	int position_y;			// Shoot Y position
	int frame;				// Shoot animation frame
	int speed;				// Shoot speed
	int type;				// Shoot type

	struct shoot_s* next;   // Next shoot (simple linked list)

} shoot_t;


typedef struct tank_s {

	int position_x;			// Tank X position
	int position_y;			// Tank Y position

} tank_t;


typedef struct alien_s {

	int position_x;			// Alien X position
	int position_y;			// Alien Y position

	int frame;				// Animation frame

	int type;				// Alien type

							// Add here new behaviour vars
	
	struct alien_s* next;	// Next alien (simple linked list)

} alien_t;


typedef struct mship_s {

	int position_x;			// Mothership X position
	int position_y;			// Mothership Y position

	BOOL direction;			// Advancement left to right or right to left

} mship_t;

typedef struct barrier_s {
	
	int position_x;			// Barrier X position
	int position_y;			// Barrier Y position

	int damage;				// Barrier damage

	struct barrier_s* next;	// Next Barrier (simple linked list)

} barrier_t;


typedef struct explosion_s {

	int position_x;			// Explosion X position
	int position_y;			// Explosion Y position
	int move_x;
	int move_y;

	int frame;				// Explosion frame

	int type;				// Explosion type

	struct explosion_s* next; // Next Explosion (simple linked list) 

} explosion_t;


typedef struct visualtext_s {

	RECT rect;				// Text rectangle
	TCHAR text[256];		// Display text
	int  timeout;			// Timeout frames (when 0 cancel the text)

} visualtext_t;

typedef struct game_vars_s {

	tank_t			*tank;			// Tank variables
	shoot_t			*tank_shoot;	// Tank shoots
	
	alien_t			*alien;			// Aliens variables
	shoot_t			*alien_shoot;	// Aliens shoots

	barrier_t		*barrier;		// Barriers variables

	explosion_t		*explosion;		// Explosion variables
	
	mship_t			*mship;			// Mothership

	visualtext_t	*visualtext;	// Text to be shown

							// Add here additional behaviour variables

	BOOL	alien_direction;	// Left or Right Movement
	int 	alien_advance;		// Advance Movement
	int		alien_speed;		// Group speed
	int		alien_step_speed;	// Speed Counter
	BOOL	alien_enter;		// Signal aliens are entering in the game

	int     level;				// Game Level
	int		enter_level_timer;	// Timer used to show level at beginning of each level

	int		score;				// Player Score
	int		lives;				// Player Lives

} game_vars_t;


void InitializeGameVars();
void InitializeTank();
void InitializeAliens();
void InitializeBarriers();

void FreeGameVars();

game_vars_t* GetGameVars();

void TankFire();
void AlienFire(alien_t* ptr);
void FireExplosion(int x, int y, int dx, int dy, int type);

BOOL CheckTankShootCollision(shoot_t* shoot);
BOOL CheckAlienShootCollision(shoot_t* shoot);

void TankStartLeft();
void TankStartRight();
void TankStopLeft();
void TankStopRight();

int CountAliens();

void ExplodeBarriers();
void ExplodeBarrier(int x, int y);
void ExplodeMShip(int x, int y);

void UpdateVars();

void PlaceVisualText(int x, int y, int width, int height, TCHAR *text, int timeout) ;
