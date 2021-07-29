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

// Bit 7 and 6 are for pause menu selected choice
// Bit 5 is START HOLD bit, meaning if true, START is being held.
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

    // SETUP PLAYER
    struct Entity player;
    setupPlayer(&player);

    // SETUP COINS
    // struct Entity coins[ENTITY_QTY];
    // setupCoins(coins);

    // GAME LOOP
    while (1)
    {
        // Get input
        movePlayer();

        if (!isPaused())
        {
            if (clock > 0) scrollHUDDown(); // Unpause window layer scrolldown
            else
            {
                checkWallCollisions(&player);
                // checkPlayerCoinCollisions(&player, coins);                

                if (scrollMapOrNot(&player)) // Scroll background and entities, not player
                {
                    scroll_bkg(xVel, yVel);
                    // scrollCoins(coins);
                } 
                else scroll_sprite(0, xVel, yVel); // Scroll player, not BG and entities

                // Move player coordinates
                player.x += xVel;
                player.y += yVel;

                delay(10);
                // performantDelay(1);
            }
        }
        else // if isPaused
        {
            if (clock < 144) scrollHUDUp(); // Pause window layer scrollup
        }
    }
}