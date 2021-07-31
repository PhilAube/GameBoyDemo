#include <gb/gb.h>
#include <stdio.h>
#include <gb/font.h>
#include "main.h"
#include "entity.c"
#include "bgtiles.c"
#include "bgmap.c"
#include "windowmap.c"
#include "sound.c"
#include "titlescreenmap.c"
#include "sprites.c"
#include "setup.c"
#include "titlescreen.c"
#include "pause.c"
#include "helpers.c"

// Bits 7 and 6 are for lives (3-2-1-0)
// Bit 5 is for pause
// Bits 4 to 0 are for score (0-25)
// 1100 0000 (0xC0) -> LIVES = 3, UNPAUSED, SCORE = 0
// 0011 1001 -> LIVES = 0, PAUSED, SCORE = 25 
UINT8 GameLoopState = 0xC0;

// Bit 7-6 are for menu selected choice
// Rest are game context (title screen, game loop, etc.)
UINT8 GameState = 0x00;

UINT8 clock = 0; // For timing events.
int xVel = 0; // Player x velocity
int yVel = 0; // Player y velocity
int xVels[25] = {0}; // For other moving entities
int yVels[25] = {0}; // For other moving entities

void main()
{
    // SETUP GRAPHICS AND SOUND
    setupHardware();

    while (1)
    {
        // Bitwise AND to get the two last bits
        int context = GameState & 0x03;

        switch (context)
        {
            case 0:
                titleScreen();
                break;
            case 1:
                initGame();
            case 2:
                gameLoop();
            default:
                break;
        }
    }
}