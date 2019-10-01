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

// Defines and declaration for Renderer.cpp

#define BUFFER_HSIZE 640
#define BUFFER_VSIZE 480

void InitializeBackbuffers(HDC hdc);

void ClearBackbuffer(HBITMAP hbackbuffer, BOOL bImage);

HBITMAP GetBackbuffer();

HBITMAP GetFrontbuffer();

void FlipBackbuffers();

struct game_vars_s;

void Render(struct game_vars_s* GameVars);

void RenderToDC(HDC hdc);
