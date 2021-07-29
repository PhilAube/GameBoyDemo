// Returns 1 if object 1 and object 2 sprites are overlapping.
int areSpritesColliding(struct Entity * o1, struct Entity * o2)
{
    if (o1->x < o2->x + SPRITE_SIZE && o1->x + SPRITE_SIZE > o2->x)
    {
        if (o1->y < o2->y + SPRITE_SIZE && o1->y + SPRITE_SIZE > o2->y)
        {
            return 1; // The sprites are overlapping
        }
    }

    return 0;
}

// Writes the score / lives to the window layer.
void updateHUD()
{
    const int offset1 = 46; // Tile to start displaying score
    const int offset2 = 52; // Tile to start displaying lives

    // Score
    UINT8 score = GameLoopState;
    score = score & 0x1F; // Bitwise AND to erase lives and pause bits.
    if (score < 10) windowmap[offset1] = 0x01; // 0
    else if (score < 20) windowmap[offset1] = 0x02; // 10
    else if (score <= 25) windowmap[offset1] = 0x03; // 20
    else windowmap[offset1] = 0x00; // Exception (shouldn't happen)
    windowmap[offset1 + 1] = (score % 10) + 1; // x1

    // Lives
    UINT8 lives = GameLoopState;
    lives = lives & 0xC0; // Bitwise AND to erase score and pause bits.
    lives = lives >> 6; // Bitshift to get the actual lives value
    windowmap[offset2] = 0x01; // First digit will always be 0
    windowmap[offset2 + 1] = lives + 1; // Second is the number of lives.

    set_win_tiles(0, 0, 20, 4, windowmap);
}

// Increments points and hides coin if player is colliding with one.
void checkPlayerCoinCollisions(struct Entity * player, struct Entity coins[])
{
    for (int i = 0; i < ENTITY_QTY; i++)
    {
        if (areSpritesColliding(player, &coins[i]))
        {
            // Hide coin sprite, increase points.
            coins[i].x = 0;
            coins[i].y = 0;
            set_sprite_tile(i + 1, 0);
            move_sprite(i + 1, 0, 0);
            GameLoopState++;
            updateHUD(); // Increment score in window layer
            // coinSound();
            break;
        }
    }
}

// (PAUSE) Hides sprites and scrolls the pause screen into view.
void scrollHUDUp()
{
    if (clock == 0) HIDE_SPRITES;

    scroll_win(0, -1);
    clock++;
    delay(1);
}

// (UNPAUSE) Scrolls the pause screen out of view and unhides sprites.
void scrollHUDDown()
{
    scroll_win(0, 1);
    clock--;
    delay(1);

    if (clock == 0) SHOW_SPRITES;
}

// Scrolls coins to follow along with BG
void scrollCoins(struct Entity coins[])
{
    for (int i = 0; i < ENTITY_QTY; i++)
    {
        coins[i].x -= xVel;
        coins[i].y -= yVel;
        scroll_sprite(i + 1, -xVel, -yVel);
    }
}

// An alternative to delay() which can save battery.
void performantDelay(int n)
{
    for (int i = 0; i < n; i++)
    {
        wait_vbl_done();
    }
}

// Returns 1 if paused, 0 otherwise.
int isPaused()
{
    // Bitwise AND to query the status of the pause bit (0010 0000)
    if (GameLoopState & 0x20) return 1;
    else return 0;
}

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

// Button handler during the game loop.
void movePlayer()
{
    int result = joypad();
    UINT8 status = 0;

    switch (result)
    {
        case J_LEFT:
            if (isPaused()) break;
            xVel = -1;
            yVel = 0;
            break;

        case J_RIGHT:
            if (isPaused()) break;
            xVel = 1;
            yVel = 0;
            break;

        case J_UP:
            if (isPaused()) break;
            xVel = 0;
            yVel = -1;
            break;

        case J_DOWN:
            if (isPaused()) break;
            xVel = 0;
            yVel = 1;
            break;

        case J_START:
            if (clock == 0 && !(GameState & 0x20)) // Only if START isn't being pressed
            {
                pauseSound(0);
                // Bitwise XOR to flip the START HOLD bit (0010 0000)
                GameState = GameState ^ 0x20; 
                // Bitwise XOR to flip the pause bit (0010 0000)
                GameLoopState = GameLoopState ^ 0x20;
            }
            else if (clock == 144 && !(GameState & 0x20)) // Only if START isn't being pressed
            {
                waitpadup(); // Only unpause when player lets go
                pauseSound(1);
                // Bitwise XOR to flip the pause bit (0010 0000)
                GameLoopState = GameLoopState ^ 0x20;
            }
            break;

        default:
            // Start button is not being held (by default)
            // Bitwise AND to mask 5th bit to 0 (1101 1111)
            GameState = GameState & 0xDF; 
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
            if (xVel == -1 || yVel == -1)
            {
                xVel = 0;
                yVel = 0;
                return;
            }
        }
        else if (player->y == MAP_SIZE) // Bottom left corner
        {
            if (xVel == -1 || yVel == 1)
            {
                xVel = 0;
                yVel = 0;
                return;
            }
        }
        else if (xVel == -1) // Just left
        {
            xVel = 0;
            return;
        } 
    }
    else if (player->x == MAP_SIZE - SPRITE_SIZE)
    {
        if (player->y == REAL_TOP + SPRITE_SIZE) // Top right corner
        {
            if (xVel == 1 || yVel == -1)
            {
                xVel = 0;
                yVel = 0;
            }
        }
        else if (player->y == MAP_SIZE) // Bottom right corner
        {
            if (xVel == 1 || yVel == 1)
            {
                xVel = 0;
                yVel = 0;
            }
        }
        else if (xVel == 1) // Just right
        {
            xVel = 0;
            return;
        }
    }

    if (player->y == REAL_TOP + SPRITE_SIZE) // Just top
    {
        if (yVel == -1)
        {
            yVel = 0;
            return;
        }
    }
    else if (player->y == MAP_SIZE) // Just bottom
    {
        if (yVel == 1)
        {
            yVel = 0;
            return;
        }
    }
}

// Returns 1 if the game should scroll map, 0 if it should scroll sprite.
int scrollMapOrNot(struct Entity * player)
{
    if (player->x <= MIDDLE_X) // Left side of the map
    {
        if (player->x == MIDDLE_X && xVel == 1) return 1;

        if (player->y <= MIDDLE_Y)
        {
            if (player->y == MIDDLE_Y && yVel == 1) return 1;
            else return 0; // Top left
        } 
        else
        {
            if (player->y >= MIDDLE_Y2)
            {
                if (player->y == MIDDLE_Y2 && yVel == -1) return 1;
                else return 0; // Bottom left
            } 
            else
            {
                if (xVel == 0) return 1; // Mid-left
                else return 0;
            } 
        }
    }
    else 
    {
        if (player->x >= MIDDLE_X2) // Right side of the map
        {
            if (player->x == MIDDLE_X2 && xVel == -1) return 1;

            if (player->y <= MIDDLE_Y)
            {
                if (player->y == MIDDLE_Y && yVel == 1) return 1;
                else return 0; // Top right
            } 
            else
            {
                if (player->y >= MIDDLE_Y2)
                {
                    if (player->y == MIDDLE_Y2 && yVel == -1) return 1;
                    else return 0; // Bottom right
                } 
                else
                {
                    if (xVel == 0) return 1; // Mid-right
                    else return 0;
                } 
            }
        }
        else // Middle part (on the x axis)
        {
            if (player->y <= MIDDLE_Y)
            {
                if (player->y == MIDDLE_Y && yVel == 1) return 1;

                if (yVel == 0) return 1; // Mid-top
                else return 0; 
            } 
            else
            {
                if (player->y >= MIDDLE_Y2)
                {
                    if (player->y == MIDDLE_Y2 && yVel == -1) return 1;

                    if (yVel == 0) return 1; // Mid-bottom
                    else return 0; 
                } 
                else return 1; // Middle AF
            }
        }
    }
}