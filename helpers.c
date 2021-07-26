// Initializes the player and sets their sprite.
void setupPlayer(struct Entity * player)
{
    player->id = 0;
    player->x = MAP_CENTER_X;
    player->y = MAP_CENTER_Y;
    player->xVel = 0;
    player->yVel = 0;

    // Setup player sprite
    set_sprite_tile(player->id, 0);
    move_sprite(player->id, MIDDLE_X, MIDDLE_Y);

    // Scroll the background to the player.
    scroll_bkg(MAP_CENTER_X - MIDDLE_X, MAP_CENTER_Y - MIDDLE_Y);
}

// Prepares the 4 entites for the animateEntities method.
void setupEntities(struct Entity entities[])
{
    for (int i = 0; i < SPRITE_QTY; i++)
    {
        entities[i].id = i + 1;
        entities[i].xVel = 0;
        entities[i].yVel = 0;
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

            if (player->y <= MIDDLE_Y) return 0; // Top right
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