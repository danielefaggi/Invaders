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

#include "stdafx.h"
#include "resource.h"
#include <stdio.h>
#include <assert.h>

game_vars_t* game_vars = NULL;

BOOL bTankLeft = FALSE;
BOOL bTankRight = FALSE;

void InitializeGameVars() {

	game_vars = (game_vars_t*) malloc(sizeof(game_vars_t));
	assert(game_vars != NULL);

	memset(game_vars, 0, sizeof(game_vars_t));
	game_vars->level = 0;
	game_vars->enter_level_timer = BEGIN_LEVEL_TIME_WAIT;
	game_vars->lives = 5;
	
}

void FreeGameVars() {
	

	//Cleanup allocated memory

	if(game_vars->tank != NULL) free(game_vars->tank);
	if(game_vars->mship != NULL) free(game_vars->mship);
	
	if(game_vars->tank_shoot != NULL) {
		shoot_t* ptr = game_vars->tank_shoot;
		shoot_t* ptr_n;
		do {
			ptr_n = ptr->next;
			free(ptr);
			ptr = ptr_n;
		} while(ptr != NULL);
	}

	if(game_vars->alien_shoot != NULL) {
		shoot_t* ptr = game_vars->alien_shoot;
		shoot_t* ptr_n;
		do {
			ptr_n = ptr->next;
			free(ptr);
			ptr = ptr_n;
		} while(ptr != NULL);
	}

	if(game_vars->alien != NULL) {
		alien_t* ptr = game_vars->alien;
		alien_t* ptr_n;
		do {
			ptr_n = ptr->next;
			free(ptr);
			ptr = ptr_n;
		} while(ptr != NULL);
	}

	if(game_vars->barrier != NULL) {
		barrier_t* ptr = game_vars->barrier;
		barrier_t* ptr_n;
		do {
			ptr_n = ptr->next;
			free(ptr);
			ptr = ptr_n;
		} while(ptr != NULL);
	}

	if(game_vars->explosion != NULL) {
		explosion_t* ptr = game_vars->explosion;
		explosion_t* ptr_n;
		do {
			ptr_n = ptr->next;
			free(ptr);
			ptr = ptr_n;
		} while(ptr != NULL);
	}

}

game_vars_t* GetGameVars() {

	return game_vars;

}

void InitializeTank() {

	game_vars->tank = (tank_t*) malloc(sizeof(tank_t));
	
	if(game_vars->tank != NULL) { 
		
		memset(game_vars->tank, 0, sizeof(tank_t));

		game_vars->tank->position_x = TANK_STARTUP_X;
		game_vars->tank->position_y = TANK_STARTUP_Y;
	}

}

void TankFire() {

	if(game_vars->tank == NULL) return;

	if(game_vars->tank_shoot == NULL) {
		game_vars->tank_shoot = (shoot_t*) malloc(sizeof(shoot_t));
		if(game_vars->tank_shoot != NULL) {

			memset(game_vars->tank_shoot, 0, sizeof(shoot_t));

			game_vars->tank_shoot->position_x = game_vars->tank->position_x;
			game_vars->tank_shoot->position_y = game_vars->tank->position_y;
			game_vars->tank_shoot->speed = 10;

			PerformSound(SOUND_LASER);

		}
	}
}


// Tank input decode

void TankStartLeft() {
	bTankLeft = TRUE;
}

void TankStartRight() {
	bTankRight = TRUE;
}
void TankStopLeft() {
	bTankLeft = FALSE;
}

void TankStopRight() {
	bTankRight = FALSE;
}

// Update the game variables 

void UpdateVars() {


	if(game_vars->enter_level_timer > 0) {
		game_vars->enter_level_timer--;
		if(game_vars->enter_level_timer == 0) {
			
			// Delete old barriers
			
			if(game_vars->barrier != NULL) {
				barrier_t* ptr = game_vars->barrier;
				barrier_t* ptr_n;
				do {
					ptr_n = ptr->next;
					free(ptr);
					ptr = ptr_n;
				} while(ptr != NULL);
			}

			InitializeBarriers();
			InitializeAliens();
		}
	} 

	// Check and move Explosions
	if(game_vars->explosion != NULL) {
		
		explosion_t* ptr = game_vars->explosion;
		do {
			ptr->position_y += ptr->move_y;
			ptr->position_x += ptr->move_x;

			ptr->frame++;

			ptr = ptr->next;

		} while(ptr != NULL);

		ptr = game_vars->explosion;
		while(ptr->next != NULL) {
			if((ptr->next->frame >= EXPLOSION_FRAMES && ptr->next->type == EXPLOSION_TYPE_FULL) ||
			   (ptr->next->frame >= 1 && ptr->next->type == EXPLOSION_TYPE_HALF)) {
				explosion_t *ptr1 = ptr->next;
				ptr->next = ptr->next->next;
				free(ptr1);
			}
			ptr = ptr->next;
			if(ptr == NULL) break;
		}

		if((game_vars->explosion->frame >= EXPLOSION_FRAMES && game_vars->explosion->type == EXPLOSION_TYPE_FULL) ||
		   (game_vars->explosion->frame >= 1 && game_vars->explosion->type == EXPLOSION_TYPE_HALF)) {
			ptr = game_vars->explosion;
			game_vars->explosion = game_vars->explosion->next;
			free(ptr);
		}
	}

	// Check and move Tank

	if(game_vars->tank != NULL) {
		if(bTankLeft) {
			game_vars->tank->position_x-=3;
			if(game_vars->tank->position_x < TANK_MIN_X) {
				game_vars->tank->position_x = TANK_MIN_X;
			}
		}
		if(bTankRight) {
			game_vars->tank->position_x+=3;
			if(game_vars->tank->position_x > TANK_MAX_X) {
				game_vars->tank->position_x = TANK_MAX_X;
			}
		}

	}

	// Check and move Tank Shoots

	if(game_vars->tank_shoot != NULL) {
		shoot_t* ptr_prev = NULL;
		shoot_t* ptr = game_vars->tank_shoot;
		do {
			ptr->position_y -= ptr->speed;

			// Check collisions
			BOOL bHit = CheckTankShootCollision(ptr);

			if(ptr->position_y < TANK_SHOOT_MIN_Y || bHit) {
				if(ptr_prev == NULL) {
					game_vars->tank_shoot = ptr->next;
					FireExplosion(ptr->position_x, ptr->position_y, 0, 0, EXPLOSION_TYPE_HALF);
					free(ptr);
					ptr = game_vars->tank_shoot;    // Adjust for next					
				} else {
					ptr_prev->next = ptr->next;    
					FireExplosion(ptr->position_x, ptr->position_y, 0, 0, EXPLOSION_TYPE_HALF);
					free(ptr);
					ptr = ptr_prev;					// Adjust for next
				}
			} else {			
				ptr = ptr->next;
			}
		} while(ptr != NULL);
	}	


	// Move mothership

	if((rand() * 1000) / RAND_MAX > 998 && 
		!game_vars->alien_enter && 
		game_vars->enter_level_timer == 0) {
		if(game_vars->mship == NULL) {
			game_vars->mship = (mship_t*) malloc(sizeof(mship_t));
			if((rand() * 1000) / RAND_MAX > 500) {
				game_vars->mship->position_x = SCREEN_WIDTH;
				game_vars->mship->position_y = 12;
				game_vars->mship->direction = FALSE;
			} else {
				game_vars->mship->position_x = -64;
				game_vars->mship->position_y = 12;
				game_vars->mship->direction = TRUE;
			}
		}
	}

	if(game_vars->mship != NULL) {
		if(game_vars->mship->direction) {
			game_vars->mship->position_x += 2;
			if(game_vars->mship->position_x > SCREEN_WIDTH) {
				free(game_vars->mship);
				game_vars->mship = NULL;
			}
		} else {
			game_vars->mship->position_x -= 2;
			if(game_vars->mship->position_x + 64 < 0) {
				free(game_vars->mship);
				game_vars->mship = NULL;
			}
		}
	}

	// Check and move Aliens

	BOOL bChangeDirection = FALSE;

	// Delayer for aliens
	BOOL bMoveAliens = FALSE;
	if(game_vars->alien_step_speed > 0) {	
		game_vars->alien_step_speed--;
	} else {
		game_vars->alien_step_speed = game_vars->alien_speed;
		bMoveAliens = TRUE;
	}


	if(!(game_vars->lives == 0 && game_vars->tank == NULL)) {
		if(game_vars->alien != NULL) {

			alien_t* ptr = game_vars->alien;

			do {
			
				if(bMoveAliens || game_vars->alien_enter) {

					ptr->frame = ((++ptr->frame) % 2);

				
					if(game_vars->alien_advance <= 0) {

						if(ptr->next == NULL)
							game_vars->alien_enter = FALSE;
						
						if(game_vars->alien_direction) {
							ptr->position_x += 6;
							bChangeDirection = bChangeDirection || 
								((ptr->position_x > ALIEN_MAX_X) && game_vars->alien_direction);
						} else {
							ptr->position_x -= 6;
							bChangeDirection = bChangeDirection || 
								((ptr->position_x < ALIEN_MIN_X) && (!game_vars->alien_direction));
						}
						
					} else {

						// Aliens at barrier level
						
						ptr->position_y += 6;
						if(ptr->position_y + 26 > BARRIER_Y_POSITION + 7) {
							ExplodeBarriers();
						}

						// Invaded

						if(ptr->position_y + 26 > TANK_STARTUP_Y + 4) {
							
							game_vars->lives = 0;
							
							if(game_vars->tank != NULL) {
								tank_t* ptrt = game_vars->tank;

								PerformSound(SOUND_BIG_EXPLOSION);

								FireExplosion(ptrt->position_x,      ptrt->position_y, -4, -4, EXPLOSION_TYPE_FULL);
								FireExplosion(ptrt->position_x + 4,  ptrt->position_y, -2, -2, EXPLOSION_TYPE_FULL);
								FireExplosion(ptrt->position_x,      ptrt->position_y,  2, -2, EXPLOSION_TYPE_FULL);
								FireExplosion(ptrt->position_x -4,   ptrt->position_y,  4, -4, EXPLOSION_TYPE_FULL);
															
								game_vars->tank = NULL;
								free(ptrt);
							}
						}

					}
				}

				// Check if can fire
				if(rand() < (RAND_MAX) / (200 / max((game_vars->level/2+1>5?5:game_vars->level/2+1),
												    6-(game_vars->alien_speed/2+1>5?5:game_vars->alien_speed/2+1)) ) ) {
					BOOL bLineFree = TRUE;
					alien_t* ptr1 = game_vars->alien;
					do {
						if(ptr1->position_x >= ptr->position_x - 6 &&
							ptr1->position_x <= ptr->position_x + 6) {

							if(ptr1->position_y > ptr->position_y) {
								bLineFree = FALSE;
								break;
							}
						}
						
						ptr1 = ptr1->next;
					} while(ptr1 != NULL);
					if(bLineFree) AlienFire(ptr);
				}

				ptr = ptr->next;

			} while(ptr != NULL);

			if(bMoveAliens) {
				int nAliens = CountAliens();
				if(nAliens < 2) {
					game_vars->alien_speed =  0;
				} else if(nAliens < 5) {
					game_vars->alien_speed =  1;
				} else if(nAliens < 10) {
					game_vars->alien_speed =  2;
				} else if(nAliens < 15) {
					game_vars->alien_speed =  3 + (1-game_vars->level<0?0:1-game_vars->level);
				} else if(nAliens < 20) {
					game_vars->alien_speed =  4 + (2-game_vars->level<0?0:2-game_vars->level);
				} else if(nAliens < 30) {
					game_vars->alien_speed =  8 + (4-game_vars->level<0?0:4-game_vars->level);
				} else {
					game_vars->alien_speed = 10 + (5-game_vars->level<0?0:5-game_vars->level);
				}


			}

			if(bMoveAliens || game_vars->alien_enter) {
				if(game_vars->alien_advance > 0) {
					game_vars->alien_advance--;
				} else {
					if(bChangeDirection) {
						game_vars->alien_direction = !game_vars->alien_direction; 
						game_vars->alien_advance = 5;
					} 
				}
			}			
		} else { // if(alien != NULL)
			
			if(game_vars->enter_level_timer <= 0) {
				if(CountAliens() == 0) {
					game_vars->level++;
					game_vars->enter_level_timer = BEGIN_LEVEL_TIME_WAIT;
				}
			}
		}
	} 


	// Check and move Alien Shoots
	
	if(game_vars->alien_shoot != NULL) {
		
		shoot_t* ptr = game_vars->alien_shoot;
		do {
			ptr->position_y += ptr->speed;
			if(ptr->type == ALIEN_SHOOT_BOMB) {
				ptr->frame = ((++(ptr->frame)) % 2);
			}

			ptr = ptr->next;
		} while(ptr != NULL);

		ptr = game_vars->alien_shoot;
		while(ptr->next != NULL) {
			BOOL bHit = CheckAlienShootCollision(ptr->next);
			if(ptr->next->position_y > ALIEN_SHOOT_Y_MAX || bHit) {				
				shoot_t *ptr1 = ptr->next;
				if(ptr1->type == ALIEN_SHOOT_BOMB) {
					FireExplosion(ptr1->position_x, ptr1->position_y, 0, -1, EXPLOSION_TYPE_FULL);
				} else {
					FireExplosion(ptr1->position_x, ptr1->position_y, 0, 0, EXPLOSION_TYPE_HALF);
				}
				ptr->next = ptr->next->next;
				free(ptr1);
			}
			ptr = ptr->next;
			if(ptr == NULL) break;
		}
	
		BOOL bHit = CheckAlienShootCollision(game_vars->alien_shoot);
		if(game_vars->alien_shoot->position_y > ALIEN_SHOOT_Y_MAX || bHit) {
			ptr = game_vars->alien_shoot;
			if(ptr->type == ALIEN_SHOOT_BOMB) {
				FireExplosion(ptr->position_x, ptr->position_y, 0, -1, EXPLOSION_TYPE_FULL);
			} else {
				FireExplosion(ptr->position_x, ptr->position_y, 0, 0, EXPLOSION_TYPE_HALF);
			}
			game_vars->alien_shoot = game_vars->alien_shoot->next;
			free(ptr);
		}
	}

	// "Move" barriers

	if(game_vars->barrier != NULL) {
		barrier_t* ptr = game_vars->barrier;
		do {

			if(ptr->position_y > BARRIER_Y_POSITION)
				ptr->position_y--;
			else if(ptr->position_y < BARRIER_Y_POSITION)
				ptr->position_y++;

			if(ptr->damage < 0) {
				ptr->damage++;
			}
			ptr = ptr->next;
		} while(ptr != NULL);
	}

	// Update the timeout of visualtext

	if(game_vars->visualtext != NULL) {
		if(game_vars->visualtext->timeout > 0) {
			game_vars->visualtext->timeout--;
		} else {
			free(game_vars->visualtext);
			game_vars->visualtext = NULL;
		}
	}

}

void PlaceVisualText(int x, int y, int width, int height, TCHAR *text, int timeout) {

	visualtext_t* ptr = (visualtext_t*) malloc(sizeof(visualtext_t));
	memset(ptr, 0, sizeof(visualtext_t));
	ptr->rect.left = x;
	ptr->rect.top  = y;
	ptr->rect.right = x + width;
	ptr->rect.bottom = y + height;

	strcpy(ptr->text, text);
	
	ptr->timeout = timeout;

	game_vars->visualtext = ptr;
}

void InitializeAliens() {

	int y_offset = (32 + ALIEN_Y_SPACE) * 5;

	int n;

	if(game_vars->alien != NULL) return;

	alien_t* last_ptr;

	for(n = 0; n < 40; n++) {

		alien_t* ptr = (alien_t*) malloc(sizeof(alien_t));
		memset(ptr, 0, sizeof(alien_t));

		ptr->position_x = (32 + ALIEN_X_SPACE) * (n % 8);
		ptr->position_y = (32 + ALIEN_Y_SPACE) * (n / 8) - y_offset;

		if(n / 8 == 0) {
			ptr->type = ALIEN_TYPE_2;
		} else if(n / 8 == 1 || n / 8 == 2) {
			ptr->type = ALIEN_TYPE_1;
		} else {
			ptr->type = ALIEN_TYPE_0;
		}

		if(n == 0) {
			game_vars->alien = ptr;
		} else {
			last_ptr->next = ptr;
		}

		last_ptr = ptr;
	}

	game_vars->alien_advance = (y_offset + 32) / 6;   // Alien step: 6px
	game_vars->alien_speed = 5;
	game_vars->alien_direction = TRUE;
	game_vars->alien_enter = TRUE;
}


void ExplodeBarrier(int x, int y) {

	PerformSound(SOUND_BIG_EXPLOSION);

	FireExplosion(x,      y - 3, -4, -2, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 4,  y,     -3, -1, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 8,  y + 3, -2,  0, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 12, y - 2, -1,  0, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 16, y + 2,  0,  0, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 20, y,      0,  0, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 24, y - 2,  1,  0, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 28, y + 2,  2, -1, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 32, y - 3,  3, -2, EXPLOSION_TYPE_FULL);

}

void ExplodeMShip(int x, int y) {

	FireExplosion(x,      y - 3, -4, -2, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 4,  y,     -3, -1, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 8,  y + 3, -2,  0, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 12, y - 2, -1,  0, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 16, y + 2,  0,  0, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 20, y,      0,  0, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 24, y - 2,  1,  0, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 28, y + 2,  2, -1, EXPLOSION_TYPE_FULL);
	FireExplosion(x + 32, y - 3,  3, -2, EXPLOSION_TYPE_FULL);

}

void ExplodeBarriers() {

	if(game_vars->barrier != NULL) {

		PerformSound(SOUND_BIG_EXPLOSION);

		barrier_t* ptr_next;
		barrier_t* ptr = game_vars->barrier;
		do {
			
			ExplodeBarrier(ptr->position_x, ptr->position_y);

			ptr_next = ptr->next;
			free(ptr);
			ptr = ptr_next;
		} while(ptr != NULL);

		game_vars->barrier = NULL;

	}
}

int CountAliens() {
	if(game_vars->alien == NULL) {
		return 0;
	} else {
		int n = 0;
		alien_t* ptr = game_vars->alien;
		do {
			
			n++;
			
			ptr = ptr->next;

		} while(ptr != NULL);

		return n;
	}
}

void AlienFire(alien_t* ptr) {
	
	shoot_t* shoot = (shoot_t*) malloc(sizeof(shoot_t));
	if(shoot == NULL) return;

	memset(shoot, 0, sizeof(shoot_t));

	shoot->position_x = ptr->position_x;
	shoot->position_y = ptr->position_y;
	
	if(rand() > RAND_MAX / 8){
		shoot->speed = 8 + ((rand()*8)/RAND_MAX);
		shoot->type = ALIEN_SHOOT_NORMAL;
	} else {
		shoot->speed = 3 + ((rand()*3)/RAND_MAX);
		shoot->type = ALIEN_SHOOT_BOMB;
	}

	shoot_t* ptr1;
	if(game_vars->alien_shoot == NULL) {
		game_vars->alien_shoot = shoot;
	} else {
		ptr1 = game_vars->alien_shoot;
		do {
			if(ptr1->next == NULL) {
				ptr1->next = shoot;
				break;
			}
			ptr1 = ptr1->next;
		} while(ptr1 != NULL);
	}

}

void FireExplosion(int x, int y, int dx, int dy, int type) {

	explosion_t* expl = (explosion_t*) malloc(sizeof(explosion_t));
	if(expl == NULL) return;

	memset(expl, 0, sizeof(explosion_t));

	expl->position_x = x;
	expl->position_y = y;
	expl->move_x = dx;
	expl->move_y = dy;
	expl->type = type;

	if(game_vars->explosion == NULL) {
		game_vars->explosion = expl;
	} else {
		explosion_t* ptr = game_vars->explosion;
		do {
			if(ptr->next == NULL) {
				ptr->next = expl;
				break;
			}
			ptr = ptr->next;
		} while(ptr != NULL);
	}

}

BOOL CheckTankShootCollision(shoot_t* shoot) {

	int shoot_x = shoot->position_x + 16;
	int shoot_y = shoot->position_y + 6;

	// Collision to aliens
	{
		alien_t* prev_ptr = NULL;
		alien_t* ptr = game_vars->alien;
		while(ptr != NULL) {
			BOOL bHit = TRUE;

			bHit = bHit && shoot_x > ptr->position_x + 4;
			bHit = bHit && shoot_x < ptr->position_x + 32 - 4;
			bHit = bHit && shoot_y > ptr->position_y + 6;
			bHit = bHit && shoot_y < ptr->position_y + 32 - 4;

			if(bHit) {
				switch(ptr->type) {
				case ALIEN_TYPE_0:
					game_vars->score += 10;
					break;
				case ALIEN_TYPE_1:
					game_vars->score += 20;
					break;
				default:
				case ALIEN_TYPE_2:
					game_vars->score += 30;
					break;
				}
			}

			if(bHit) {

				PerformSound(SOUND_EXPLOSION);
				
				if(prev_ptr == NULL) {
					alien_t* ptr1 = game_vars->alien;
					game_vars->alien = ptr->next;
					FireExplosion(ptr1->position_x, ptr1->position_y, 0, 0, EXPLOSION_TYPE_FULL);
					free(ptr1);
					return TRUE;
				} else {
					prev_ptr->next = ptr->next;
					FireExplosion(ptr->position_x, ptr->position_y, 0, 0, EXPLOSION_TYPE_FULL);
					free(ptr);
					return TRUE;
				}
			}

			prev_ptr = ptr;
			ptr = ptr->next;
		}
	}

	// Collision with mothership
	{
		if(game_vars->mship != NULL) {

			mship_t* ptr = game_vars->mship;

			BOOL bHit = TRUE;

			bHit = bHit && shoot_x > ptr->position_x + 4;
			bHit = bHit && shoot_x < ptr->position_x + 64 - 4;
			bHit = bHit && shoot_y > ptr->position_y + 6;
			bHit = bHit && shoot_y < ptr->position_y + 28 - 4;
			
			if(bHit) {

				PerformSound(SOUND_BIG_EXPLOSION);

				ExplodeMShip(ptr->position_x, ptr->position_y);

				int ns = ((rand()*4) / RAND_MAX) * 50 + 50;

				TCHAR ts[256];
				memset(ts, 0, 256 * sizeof(TCHAR));
				_stprintf(ts, "%d\0", ns);

				PlaceVisualText(ptr->position_x, ptr->position_y, 64, 32, ts, 30);

				game_vars->score += ns;

				free(game_vars->mship);
				game_vars->mship = NULL;
			}

		}

	}

	// Collision with alien shoots
	{
		shoot_t* prev_ptr = NULL;
		shoot_t* ptr = game_vars->alien_shoot;
		while(ptr != NULL) {
			BOOL bHit = TRUE;

			bHit = bHit && shoot_x > ptr->position_x + 4;
			bHit = bHit && shoot_x < ptr->position_x + 32 - 4;
			bHit = bHit && shoot_y > ptr->position_y + 6;
			bHit = bHit && shoot_y < ptr->position_y + 32 - 4;

			if(bHit && ptr->type == ALIEN_SHOOT_BOMB) {

				PerformSound(SOUND_EXPLOSION);

				if(prev_ptr == NULL) {
					shoot_t* ptr1 = game_vars->alien_shoot;
					game_vars->alien_shoot = ptr->next;
					FireExplosion(ptr1->position_x, ptr1->position_y, 0, 0, EXPLOSION_TYPE_FULL);
					free(ptr1);
					return TRUE;
				} else {
					prev_ptr->next = ptr->next;
					FireExplosion(ptr->position_x, ptr->position_y, 0, 0, EXPLOSION_TYPE_FULL);
					free(ptr);
					return TRUE;
				}
			}

			prev_ptr = ptr;
			ptr = ptr->next;
		}
	}

	// Collision with barriers

	{
		barrier_t* ptr;
		barrier_t* prev_ptr = NULL;

		if(game_vars->barrier != NULL) {
			ptr = game_vars->barrier;
			do {
				BOOL bHit = TRUE;

				bHit = bHit && shoot_x > ptr->position_x + 2;
				bHit = bHit && shoot_x < ptr->position_x + BARRIER_WIDTH - 2;
				bHit = bHit && shoot_y > ptr->position_y + 6;
				bHit = bHit && shoot_y < ptr->position_y + BARRIER_HEIGHT - 14;

				if(bHit) {

					PerformSound(SOUND_SMALL_EXPLOSION);

					ptr->damage+=5;
					ptr->position_y-=2;
					if(ptr->damage > 100) {
						if(prev_ptr == NULL) {
							game_vars->barrier = ptr->next;
							ExplodeBarrier(ptr->position_x,      ptr->position_y);
							free(ptr);
						} else {
							prev_ptr->next = ptr->next;
							ExplodeBarrier(ptr->position_x,      ptr->position_y);
							free(ptr);
						}
					}
					return TRUE;
				}


				prev_ptr = ptr;
				ptr = ptr->next;

			} while(ptr != NULL);
		}
	}

	return FALSE;
}

BOOL CheckAlienShootCollision(shoot_t* shoot) {

	int shoot_x = shoot->position_x + 16;
	int shoot_y = shoot->position_y + 26;
	int shoot1_y = shoot->position_y + 18;

	// Check collision to barriers
	{
		barrier_t* prev_ptr = NULL;
		barrier_t* ptr;
		if(game_vars->barrier != NULL) {
			ptr = game_vars->barrier;
			do {
				BOOL bHit = TRUE;

				bHit = bHit && shoot_x > ptr->position_x + 2;
				bHit = bHit && shoot_x < ptr->position_x + BARRIER_WIDTH - 2;
				bHit = bHit && shoot_y > ptr->position_y + 6;
				bHit = bHit && shoot_y < ptr->position_y + BARRIER_HEIGHT - 14;

				BOOL bHit1 = TRUE;

				bHit1 = bHit1 && shoot_x > ptr->position_x + 2;
				bHit1 = bHit1 && shoot_x < ptr->position_x + BARRIER_WIDTH - 2;
				bHit1 = bHit1 && shoot1_y > ptr->position_y + 6;
				bHit1 = bHit1 && shoot1_y < ptr->position_y + BARRIER_HEIGHT - 14;

				if(bHit || bHit1) {
					if(shoot->type == ALIEN_SHOOT_NORMAL) {
						ptr->damage ++;
						ptr->position_y +=2;
					} else {
						ptr->damage += 5;
						ptr->position_y += 5;
					}

					if(ptr->damage > 100) {
						if(prev_ptr == NULL) {
							game_vars->barrier = ptr->next;
							ExplodeBarrier(ptr->position_x,      ptr->position_y);
							free(ptr);
						} else {
							prev_ptr->next = ptr->next;
							ExplodeBarrier(ptr->position_x,      ptr->position_y);
							free(ptr);
						}
					}

					return TRUE;
				}

				prev_ptr = ptr;
				ptr = ptr->next;
			} while(ptr != NULL);
		}
	}

	// Check collision to tank
	{
		if(game_vars->tank != NULL) {
		
			tank_t* ptr = game_vars->tank;

			BOOL bHit = TRUE;

			bHit = bHit && shoot_x > ptr->position_x + 2;
			bHit = bHit && shoot_x < ptr->position_x + 30;
			bHit = bHit && shoot_y > ptr->position_y + 14;
			bHit = bHit && shoot_y < ptr->position_y + 30;

			if(bHit) {

				PerformSound(SOUND_BIG_EXPLOSION);

				FireExplosion(ptr->position_x,      ptr->position_y, -4, -4, EXPLOSION_TYPE_FULL);
				FireExplosion(ptr->position_x + 4,  ptr->position_y, -2, -2, EXPLOSION_TYPE_FULL);
				FireExplosion(ptr->position_x,      ptr->position_y,  2, -2, EXPLOSION_TYPE_FULL);
				FireExplosion(ptr->position_x -4,   ptr->position_y,  4, -4, EXPLOSION_TYPE_FULL);

				game_vars->tank = NULL;
				free(ptr);
				
				game_vars->lives--;

				return TRUE;
			}
		}		
	}

	return FALSE;
}

void InitializeBarriers() {

	int x_step   = ((SCREEN_WIDTH - 32 * 2) - BARRIER_WIDTH * 4) / 4;
	int x_offset = x_step / 2 + 32;
	int x_inc    = x_step + BARRIER_WIDTH;

	barrier_t* prev_ptr = NULL;

	int n;
	for(n = 0; n < 4; n++) {
		barrier_t* ptr = (barrier_t*) malloc(sizeof(barrier_t));
		if(ptr == NULL) continue;
		memset(ptr, 0, sizeof(barrier_t));

		ptr->position_x = x_offset + x_inc * n;
		ptr->position_y = BARRIER_Y_POSITION;
		ptr->damage = -4;
		
		if(prev_ptr == NULL) {
			game_vars->barrier = ptr;
			prev_ptr = ptr;
		} else {
			prev_ptr->next = ptr;
			prev_ptr = ptr;
		}
	}

}