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

// Implementation file 
#include "stdafx.h"
#include "resource.h"
#include <stdio.h>

extern int record;									// Record is defined in invaders.cpp

// The blinker timer
int nBlinker = 0;

// The backbuffers
HBITMAP g_backbuffer[2];

// The operations backbuffers;
HDC g_hmemoryDC[2];

// The selected backbuffer
int nBackbuffer;

void InitializeBackbuffers(HDC hdc) {

	g_hmemoryDC[0] = CreateCompatibleDC(hdc);

	g_backbuffer[0] = CreateCompatibleBitmap(hdc, BUFFER_HSIZE, BUFFER_VSIZE);
	g_backbuffer[1] = CreateCompatibleBitmap(hdc, BUFFER_HSIZE, BUFFER_VSIZE);

	ClearBackbuffer(g_backbuffer[0], FALSE);
	ClearBackbuffer(g_backbuffer[1], FALSE);

	g_hmemoryDC[1] = CreateCompatibleDC(hdc);
}

void ClearBackbuffer(HBITMAP hbackbuffer, BOOL bImage) {

	HGDIOBJ lastobjd = SelectObject(g_hmemoryDC[0], hbackbuffer);

	if(bImage) {
		HGDIOBJ lastobjs = SelectObject(g_hmemoryDC[1], GetBitmap(BITMAP_BACKG1));
		BitBlt(g_hmemoryDC[0], 0, -16, BUFFER_HSIZE, BUFFER_VSIZE, g_hmemoryDC[1], 0, 0, SRCCOPY);	
		SelectObject(g_hmemoryDC[0], lastobjs);
	} else {

		HBRUSH brush = (HBRUSH) GetStockObject(WHITE_BRUSH);

		RECT rect;
		rect.top = 0;
		rect.left = 0;
		rect.bottom = BUFFER_VSIZE;
		rect.right = BUFFER_HSIZE;

		FillRect(g_hmemoryDC[0], &rect, brush);
	}

	SelectObject(g_hmemoryDC[0], lastobjd);
	
}

HBITMAP GetBackbuffer() {

	return g_backbuffer[nBackbuffer];
}

HBITMAP GetFrontbuffer() {

	return g_backbuffer[nBackbuffer % 2];
}

void FlipBackbuffers() {
	
	if(++nBackbuffer > 1) nBackbuffer = 0;

}

void Render(game_vars_t* GameVars) {

	ClearBackbuffer(GetBackbuffer(), TRUE);

	HDC hddc = g_hmemoryDC[0];
	HDC hsdc = g_hmemoryDC[1];

	HGDIOBJ lastdobj = SelectObject(hddc, GetBackbuffer());
	HGDIOBJ lastsobj = SelectObject(hsdc, GetBitmap(BITMAP_TANK));

	// Draw Tank Shoots

	if(GameVars->tank_shoot != NULL) {
		SelectObject(hsdc, GetBitmap(BITMAP_TANK_SHOOT));
		shoot_t* ptr = GameVars->tank_shoot;
		do {
			TransparentBlt(hddc, ptr->position_x, ptr->position_y, 
										32, 32, hsdc, 0, 0, 32, 32, RGB(255, 255, 255));
			ptr = ptr->next;
		} while(ptr != NULL);
	}
	
	// Draw Tank
	if(GameVars->tank != NULL) {
		SelectObject(hsdc, GetBitmap(BITMAP_TANK));
		TransparentBlt(hddc, GameVars->tank->position_x, GameVars->tank->position_y, 
										32, 32, hsdc, 0, 0, 32, 32, RGB(255, 255, 255));
	}

	if(GameVars->alien != NULL) {
		
		alien_t* ptr = GameVars->alien;

		do {
			switch(ptr->type) {

			case ALIEN_TYPE_0:
			default:
				if(ptr->frame) {
					SelectObject(hsdc, GetBitmap(BITMAP_ALIEN1_1));	
				} else {
					SelectObject(hsdc, GetBitmap(BITMAP_ALIEN1_2));	
				}
				break;
			case ALIEN_TYPE_1:
				if(ptr->frame) {
					SelectObject(hsdc, GetBitmap(BITMAP_ALIEN2_1));	
				} else {
					SelectObject(hsdc, GetBitmap(BITMAP_ALIEN2_2));	
				}
				break;
			case ALIEN_TYPE_2:
				if(ptr->frame) {
					SelectObject(hsdc, GetBitmap(BITMAP_ALIEN3_1));	
				} else {
					SelectObject(hsdc, GetBitmap(BITMAP_ALIEN3_2));	
				}
				break;

			}

			TransparentBlt(hddc, ptr->position_x, ptr->position_y, 
										32, 32, hsdc, 0, 0, 32, 32, RGB(255, 255, 255));
			
			ptr = ptr->next;

		} while(ptr != NULL);
	}

	// Draw Mothership
	if(GameVars->mship != NULL) {
		mship_t* ptr = GameVars->mship;
		SelectObject(hsdc, GetBitmap(BITMAP_MSHIP));
		TransparentBlt(hddc, ptr->position_x, ptr->position_y, 
									64, 32, hsdc, 0, 0, 64, 32, RGB(255, 255, 255));		
	}

	// Draw Alien Shoots
	if(GameVars->alien_shoot != NULL) {
		
		shoot_t* ptr = GameVars->alien_shoot;

		do {
		
			if(ptr->type == ALIEN_SHOOT_BOMB) {
				if(ptr->frame) {
					SelectObject(hsdc, GetBitmap(BITMAP_ALIEN_SHOOT2_1));	
				} else {
					SelectObject(hsdc, GetBitmap(BITMAP_ALIEN_SHOOT2_2));	
				}
			} else {
				SelectObject(hsdc, GetBitmap(BITMAP_ALIEN_SHOOT1));	
			}

			TransparentBlt(hddc, ptr->position_x, ptr->position_y, 
										32, 32, hsdc, 0, 0, 32, 32, RGB(255, 255, 255));			
			ptr = ptr->next;

		} while(ptr != NULL);
	}

	// Draw Explosions
	if(GameVars->explosion != NULL) {
		
		explosion_t* ptr = GameVars->explosion;

		do {

			switch(ptr->frame) {
			case 0:
				SelectObject(hsdc, GetBitmap(BITMAP_EXPL1_1));
				break;
			case 1:
				SelectObject(hsdc, GetBitmap(BITMAP_EXPL1_2));
				break;
			default:
				SelectObject(hsdc, GetBitmap(BITMAP_EXPL1_3));
			}

			TransparentBlt(hddc, ptr->position_x, ptr->position_y, 
										32, 32, hsdc, 0, 0, 32, 32, RGB(255, 255, 255));			
			ptr = ptr->next;

		} while(ptr != NULL);
	}

	// Draw Barriers
	if(GameVars->barrier != NULL) {
		
		barrier_t* ptr = GameVars->barrier;

		do {

			if(ptr->damage < -2) {
				SelectObject(hsdc, GetBitmap(BITMAP_BARREF1));
			} else if(ptr->damage < -1) {
				SelectObject(hsdc, GetBitmap(BITMAP_BARREF2));
			} else if(ptr->damage <  0) {
				SelectObject(hsdc, GetBitmap(BITMAP_BARREF3));
			} else if(ptr->damage < 50) {
				SelectObject(hsdc, GetBitmap(BITMAP_DEFENCE1));
			} else if(ptr->damage < 75) {
				SelectObject(hsdc, GetBitmap(BITMAP_DEFENCE2));
			} else {
				SelectObject(hsdc, GetBitmap(BITMAP_DEFENCE3));
			}

			TransparentBlt(hddc, ptr->position_x, ptr->position_y, 
										BARRIER_WIDTH, BARRIER_HEIGHT, hsdc, 0, 0, 
										BARRIER_WIDTH, BARRIER_HEIGHT, RGB(255, 255, 255));			
			ptr = ptr->next;

		} while(ptr != NULL);
	}


	if(++nBlinker>30) nBlinker = 0;

	if(GameVars->enter_level_timer > 0 && 
	   nBlinker%15 < 10) {

		RECT rt;
		rt.left   = 0;
		rt.top    = 0;
		rt.right  = SCREEN_WIDTH;
		rt.bottom = SCREEN_HEIGHT;

		TCHAR szMessage[256];
		memset(szMessage, 0, 256 * sizeof(TCHAR));
		int level = (GameVars->level) + 1;
		_stprintf(szMessage, _T("LEVEL %d\0"), level);

		int prevbk = SetBkMode(hddc, TRANSPARENT);

		COLORREF oldtextcolor = SetTextColor(g_hmemoryDC[0], RGB(255, 0, 0));
		DrawText(hddc, szMessage, strlen(szMessage), &rt, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		SetTextColor(g_hmemoryDC[0], oldtextcolor);
	
		SetBkMode(hddc, prevbk);
	}


	if(GameVars->tank == NULL && 
	   nBlinker%15 < 10) {

		RECT rt;
		rt.left   = 0;
		rt.top    = 0;
		rt.right  = SCREEN_WIDTH;
		rt.bottom = SCREEN_HEIGHT;

		TCHAR szMessage[256];
		memset(szMessage, 0, 256 * sizeof(TCHAR));

		if(GameVars->lives > 0) 
			_stprintf(szMessage, _T("PRESS FIRE TO CONTINUE"));
		else
			_stprintf(szMessage, _T("GAME OVER"));

		int prevbk = SetBkMode(hddc, TRANSPARENT);

		COLORREF oldtextcolor = SetTextColor(g_hmemoryDC[0], RGB(255, 0, 0));
		DrawText(hddc, szMessage, strlen(szMessage), &rt, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		SetTextColor(g_hmemoryDC[0], oldtextcolor);
	
		SetBkMode(hddc, prevbk);
	}

	if(GameVars->visualtext != NULL) {
		if(GameVars->visualtext->timeout > 0) {

			RECT* rt = &GameVars->visualtext->rect;

			TCHAR szMessage[256];
			memset(szMessage, 0, 256 * sizeof(TCHAR));

			_stprintf(szMessage, GameVars->visualtext->text);

			int prevbk = SetBkMode(hddc, TRANSPARENT);

			COLORREF oldtextcolor = SetTextColor(g_hmemoryDC[0], RGB(255, 0, 0));
			DrawText(hddc, szMessage, strlen(szMessage), rt, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			SetTextColor(g_hmemoryDC[0], oldtextcolor);
		
			SetBkMode(hddc, prevbk);
		}
	}


	{
		RECT rt;
		rt.left   = 0;
		rt.top    = 0;
		rt.right  = SCREEN_WIDTH;
		rt.bottom = SCREEN_HEIGHT;

		TCHAR szMessage[256];

		int prevbk = SetBkMode(hddc, TRANSPARENT);

		COLORREF oldtextcolor = SetTextColor(g_hmemoryDC[0], RGB(255, 0, 0));

		memset(szMessage, 0, 256 * sizeof(TCHAR));
		int score = GameVars->score;
		_stprintf(szMessage, _T("SCORE: %5d\0"), score);

		DrawText(hddc, szMessage, strlen(szMessage), &rt, DT_LEFT|DT_TOP|DT_SINGLELINE);

		if(score > record) record = score;

		memset(szMessage, 0, 256 * sizeof(TCHAR));
		_stprintf(szMessage, _T("HI-SCORE: %5d\0"), record);
		
		DrawText(hddc, szMessage, strlen(szMessage), &rt, DT_CENTER|DT_TOP|DT_SINGLELINE);

		memset(szMessage, 0, 256 * sizeof(TCHAR));
		_stprintf(szMessage, _T("LIVES:                         \0"));
		
		DrawText(hddc, szMessage, strlen(szMessage), &rt, DT_RIGHT|DT_TOP|DT_SINGLELINE);
		
		SetTextColor(g_hmemoryDC[0], oldtextcolor);

		SetBkMode(hddc, prevbk);

		SelectObject(hsdc, GetBitmap(BITMAP_LIVE));

		if(GameVars->lives > 1) {
			int x = SCREEN_WIDTH - 16 * 6;
			int n;
			for(n = 0; n < GameVars->lives - 1; n++) {
				TransparentBlt(hddc, x + 16 * n, 1, 
											16, 16, hsdc, 0, 0, 
											16, 16, RGB(255, 255, 255));							
			}
		}
	}

	SelectObject(hddc, lastdobj);
	SelectObject(hsdc, lastsobj);

}

void RenderToDC(HDC hdc) {

	HDC hsdc;
	hsdc = g_hmemoryDC[0];
	HGDIOBJ lastobj;
	lastobj = SelectObject(hsdc, GetFrontbuffer());
	BitBlt(hdc, 0, 0,  BUFFER_HSIZE, BUFFER_VSIZE, hsdc, 0, 0, SRCCOPY);
	SelectObject(hsdc, lastobj);

}
