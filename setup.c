// Initializes all necessary registers and loads tiles.
void setupHardware()
{
    // Setup sound registers
    NR52_REG = 0x80; // (1000 0000) turns the sound on.
    NR50_REG = 0x77; // Sets the volume in both L and R channels to max.
    NR51_REG = 0xFF; // (1111 1111) Selects which channels to use, in this case two bits for L/R for all 4 channels.

    // Setup font tiles for window layer
    font_t min_font;
    font_init();
    min_font = font_load(font_min); // 36 tiles
    font_set(min_font);

    // Setup window layer
    set_win_tiles(0, 0, 20, 18, windowmap);
    move_win(7, 144);

    // Start sprite tiles at 26 because of Nintendo logo
    set_sprite_data(26, 4, sprites);
    // Start background tiles at 37 because of font tiles
    set_bkg_data(37, 28, bgtiles);
    // First, title screen map is set
    set_bkg_tiles(0, 0, 20, 10, titlescreenmap);

    // Enable hardware
    SHOW_SPRITES;
    SHOW_WIN;
    SHOW_BKG;
    DISPLAY_ON;
}

// Initializes the player and sets their sprite.
void setupPlayer(struct Entity * player)
{
    player->x = MAP_CENTER_X;
    player->y = MAP_CENTER_Y;
    // xVel and yVel already set globally

    // Setup player sprite
    // Start at 0x1A because of the Nintendo logo
    set_sprite_tile(0, 0x1A);
    move_sprite(0, MIDDLE_X, MIDDLE_Y);

    // Scroll the background to the player.
    scroll_bkg(SCROLL_OFFSET_X, SCROLL_OFFSET_Y);
}

// TODO : Spawn coins randomly
void setupCoins(struct Entity coins[])
{
    for (int i = 0; i < ENTITY_QTY; i++)
    {
        // TODO: Get random X and Y
        coins[i].x = (i + 3) * 8 - SCROLL_OFFSET_X;
        coins[i].y = 32 - SCROLL_OFFSET_Y;
        set_sprite_tile(i + 1, 0x1C);
        move_sprite(i + 1, coins[i].x, coins[i].y);
    }
}

// Prepares the 4 entites for the animateEntities method.
void setupEntities(struct Entity entities[])
{
    for (int i = 0; i < 4; i++)
    {
        // X and Y velocities already set globally
        set_sprite_tile(i + 1, 0x1A);
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