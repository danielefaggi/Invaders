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

// Bitmap array
HBITMAP* g_hbitmaps;

// Load Bitmaps
void LoadBitmaps(HINSTANCE hInstance) {

	g_hbitmaps = (HBITMAP*) malloc(sizeof(HBITMAP)*23);

	//g_hbitmaps[BITMAP_TANK] = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_TANK));

	g_hbitmaps[BITMAP_TANK]           = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_TANK), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_DEFENCE1]       = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_DEFENCE1), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_DEFENCE2]       = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_DEFENCE2), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_DEFENCE3]       = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_DEFENCE3), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_TANK_SHOOT]     = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_TANK_SHOOT), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_ALIEN1_1]       = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN1_1), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_ALIEN1_2]       = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN1_2), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_ALIEN2_1]       = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN2_1), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_ALIEN2_2]       = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN2_2), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_ALIEN3_1]       = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN3_1), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_ALIEN3_2]       = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN3_2), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_MSHIP]          = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_MSHIP), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_ALIEN_SHOOT1]   = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_SHOOT1), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_ALIEN_SHOOT2_1] = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_SHOOT2_1), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_ALIEN_SHOOT2_2] = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_SHOOT2_2), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_EXPL1_1]		  = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_EXPL1_1), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_EXPL1_2]		  = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_EXPL1_2), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_EXPL1_3]		  = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_EXPL1_3), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_BACKG1]		  = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_BACKG1), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_LIVE]		      = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_LIVE), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_BARREF1]	      = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_DEFREF1), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_BARREF2]	      = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_DEFREF2), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	g_hbitmaps[BITMAP_BARREF3]	      = (HBITMAP) LoadImage(hInstance, MAKEINTRESOURCE(IDB_DEFREF3), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);

	DWORD dw = GetLastError();
}


HBITMAP GetBitmap(int nBitmapID) {

	return g_hbitmaps[nBitmapID];

}