// Returns 1 if paused, 0 otherwise.
int isPaused()
{
    // Bitwise AND to query the status of the pause bit (0010 0000)
    if (GameLoopState & 0x20) return 1;
    else return 0;
}

// Changes the window map to display the word pause if the game is paused.
void displayPause()
{
    const int offset = 8;

    if (isPaused() == 0)
    {
        for (int i = 0; i < 4; i++)
        {
            windowmap[i + offset] = 0x2A + i;
        }

        set_win_tiles(0, 0, 20, 2, windowmap);

        pauseSound(0);
    }
    else
    {
        waitpadup();
        pauseSound(1);

        for (int i = 0; i < 4; i++)
        {
            windowmap[i + offset] = 0x29;
        }

        set_win_tiles(0, 0, 20, 2, windowmap);
    }
}

// Animates a sprite clockwise around the screen.
void animateSprite(struct Entity * entity)
{
    if (entity->x == REAL_LEFT)
    {
        if (entity->y == REAL_TOP) // Top left
        {
            entity->yVel = 0;
            entity->xVel = 1;
        }
        else if (entity->y == REAL_HEIGHT) // Bottom left
        {
            entity->yVel = -1;
            entity->xVel = 0;
        }
    }
    else if (entity->x == REAL_WIDTH)
    {
        if (entity->y == REAL_TOP) // TOp right
        {
            entity->yVel = 1;
            entity->xVel = 0;
        }
        else if (entity->y == REAL_HEIGHT) // Bottom right
        {
            entity->xVel = -1;
            entity->yVel = 0;
        }
    }
}

// Animates 4 entities.
void animateEntities(struct Entity entities[])
{
    // Move other entity sprites / coordinates
    for (int i = 0; i < SPRITE_QTY; i++)
    {
        animateSprite(&entities[i]);

        scroll_sprite(entities[i].id, entities[i].xVel, entities[i].yVel);

        entities[i].x += entities[i].xVel;
        entities[i].y += entities[i].yVel;
    }
}

// Button handler during the game loop.
void movePlayer(struct Entity * player)
{
    int result = joypad();

    switch (result)
    {
        case J_LEFT:
            if (isPaused() == 1) break;
            player->xVel = -1;
            player->yVel = 0;
            break;

        case J_RIGHT:
            if (isPaused() == 1) break;
            player->xVel = 1;
            player->yVel = 0;
            break;

        case J_UP:
            if (isPaused() == 1) break;
            player->xVel = 0;
            player->yVel = -1;
            break;

        case J_DOWN:
            if (isPaused() == 1) break;
            player->xVel = 0;
            player->yVel = 1;
            break;

        case J_START:
            displayPause();
            // Bitwise XOR to flip the pause bit (0010 0000)
            GameLoopState = GameLoopState ^ 0x20;
            waitpadup();
            break;

        default:
            break;
    }
}

// Changes the velocity to 0 if the player is about to collide with wall.
void checkWallCollisions(struct Entity * player)
{
    if (player->x == REAL_LEFT + SPRITE_SIZE)
    {
        if (player->y == REAL_TOP + SPRITE_SIZE) // Top left corner
        {
            if (player->xVel == -1 || player->yVel == -1)
            {
                player->xVel = 0;
                player->yVel = 0;
                return;
            }
        }
        else if (player->y == MAP_SIZE) // Bottom left corner
        {
            if (player->xVel == -1 || player->yVel == 1)
            {
                player->xVel = 0;
                player->yVel = 0;
                return;
            }
        }
        else if (player->xVel == -1) // Just left
        {
            player->xVel = 0;
            return;
        } 
    }
    else if (player->x == MAP_SIZE - SPRITE_SIZE)
    {
        if (player->y == REAL_TOP + SPRITE_SIZE) // Top right corner
        {
            if (player->xVel == 1 || player->yVel == -1)
            {
                player->xVel = 0;
                player->yVel = 0;
            }
        }
        else if (player->y == MAP_SIZE) // Bottom right corner
        {
            if (player->xVel == 1 || player->yVel == 1)
            {
                player->xVel = 0;
                player->yVel = 0;
            }
        }
        else if (player->xVel == 1) // Just right
        {
            player->xVel = 0;
            return;
        }
    }

    if (player->y == REAL_TOP + SPRITE_SIZE) // Just top
    {
        if (player->yVel == -1)
        {
            player->yVel = 0;
            return;
        }
    }
    else if (player->y == MAP_SIZE) // Just bottom
    {
        if (player->yVel == 1)
        {
            player->yVel = 0;
            return;
        }
    }
}

// Returns 1 if the game should scroll map, 0 if it should scroll sprite.
int scrollMapOrNot(struct Entity * player)
{
    if (player->x <= MIDDLE_X) // Left side of the map
    {
        if (player->x == MIDDLE_X && player->xVel == 1) return 1;

        if (player->y <= MIDDLE_Y)
        {
            if (player->y == MIDDLE_Y && player->yVel == 1) return 1;
            else return 0; // Top left
        } 
        else
        {
            if (player->y >= MIDDLE_Y2)
            {
                if (player->y == MIDDLE_Y2 && player->yVel == -1) return 1;
                else return 0; // Bottom left
            } 
            else
            {
                if (player->xVel == 0) return 1; // Mid-left
                else return 0;
            } 
        }
    }
    else 
    {
        if (player->x >= MIDDLE_X2) // Right side of the map
        {
            if (player->x == MIDDLE_X2 && player->xVel == -1) return 1;

            if (player->y <= MIDDLE_Y)
            {
                if (player->y == MIDDLE_Y && player->yVel == 1) return 1;
                else return 0; // Top right
            } 
            else
            {
                if (player->y >= MIDDLE_Y2)
                {
                    if (player->y == MIDDLE_Y2 && player->yVel == -1) return 1;
                    else return 0; // Bottom right
                } 
                else
                {
                    if (player->xVel == 0) return 1; // Mid-right
                    else return 0;
                } 
            }
        }
        else // Middle part (on the x axis)
        {
            if (player->y <= MIDDLE_Y)
            {
                if (player->y == MIDDLE_Y && player->yVel == 1) return 1;

                if (player->yVel == 0) return 1; // Mid-top
                else return 0; 
            } 
            else
            {
                if (player->y >= MIDDLE_Y2)
                {
                    if (player->y == MIDDLE_Y2 && player->yVel == -1) return 1;

                    if (player->yVel == 0) return 1; // Mid-bottom
                    else return 0; 
                } 
                else return 1; // Middle AF
            }
        }
    }
}