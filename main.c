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

    // SETUP: SPRITES
    set_sprite_data(0, 3, sprites);
    SHOW_SPRITES;

    // SETUP: BACKGROUND
    set_bkg_data(0, 3, bgtiles);
    set_bkg_tiles(0, 0, 32, 32, bgmap);
    SHOW_BKG;
    DISPLAY_ON;

    // Setup player
    struct Entity player;
    player.id = 0;
    player.x = MIDDLE_X;
    player.y = MIDDLE_Y;
    player.xVel = 0;
    player.yVel = 0;

    // Setup player sprite
    set_sprite_tile(player.id, 0);
    move_sprite(player.id, MIDDLE_X, MIDDLE_Y);

    // Setting up 4 other entities
    // struct Entity entities[SPRITE_QTY];

    // And their sprites
    /*for (int i = 0; i < SPRITE_QTY; i++)
    {
        entities[i].id = i + 1;
        entities[i].xVel = 0;
        entities[i].yVel = 0;
        set_sprite_tile(i + 1, 2);
    }*/

    /*move_sprite(1, REAL_LEFT, REAL_TOP);
    entities[0].x = REAL_LEFT;
    entities[0].y = REAL_TOP;
    move_sprite(2, REAL_WIDTH, REAL_TOP);
    entities[1].x = REAL_WIDTH;
    entities[1].y = REAL_TOP;
    move_sprite(3, REAL_LEFT, REAL_HEIGHT);
    entities[2].x = REAL_LEFT;
    entities[2].y = REAL_HEIGHT;
    move_sprite(4, REAL_WIDTH, REAL_HEIGHT);
    entities[3].x = REAL_WIDTH;
    entities[3].y = REAL_HEIGHT;*/

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

        // Move other entity sprites / coordinates
        /*for (int i = 0; i < SPRITE_QTY; i++)
        {
            animateSprite(&entities[i]);

            scroll_sprite(entities[i].id, entities[i].xVel, entities[i].yVel);

            entities[i].x += entities[i].xVel;
            entities[i].y += entities[i].yVel;
        }*/

        delay(25);
    }
}