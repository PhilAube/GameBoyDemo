// Animates a sprite clockwise around the screen.
void animateSprite(struct Entity * entity, int index)
{
    if (entity->x == REAL_LEFT)
    {
        if (entity->y == REAL_TOP) // Top left
        {
            yVels[index] = 0;
            xVels[index] = 1;
        }
        else if (entity->y == REAL_HEIGHT) // Bottom left
        {
            yVels[index] = -1;
            xVels[index] = 0;
        }
    }
    else if (entity->x == REAL_WIDTH)
    {
        if (entity->y == REAL_TOP) // TOp right
        {
            yVels[index] = 1;
            xVels[index] = 0;
        }
        else if (entity->y == REAL_HEIGHT) // Bottom right
        {
            xVels[index] = -1;
            yVels[index] = 0;
        }
    }
}

// Animates 4 entities.
void animateEntities(struct Entity entities[])
{
    // Move other entity sprites / coordinates
    for (int i = 0; i < 4; i++)
    {
        animateSprite(&entities[i], i);

        scroll_sprite(i + 1, xVels[i], yVels[i]);

        entities[i].x += xVels[i];
        entities[i].y += yVels[i];
    }
}

// Waits for the player to press start and goes to the next context.
void titleScreen()
{
    struct Entity entities[4];
    setupEntities(entities);

    while (joypad() != J_A)
    {
        animateEntities(entities);
        wait_vbl_done();
    }

    pauseSound();

    // Next context
    GameState++;
    HIDE_SPRITES;

    // Reset sprites
    for (int i = 0; i < 4; i++)
    {
        set_sprite_tile(i + 1, 0x00);
        move_sprite(i + 1, 0, 0);
        entities[i].x = 0;
        entities[i].y = 0;
    }

    while (clock < 144)
    {
        scroll_win(0, -1);
        delay(2);
        clock++;
    }

    delay(150);
}