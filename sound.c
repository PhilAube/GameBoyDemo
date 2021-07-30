// Plays the pause sound.
void pauseSound(int paused)
{
    const int offset = 8;
        
    int length = 50;

    NR10_REG = 0x00; 
    NR11_REG = 0x80;

    if (paused == 0) // Pause sound
    {
        // Set window tiles to pause
        for (int i = 0; i < 4; i++)
        {
            windowmap[i + offset] = 0x2A + i;
        }

        set_win_tiles(0, 0, 20, 1, windowmap);

        // C
        NR12_REG = 0x43;  
        NR13_REG = 0x06;
        NR14_REG = 0x87;    
        delay(length);

        // E
        NR12_REG = 0x43;  
        NR13_REG = 0x39;
        NR14_REG = 0x87;  
        delay(length);

        // G
        NR12_REG = 0x43;  
        NR13_REG = 0x59;
        NR14_REG = 0x87;  
        delay(length);

        // High C
        NR12_REG = 0x43;  
        NR13_REG = 0x82;
        NR14_REG = 0x87;  
        delay(length);
    }
    else // Unpause sound
    {
        // Set window tiles back
        // for (int i = 0; i < 4; i++) windowmap[i + offset] = 0x29;
        //set_win_tiles(0, 0, 20, 1, windowmap);

        // High C
        NR12_REG = 0x43;  
        NR13_REG = 0x82;
        NR14_REG = 0x87;  
        delay(length);

        // G
        NR12_REG = 0x43;  
        NR13_REG = 0x59;
        NR14_REG = 0x87;  
        delay(length);

        // E
        NR12_REG = 0x43;  
        NR13_REG = 0x39;
        NR14_REG = 0x87;  
        delay(length);

        // C
        NR12_REG = 0x43;  
        NR13_REG = 0x06;
        NR14_REG = 0x87;    
        delay(length);
    }
}

// 321 GO sound
void countdownSound()
{
    int offset = 189;

    for (int i = 0; i < 3; i++)
    {
        // Show 321
        windowmap[offset] = 0x31 + (i * 4);
        windowmap[offset + 1] = 0x32 + (i * 4);
        windowmap[offset + 20] = 0x33 + (i * 4);
        windowmap[offset + 21] = 0x34 + (i * 4);
        set_win_tiles(0, 0, 20, 18, windowmap);

        // Make C sound
        NR10_REG = 0x00;
        NR11_REG = 0X81;
        NR12_REG = 0X43;
        NR13_REG = 0X0D;
        NR14_REG = 0X86;
        delay(1000);
    }

    // Show GO
    windowmap[offset] = 0x3D;
    windowmap[offset + 1] = 0x3E;
    windowmap[offset + 20] = 0x3F;
    windowmap[offset + 21] = 0x40;
    set_win_tiles(0, 0, 20, 18, windowmap);

    // Higher C sound
    NR10_REG = 0x00;
    NR11_REG = 0X80;
    NR12_REG = 0X40; // Perma note
    NR13_REG = 0X06;
    NR14_REG = 0X87;
    delay(500);
    NR12_REG = 0X41; // Stop the perma note

    // Hide the GO
    windowmap[offset] = 0x00;
    windowmap[offset + 1] = 0x00;
    windowmap[offset + 20] = 0x00;
    windowmap[offset + 21] = 0x00;
    set_win_tiles(0, 0, 20, 18, windowmap);
}