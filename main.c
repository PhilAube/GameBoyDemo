#include <gb/gb.h>
#include <stdio.h>
#include <gb/font.h>
#include "main.h"
#include "entity.c"
#include "sound.c"
#include "bgtiles.c"
#include "bgmap.c"
#include "windowmap.c"
#include "sprites.c"
#include "setup.c"
#include "helpers.c"

// Bits 7 and 6 are for lives (3-2-1-0)
// Bit 5 is for pause
// Bits 4 to 0 are for score (0-25)
// 1100 0000 (0xC0) -> LIVES = 3, UNPAUSED, SCORE = 0
// 0011 1001 -> LIVES = 0, PAUSED, SCORE = 25 
UINT8 GameLoopState = 0xC0;

void main()
{
    // SETUP
    setupHardware();

    struct Entity player;
    setupPlayer(&player);

    // struct Entity entities[SPRITE_QTY];
    // setupEntities(entities);

    // GAME LOOP
    while (1)
    {
        // Get input
        movePlayer(&player);

        if (isPaused() == 0)
        {
            checkWallCollisions(&player);

            // Move player sprite on screen
            if (scrollMapOrNot(&player) == 1) scroll_bkg(player.xVel, player.yVel);
            else scroll_sprite(player.id, player.xVel, player.yVel);

            // Move player coordinates
            player.x += player.xVel;
            player.y += player.yVel;

            // animateEntities(entities);

            delay(20);
        }
    }
}