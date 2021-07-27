#include <gb/gb.h>
#include <stdio.h>
#include "main.h"
#include "windowmap.c"
#include "sprites.c"
#include "entity.c"
#include "helpers.c"
#include "bgtiles.c"
#include "bgmap.c"
#include <gb/font.h>

// Bits 7 and 6 are for lives (3-2-1-0)
// Bit 5 is for pause
// Bits 4 to 0 are for score (0-25)
// 1100 0000 (0xC0) -> LIVES = 3, UNPAUSED, SCORE = 0
// 0011 1001 -> LIVES = 0, PAUSED, SCORE = 25 
UINT8 GameLoopState = 0xC0;

void main()
{
    // Setup font tiles for window layer
    font_t min_font;
    font_init();
    min_font = font_load(font_min); // 36 tiles
    font_set(min_font);

    // SETUP WINDOW LAYER
    set_win_tiles(0, 0, 20, 2, windowmap);
    move_win(7, 128);

    // SETUP SPRITES AND BACKGROUND MAP
    set_sprite_data(0, 3, sprites);
    set_bkg_data(37, 9, bgtiles);
    set_bkg_tiles(0, 0, 32, 32, bgmap);

    SHOW_SPRITES;
    SHOW_WIN;
    SHOW_BKG;
    DISPLAY_ON;

    // SETUP PLAYER
    struct Entity player;
    setupPlayer(&player);

    // Setting up 4 other entities and their sprites
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