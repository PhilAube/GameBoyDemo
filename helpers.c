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

        // FOR DEBUGGING: Show coordinates
        case J_A:
            printf("X %d / Y %d \n", player->x, player->y);
            // Stop player
            player->xVel = 0;
            player->yVel = 0;
            // Prevent multiple prints
            waitpadup();
            break;
        
        // FOR DEBUGGING: Eraser
        case J_B:
            printf(" \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n");
            // Prevent multiple prints
            waitpadup();
            break;

        default:
            break;
    }
}

// Changes the velocity to 0 if the player is about to collide with wall.
void checkWallCollisions(struct Entity * player)
{
    if (player->x == REAL_LEFT)
    {
        if (player->y == REAL_TOP) // Top left corner
        {
            if (player->xVel == -1 || player->yVel == -1)
            {
                player->xVel = 0;
                player->yVel = 0;
                return;
            }
        }
        else if (player->y == REAL_HEIGHT) // Bottom left corner
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
    else if (player->x == REAL_WIDTH)
    {
        if (player->y == REAL_TOP) // Top right corner
        {
            if (player->xVel == 1 || player->yVel == -1)
            {
                player->xVel = 0;
                player->yVel = 0;
            }
        }
        else if (player->y == REAL_HEIGHT) // Bottom right corner
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

    if (player->y == REAL_TOP) // Just top
    {
        if (player->yVel == -1)
        {
            player->yVel = 0;
            return;
        }
    }
    else if (player->y == REAL_HEIGHT) // Just bottom
    {
        if (player->yVel == 1)
        {
            player->yVel = 0;
            return;
        }
    }
}