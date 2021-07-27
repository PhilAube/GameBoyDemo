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
    set_win_tiles(0, 0, 20, 2, windowmap);
    move_win(7, 128);

    // Start sprite tiles at 26 because of Nintendo logo
    set_sprite_data(26, 3, sprites);
    // Start background tiles at 37 because of font tiles
    set_bkg_data(37, 9, bgtiles);
    set_bkg_tiles(0, 0, 32, 32, bgmap);

    // Enable hardware
    SHOW_SPRITES;
    SHOW_WIN;
    SHOW_BKG;
    DISPLAY_ON;
}

// Initializes the player and sets their sprite.
void setupPlayer(struct Entity * player)
{
    player->id = 0;
    player->x = MAP_CENTER_X;
    player->y = MAP_CENTER_Y;
    player->xVel = 0;
    player->yVel = 0;

    // Setup player sprite
    // Start at 0x1A because of the Nintendo logo
    set_sprite_tile(player->id, 0x1A);
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