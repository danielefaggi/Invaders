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

#define SOUND_LASER				0
#define SOUND_EXPLOSION			1
#define SOUND_BIG_EXPLOSION		2
#define SOUND_SMALL_EXPLOSION	3

void LoadSounds(HINSTANCE hInst);

void PerformSound(int idSound);

void SoundOn();
void SoundOff();
