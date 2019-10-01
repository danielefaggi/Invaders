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
#include <mmsystem.h>
#include <assert.h>

// Sounds Management

LPVOID g_lpsounds[5];

BOOL bSoundOn = TRUE;

void LoadSounds(HINSTANCE hInst) {

	{
		HRSRC hrsrc = FindResource(hInst, MAKEINTRESOURCE(IDR_LASER), "WAVE");
		assert(hrsrc != NULL);
		HGLOBAL hglobal = LoadResource(hInst, hrsrc);
		assert(hglobal != NULL);
		g_lpsounds[SOUND_LASER] = LockResource(hglobal);
	}


	{
		HRSRC hrsrc = FindResource(hInst, MAKEINTRESOURCE(IDR_EXPLOSION), "WAVE");
		assert(hrsrc != NULL);
		HGLOBAL hglobal = LoadResource(hInst, hrsrc);
		assert(hglobal != NULL);
		g_lpsounds[SOUND_EXPLOSION] = LockResource(hglobal);
	}


	{
		HRSRC hrsrc = FindResource(hInst, MAKEINTRESOURCE(IDR_BIGEXPLOSION), "WAVE");
		assert(hrsrc != NULL);
		HGLOBAL hglobal = LoadResource(hInst, hrsrc);
		assert(hglobal != NULL);
		g_lpsounds[SOUND_BIG_EXPLOSION] = LockResource(hglobal);
	}

	{
		HRSRC hrsrc = FindResource(hInst, MAKEINTRESOURCE(IDR_SMALLEXPLOSION), "WAVE");
		assert(hrsrc != NULL);
		HGLOBAL hglobal = LoadResource(hInst, hrsrc);
		assert(hglobal != NULL);
		g_lpsounds[SOUND_SMALL_EXPLOSION] = LockResource(hglobal);
	}

}

void PerformSound(int idSound) {

	if(bSoundOn)
		PlaySound((LPCTSTR) g_lpsounds[idSound], NULL, SND_MEMORY|SND_ASYNC);

}

void SoundOn() {
	
	bSoundOn = TRUE;

}

void SoundOff() {

	bSoundOn = FALSE;


}
