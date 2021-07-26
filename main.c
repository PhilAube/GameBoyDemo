#include <gb/gb.h>
#include <stdio.h>
#include "main.h"
#include "sprites.c"
#include "entity.c"
#include "helpers.c"
#include "bgtiles.c"
#include "bgmap.c"
#include <gb/font.h>
#include "windowmap.c"

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
    set_bkg_data(37, 5, bgtiles);
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