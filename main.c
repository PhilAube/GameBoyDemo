#include <gb/gb.h>
#include <stdio.h>
#include "main.h"
#include "sprites.c"
#include "entity.c"
#include "helpers.c"

// CONSTANTS
int const REAL_LEFT = 8; // First visible X pixel
int const REAL_TOP = 16; // First visible Y pixel
int const REAL_WIDTH = 160;
int const REAL_HEIGHT = 152;
int const SPRITESIZE = 8;
// So that a sprite can be placed mid-screen.
int const MIDDLE_X = 84; // (REAL_WIDTH - SPRITESIZE / 2) + SPRITESIZE;
int const MIDDLE_Y = 80; // (REAL_HEIGHT - SPRITESIZE / 2) + SPRITESIZE;

void main()
{
    printf("GAME BOY DEMO 0.02\n");
    // FOR DEBUGGING
    printf("PRESS A TO SEE X/Y\n");
    printf("PRESS B FOR ERASER\n");

    // GENERAL SETUP
    set_sprite_data(0, 3, sprites);
    SHOW_SPRITES;

    // Setup player
    struct Entity player;
    player.id = 0;
    player.x = MIDDLE_X;
    player.y = MIDDLE_Y;

    // Setup player sprite
    set_sprite_tile(player.id, 0);
    move_sprite(player.id, MIDDLE_X, MIDDLE_Y);

    // Setting up 4 other entities
    struct Entity entities[4];

    // And their sprites
    for (int i = 0; i < 4; i++)
    {
        entities[i].id = i + 1;
        set_sprite_tile(i + 1, 2);
    }

    move_sprite(1, REAL_LEFT, REAL_TOP);
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
    entities[3].y = REAL_HEIGHT;

    // GAME LOOP
    while (1)
    {
        // Get input
        movePlayer(&player);
        checkWallCollisions(&player);

        // Move player sprite on screen
        scroll_sprite(player.id, player.xVel, player.yVel);

        // Move player coordinates
        player.x += player.xVel;
        player.y += player.yVel;

        // Move other entity sprites / coordinates
        for (int i = 0; i < 4; i++)
        {
            animateSprite(&entities[i]);

            scroll_sprite(entities[i].id, entities[i].xVel, entities[i].yVel);

            entities[i].x += entities[i].xVel;
            entities[i].y += entities[i].yVel;
        }

        delay(50);
    }
}