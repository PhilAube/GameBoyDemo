int detectEdges(struct Entity * player);

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

// Modifies x/y velocities based on joypad.
void movePlayer(struct Entity * player)
{
    int result = joypad();

    switch (result)
    {
        case J_LEFT:
            player->xVel = -1;
            player->yVel = 0;
            break;

        case J_RIGHT:
            player->xVel = 1;
            player->yVel = 0;
            break;

        case J_UP:
            player->xVel = 0;
            player->yVel = -1;

            break;

        case J_DOWN:
            player->xVel = 0;
            player->yVel = 1;
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
    // Lower half of the map
    if (player->y >= MIDDLE_Y2 && player->yVel != 0)
    {
        if (player->y == MIDDLE_Y2) return 1;
        else return 0;
    } 

    if (player->x <= MIDDLE_X) // Left side of the map
    {
        if (player->y <= MIDDLE_Y) return 0; // Top left
        else
        {
            if (player->y >= MIDDLE_Y2) return 0; // Bottom left
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
            if (player->x == MIDDLE_X2) return 1;
            if (player->y <= MIDDLE_Y) return 0; // Top right
            else
            {
                if (player->y >= MIDDLE_Y2) return 0; // Bottom right
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
                if (player->yVel == 0) return 1; // Mid-top
                else return 0; 
            } 
            else
            {
                if (player->y >= MIDDLE_Y2)
                {
                    if (player->yVel == 0) return 1; // Mid-bottom
                    else return 0; 
                } 
                else return 1; // Middle AF
            }
        }
    }
}