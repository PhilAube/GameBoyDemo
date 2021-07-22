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
int const MIDDLE_X = 76; // (REAL_WIDTH - SPRITESIZE) / 2;
int const MIDDLE_Y = 72; // (REAL_HEIGHT - SPRITESIZE) / 2;

void main()
{
    // Setting up player
    struct Entity player;
    player.id = 0;
    player.x = REAL_LEFT;
    player.y = REAL_TOP;

    // SETUP
    set_sprite_data(0, 2, sprites);

    // SETUP PLAYER
    set_sprite_tile(player.id, 0);
    move_sprite(player.id, REAL_LEFT, REAL_TOP);

    SHOW_SPRITES;

    // GAME
    printf(" Greetings, planet. \n");

    while (1)
    {
        animateSprite(&player);

        scroll_sprite(player.id, player.xVel, player.yVel);

        player.x += player.xVel;
        player.y += player.yVel;

        delay(100);
    }
}