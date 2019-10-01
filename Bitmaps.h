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

// Define and Declares for Bitmaps.cpp

#define BITMAP_TANK				 0
#define BITMAP_DEFENCE1			 1
#define BITMAP_DEFENCE2			 2
#define BITMAP_DEFENCE3			 3
#define BITMAP_TANK_SHOOT		 4
#define BITMAP_ALIEN1_1			 5
#define BITMAP_ALIEN1_2			 6
#define BITMAP_ALIEN_SHOOT1      7
#define BITMAP_ALIEN_SHOOT2_1    8
#define BITMAP_ALIEN_SHOOT2_2    9
#define BITMAP_EXPL1_1			10
#define BITMAP_EXPL1_2			11
#define BITMAP_EXPL1_3			12
#define BITMAP_ALIEN2_1			13
#define BITMAP_ALIEN2_2			14
#define BITMAP_ALIEN3_1			15
#define BITMAP_ALIEN3_2			16
#define BITMAP_BACKG1			17
#define BITMAP_MSHIP			18
#define BITMAP_LIVE			    19
#define BITMAP_BARREF1		    20
#define BITMAP_BARREF2		    21
#define BITMAP_BARREF3		    22

void LoadBitmaps(HINSTANCE hInstance);

HBITMAP GetBitmap(int nBitmapID);
