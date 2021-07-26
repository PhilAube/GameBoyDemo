#include <gb/gb.h>
#include <stdio.h>
#include "main.h"
#include "sprites.c"
#include "entity.c"
#include "helpers.c"
#include "bgtiles.c"
#include "bgmap.c"

void main()
{
    // printf("GAME BOY DEMO 0.03\n");

    // SETUP SPRITES AND BACKGROUND MAP
    set_sprite_data(0, 3, sprites);
    set_bkg_data(0, 4, bgtiles);
    set_bkg_tiles(0, 0, 32, 32, bgmap);

    SHOW_SPRITES;
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