void updateHUD();
void scrollHUDDown(int show);
void scrollHUDUp(int hide);
void resetGame(struct Entity * player);
int getSelectedMenuChoice();

// Overlays the text for the pause menu.
void changePauseMenu()
{
    const int offset1 = 8;
    const int offset2 = 145; // Play
    const int offset3 = 205; // Restart
    const int offset4 = 265; // Quit

    const UINT8 play[4] = {0x1A,0x16,0x0B,0x23};
    const UINT8 restart[7] = {0x1C,0x0F,0x1D,0x1E,0x0B,0x1C,0x1E};
    const UINT8 quit[4] = {0x1B,0x1F,0x13,0x1E};

    // Set top of window tiles to pause
    for (int i = 0; i < 4; i++) windowmap[i + offset1] = 0x2A + i;

    // -> PLAY
    for (int i = 0; i < 10; i++)
    {
        if (i < 6) windowmap[i + offset2] = 0x00;
        else windowmap[i + offset2] = play[i - 6];
    }

    // -> RESTART
    for (int i = 0; i < 10; i++)
    {
        if (i < 3) windowmap[i + offset3] = 0x00; // Pad to the right
        else windowmap[i + offset3] = restart[i - 3];
    } 

    // -> QUIT
    for (int i = 0; i < 10; i++)
    {
        if (i < 6) windowmap[i + offset4] = 0x00;
        else windowmap[i + offset4] = quit[i - 6];
    } 

    // -> ARROW (Reset to the first option every time)
    windowmap[offset2] = 0x30;

    set_win_tiles(0, 0, 20, 18, windowmap);
}

// Plays unpause sound, scrolls HUD down and flips bits back to defaults.
void unpause()
{
    const int offset = 8;
    waitpadup();
    unpauseSound();
    scrollHUDDown(1);

    // Set window tiles back
    for (int i = 0; i < 4; i++) windowmap[i + offset] = 0x29;
    set_win_tiles(0, 0, 20, 1, windowmap);

    // Bitwise XOR to flip the pause bit (0010 0000)
    GameLoopState = GameLoopState ^ 0x20;

    // Set menu choice back to 1st option
    // Bitwise AND to mask bits to 0 (0011 1111)
    GameState = GameState & 0x3F;
}

// Handles button presses during pause.
void pauseMenu(struct Entity * player)
{
    switch (joypad())
    {
        case J_START: // Unpause
            unpause();
            break;

        case J_UP: 
            switch (getSelectedMenuChoice()) // Cycle through pause menu options
            {
                case 0: // Play
                    // Set menu choice to restart (2)
                    GameState = GameState | 0x80; // Bitwise OR to mask 7th bit to 1
                    break;
                case 1: // Restart
                    // Set menu choice to play (0)
                    GameState = GameState & 0x3F; // Mask 7th and 6th bit to 0 (0011 1111)
                    break;
                case 2: // Quit
                    // Set menu choice to restart (1)
                    GameState = GameState & 0x7F; // Mask 7th bit to 0 (0111 1111)
                    GameState = GameState | 0x40; // Mask 6th bit to 1 (0100 0000)
                    break;
            }

            scrollSound();
            updateHUD();
            waitpadup();
            break;

        case J_DOWN:
            switch (getSelectedMenuChoice()) // Cycle through pause menu options
            {
                case 0: // Play
                    // Bitwise OR to set menu choice to restart (0100 0000)
                    GameState = GameState | 0x40;
                    break;
                case 1: // Restart
                    // Set menu choice to quit (1000 0000)
                    GameState = GameState & 0xBF; // Mask 6th bit to 0 (1011 1111)
                    GameState = GameState | 0x80; // Mask 7th bit to 1 (1000 0000)
                    break;
                case 2: // Quit
                    // Set menu choice to play
                    GameState = GameState & 0x7F; // Mask 7th bit to 0 (0111 1111)
                    break;
            }

            scrollSound();
            updateHUD();
            waitpadup();
            break;

        case J_A:
            switch (getSelectedMenuChoice())
            {
                case 0: // Play
                    unpause();
                    break;

                case 1: // Restart
                    GameState--;
                    // Reset background
                    move_bkg(SCROLL_OFFSET_X, SCROLL_OFFSET_Y);
                    resetGame(player);

                    unpauseSound();
                    scrollHUDDown(0);

                    set_win_tiles(0, 0, 20, 18, windowmap);
                    delay(100);

                    scrollHUDUp(0);
                    break;
                
                case 2: // Quit
                    // Setting the game context back to 0 (title screen)
                    // Bitwise AND to mask bits to 0 (1111 1100)
                    GameState = GameState & 0xFC;
                    
                    // Reset background
                    set_bkg_tiles(0, 0, 20, 18, titlescreenmap);
                    move_bkg(0, 0);

                    // Move player sprite before HUD scrolldown
                    move_sprite(0, 0, 0); 

                    unpauseSound();
                    scrollHUDDown(1);

                    resetGame(player);
                    set_win_tiles(0, 0, 20, 18, windowmap);
                    break;
            }
            
            break;
    }
}
